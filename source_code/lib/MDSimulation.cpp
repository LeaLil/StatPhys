#include "MDSimulation.h"
#include "TrajectoryFileWriter.h"
#include "MDRun.h"
#include "CoordinatesAndVelocitiesInitializer.h"
#include "ParameterIO.h"
#include "ParameterValidityChecker.h"
#include "RandomNumberGenerator.h"

MDSimulation::MDSimulation(std::ostream &outputStream)
        : output(outputStream) {
}

void MDSimulation::performSimulation(const std::string &parameterFile, std::string coordinateFile) {
    MDParameters par = ParameterIO::readParameters(parameterFile);
    s.mdParameters = &par;

    performSimulation(par, coordinateFile);
}

void MDSimulation::performSimulation(const MDParameters &par, std::string coordinateFile) {
    parameters = par;
    prepareRun();
    checkParameterValidity();
    initializeCoordinatesAndVelocities(coordinateFile);
    executeMDIterations();
    finalizeRun();
}

void MDSimulation::prepareRun() {
    RandomNumberGenerator::setSeed(parameters.randomSeed);
    timer.programStart();
    output.printHeader();
    output.printParameters(parameters);
}

void MDSimulation::checkParameterValidity() {
    ParameterValidityChecker validityChecker(parameters);
    if (!validityChecker.valid()) {
        throw std::runtime_error("Invalid parameters: " + validityChecker.getErrorMessage());
    }
}

void MDSimulation::initializeCoordinatesAndVelocities(const std::string &coordinateFile) {
    CoordinatesAndVelocitiesInitializer xvInitializer(output, parameters, coordinateFile);
    s.boxLength = Point(parameters.boxSize[0], parameters.boxSize[1], parameters.boxSize[2]);
    xvInitializer.initialize(positions, velocities, moleculeList, s);

}

void MDSimulation::executeMDIterations() {
    TrajectoryFileWriter trajectoryWriter(parameters, "coords.txt", "coords.traj");
    trajectoryWriter.writeBeforeRun();

    timer.mdStart();
    MDRun mdRun(parameters, output, s, trajectoryWriter, moleculeList);
    mdRun.run(positions, velocities);
    timer.mdEnd();

    printRadialDistribution(mdRun.getRadialDistribution());
    trajectoryWriter.writeFinalCoordinates(moleculeList);
}

void MDSimulation::printRadialDistribution(const AveragedRadialDistribution &radialDistribution) {
    if (parameters.radialDistrCutoffRadius > 0 && parameters.numberAtoms > 1) {
        int ngr = radialDistribution.getNumberBins();
        double dgr = radialDistribution.getBinSize();
        std::vector<double> gr = radialDistribution.calculateNormalizedDistribution(parameters.numberAtoms,
                                                                                    parameters.boxSize[1] *
                                                                                    parameters.boxSize[2]);
        output.printRadialDistribution(ngr, dgr, gr.data());
    }
}

void MDSimulation::finalizeRun() {
    timer.programEnd();
    output.printTiming(timer);
}
