#include "InteractionCalculator.h"
#include "LJPotential.h"
#include "HarmonicPotential.h"
#include "MorsePotential.h"
#include "TotalPotential.h"
#include "Molecule.h"
#include <cmath>

inline int nearestInteger(double x) {
    return x > 0 ? static_cast<int>(x + 0.5) : static_cast<int>(x - 0.5);
}

InteractionCalculator::InteractionCalculator(const MDParameters& parameters)
  : par(parameters),
    radialDistribution(parameters.numberRadialDistrPoints, parameters.radialDistrCutoffRadius) {
    initializeValues();
}

void InteractionCalculator::initializeValues() {
    sig6 = par.sigmaLJ * par.sigmaLJ;
    sig6 = sig6 * sig6 * sig6;
    c6 = 4. * par.epsilonLJ * sig6;
    c12 = c6 * sig6;
    rcutf2 = par.interactionCutoffRadius * par.interactionCutoffRadius;
    for (int m = 0; m < 3; m++)
        inverseBoxLength[m] = 1.0 / par.boxSize[m];
}

void InteractionCalculator::calculate(const std::vector<double>& positions, std::vector<double>& forces, std::vector<Molecule>& moleculeList) {
    resetVariablesToZero(forces);

    //TODO: Interactions for molecules:
    for(int i = 0; i < moleculeList.size(); i++) {
        for(int j = i+1; j < moleculeList.size(); j++) {
            potentialEnergy += moleculeList[i].calculateInteraction(moleculeList[j], par);
        }
    }

    virial /= 2; //TODO: Explain please


}


void InteractionCalculator::resetVariablesToZero(std::vector<double>& forces) {
    radialDistribution.setZero();
    potentialEnergy = 0;
    virial = 0;
    int nat3 = 3 * par.numberAtoms;
    for (int j3 = 0; j3 < nat3; j3++)
        forces[j3] = 0;
}

void InteractionCalculator::calculateInteraction(int i, int j, const std::vector<double>& positions,
                                                 std::vector<double>& forces) {
    applyPeriodicBoundaryConditions(i, j, positions);

    calculateSquaredDistance();

    if (rij2 < rcutf2) {
        calculatePotentialAndForceMagnitude();
        potentialEnergy += eij;
        calculateForceAndVirialContributions(i, j, forces);
    }
    radialDistribution.addPairAtSquaredDistance(rij2);
}

void InteractionCalculator::applyPeriodicBoundaryConditions(int i, int j, const std::vector<double>& positions) {
    int i3 = 3 * i;
    int j3 = 3 * j;
    for (int m = 0; m < 3; m++) {
        xij[m] = positions[i3 + m] - positions[j3 + m];
        xij[m] = xij[m] - nearestInteger(xij[m]*inverseBoxLength[m]) * par.boxSize[m];
    }
}

void InteractionCalculator::calculateSquaredDistance() {
    rij2 = 0;
    for (int m = 0; m < 3; m++)
        rij2 += xij[m] * xij[m];
}

void InteractionCalculator::calculatePotentialAndForceMagnitude() {
    double r = sqrt(rij2);
   // Potential *potential = new LJPotential(r, r, par.sigmaLJ, par.epsilonLJ);
    //Potential *potential = new HarmonicPotential(1, r, 0.01);
    //Potential *potential = new MorsePotential(r, 0.11, 1, 1);

    Potential *potential = new TotalPotential(r, true, par); //You forgot a "public" beim Erben :-) Please don't use 1/0 for true/false
    //Avogadro
    eij= potential->computePotential();
    dij = potential->computeForceMagnitude();

    delete potential;

}

void InteractionCalculator::calculateForceAndVirialContributions(int i, int j, std::vector<double>& forces) {
    int i3 = 3 * i;
    int j3 = 3 * j;
    for (int m = 0; m < 3; m++) {
        // Force increment in direction of inter-particle vector
        //(note: xij[m]/rij is unit vector in inter-particle direction.)
        double df = xij[m] * dij;
        forces[i3 + m] += df;
        forces[j3 + m] -= df;
        virial -= xij[m] * df;
    }
}

double InteractionCalculator::getPotentialEnergy() const {
    return potentialEnergy;
}

double InteractionCalculator::getVirial() const {
    return virial;
}

const InstantaneousRadialDistribution& InteractionCalculator::getInstantaneousRadialDistribution() const {
    return radialDistribution;
}
