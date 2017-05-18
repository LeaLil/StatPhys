#include "MDRun.h"
#include "PeriodicBoundaryConditions.h"
#include "CenterOfMassCalculator.h"
#include "TrajectoryFileWriter.h"
#include <cmath>

MDRun::MDRun(const MDParameters &parameters, MDRunOutput &out, System &s, TrajectoryFileWriter &trajectoryFileWriter,
             std::vector<Molecule> &moleculeList)
        : par(parameters),
          output(out),
          s(s),
          trajectoryWriter(trajectoryFileWriter),
          forceCalculator(parameters),
          radialDistribution(parameters.numberRadialDistrPoints, parameters.radialDistrCutoffRadius),
          moleculeList(moleculeList) {
}

void MDRun::run(std::vector<double> &x, std::vector<double> &v) {
    forces.resize(x.size());

    synchronizedPositions.resize(x.size());

    radialDistribution.setZero();

    initializeVariables();
    initializeTemperature(v);

    output.printInitialTemperature(properties[1] / fac);
    output.printIterationStart();

    /* dynamics step */
    double time = par.initialTime;
    for (int nstep = 0; nstep < par.numberMDSteps; nstep++) {
        time += par.timeStep;
        performStep(x, v, moleculeList, nstep, time);
    }

    printAverages(time);
}

void MDRun::initializeVariables() {
    nat3 = 3 * par.numberAtoms;
    const double boltzmannConstant = 8.3144598e-3; // units: K^-1 ps^-2 u nm^2
    fac = nat3 * boltzmannConstant / 2.;
    s.totalKineticEnergy = ekin0 = fac * par.targetTemperature;
    halfTimeStep = par.timeStep / 2;
    dtm = par.timeStep / par.atomicMass;
    vol = par.boxSize[0] * par.boxSize[1] * par.boxSize[2];

    nhpr = 100 * par.propertyPrintingInterval;
    nlsq = par.numberMDSteps / 10;
    if (nlsq < 10) {
        nlsq = 10;
    }
    if (nlsq < par.propertyPrintingInterval) {
        nlsq = par.propertyPrintingInterval;
    }
    if (nhpr > nlsq) {
        nhpr = nlsq;
    }
    for (int i = 0; i < numberProperties; i++) {
        properties[i] = 0.;
        averages[i] = 0.;
        fluctuations[i] = 0.;
    }
    s.virial = 0;
    s.cutoffRadiusSquared = par.radialDistrCutoffRadius * par.radialDistrCutoffRadius;
}

void MDRun::initializeTemperature(const std::vector<double> &velocities) {
    s.totalKineticEnergy = 0;
    for (Molecule &m : moleculeList) {
        for (Element &e: m.elementList) {
            double sum = e.velocityVector.x * e.velocityVector.x + e.velocityVector.y * e.velocityVector.y +
                         e.velocityVector.z * e.velocityVector.z;
            sum *= e.weight * 0.5;
            s.totalKineticEnergy += sum;
        }
    }
    properties[1] = s.totalKineticEnergy;
    if (par.mdType == SimulationType::constantTemperature) {
        if (s.totalKineticEnergy < 1.e-6) {
            ekg = ekin0;
        } else {
            ekg = s.totalKineticEnergy;
        }
    }
}

void
MDRun::performStep(std::vector<double> &positions, std::vector<double> &velocities, std::vector<Molecule> &moleculeList,
                   int nstep, double time) {
    /* put atoms in central periodic box */
    PeriodicBoundaryConditions::recenterAtoms(par.numberAtoms, positions, par.boxSize, moleculeList);

    /* calculate forces, potential energy, virial
     * and contribution to the radial distribution function for the whole system
     * Doesn't apply anything! Just computes stuff!
     */
    s.totalPotentialEnergy = 0;
    s.virial = 0;
    forceCalculator.calculate(positions, forces, moleculeList);
    radialDistribution.addInstantaneousDistribution(forceCalculator.getInstantaneousRadialDistribution());


    s.virial /= 2;
    s.totalPotentialEnergy = forceCalculator.getPotentialEnergy();


    properties[3] = s.virial;
    properties[2] = s.totalPotentialEnergy;

    /* determine velocity scaling factor, when coupling to a bath */
    double scal = 1;
    if (par.mdType == SimulationType::constantTemperature) {
        double dtt = par.timeStep / par.temperatureCouplingTime;
        scal = std::sqrt(1 + dtt * (ekin0 / ekg - 1));
    }

    /* perform leap-frog integration step,
     * calculate kinetic energy at time t-dt/2 and at time t,
     * and calculate pressure
     */
    s.oldTotalKineticEnergy = 0.;
    s.totalKineticEnergy = 0.;
    /* Do the same for molecule list; */
    for (Molecule &m : moleculeList) {
        m.applyForces(par, scal);
    }

    properties[1] = s.totalKineticEnergy;
    properties[0] = properties[1] + properties[2];
    properties[4] = 2 * (s.totalKineticEnergy - s.virial) / (vol * 3.); //Compute new pressurce
    properties[5] = scal; //Save scal for no obv. reason
    if (par.mdType == SimulationType::constantTemperature) {
        ekg = s.oldTotalKineticEnergy;
    }

    /* update arrays for averages and fluctuations */
    for (int m = 0; m < numberProperties; m++) {
        averages[m] += properties[m];
        fluctuations[m] += properties[m] * properties[m];
    }

    printOutputForStep(positions, velocities, nstep, time);
}

void MDRun::printOutputForStep(const std::vector<double> &positions, const std::vector<double> &velocities, int nstep,
                               double time) {
    if ((nstep + 1) == (nstep + 1) / par.trajectoryOutputInterval * par.trajectoryOutputInterval) {
        trajectoryWriter.writeOutTrajectoryStep(moleculeList);
    }

    if (nstep == (nstep + 1) / nhpr * nhpr) {
        output.printPropertiesHeader();
    }

    if ((nstep + 1) == (nstep + 1) / par.propertyPrintingInterval * par.propertyPrintingInterval || nstep == 0) {
        output.printProperties(nstep, time, properties);
    }

    /* calculate and print center of mass motion
     * once in nlsq steps, at time t-dt/2
     * The positions must be back-calculated for t-dt/2, because of the time shift between x and v (leap-frog)
     */
    if ((nstep + 1) == (nstep + 1) / nlsq * nlsq) {
        for (int j3 = 0; j3 < nat3; j3++) {
            synchronizedPositions[j3] = positions[j3] - velocities[j3] * halfTimeStep;
        }
        CenterOfMassCalculator cm;
        cm.update(par.numberAtoms, synchronizedPositions, velocities, par.atomicMass);
        cm.printResults(output);
    }
}

void MDRun::printAverages(double time) {
    double tspan = par.numberMDSteps;
    for (int m = 0; m < numberProperties; m++) {
        averages[m] = averages[m] / tspan;
        fluctuations[m] = std::sqrt(std::abs(fluctuations[m] / tspan - averages[m] * averages[m]));
    }
    output.printAverages(par.numberMDSteps, time, averages);
    output.printRMSFluctuations(par.numberMDSteps, time, fluctuations);
    output.printAverageAndRMSTemperature(averages[1] / fac, fluctuations[1] / fac);
}

const AveragedRadialDistribution &MDRun::getRadialDistribution() const {
    return radialDistribution;
}
