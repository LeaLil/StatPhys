#include "MDParameters.h"
#include <stdexcept>

MDParameters MDParameters::defaultParameters() {
    MDParameters p;
    p.numberAtoms = 1000;
    p.xvInitialization = InitialXVGenerator::generateInitialX;
    p.finalXVOutput = FinalCoordinateFileFormat::ascii;
    p.boxSize[0] = 10.0;
    p.boxSize[1] = 10.0;
    p.boxSize[2] = 10.0;
    p.numberAtomsOnBoxEdge[0] = 10;
    p.numberAtomsOnBoxEdge[1] = 10;
    p.numberAtomsOnBoxEdge[2] = 10;
    p.coordInitializationSpread = 0.1;
    p.randomSeed = 42;
    p.initialTemperature = 1.0;
    p.mdType = SimulationType::constantEnergy;
    p.targetTemperature = 1.0;
    p.temperatureCouplingTime = 1.0;
    p.numberMDSteps = 1000;
    p.initialTime = 0.0;
    p.timeStep = 0.005;
    p.atomicMass = 1.0;
    p.epsilonLJ = 1.0;
    p.sigmaLJ = 1.0;
    p.interactionCutoffRadius = 2.5;
    p.propertyPrintingInterval = 1;
    p.trajectoryOutputInterval = 5;
    p.trajectoryOutput = false;
    p.trajectoryOutputFormat = TrajectoryFileFormat::ascii;
    p.numberRadialDistrPoints = 100;
    p.radialDistrCutoffRadius = 2.5;
    return p;
}

FinalCoordinateFileFormat finalCoordinateFileFormatFromInt(int ntxo) {
    if (ntxo == 0)
        return FinalCoordinateFileFormat::binary;
    else if (ntxo == 1)
        return FinalCoordinateFileFormat::ascii;
    else
        throw std::runtime_error("Invalid value for FinalXVOutput");
}

int finalCoordinateFileFormatToInt(FinalCoordinateFileFormat ntxo) {
    switch (ntxo) {
        case FinalCoordinateFileFormat::binary:
            return 0;
        case FinalCoordinateFileFormat::ascii:
            return 1;
    }
}

InitialXVGenerator initialXVGeneratorFromInt(int ntxi) {
    switch (ntxi) {
        case 0:
            return InitialXVGenerator::generateInitialX;
        case 1:
            return InitialXVGenerator::xFromAscii;
        case 2:
            return InitialXVGenerator::xFromBinary;
        case 3:
            return InitialXVGenerator::xvFromAscii;
        case 4:
            return InitialXVGenerator::xvFromBinary;
        default:
            throw std::runtime_error("Invalid value for XVInitialization");
    }
}

int initialXVGeneratorToInt(InitialXVGenerator ntxi) {
    switch (ntxi) {
        case InitialXVGenerator::generateInitialX:
            return 0;
        case InitialXVGenerator::xFromAscii:
            return 1;
        case InitialXVGenerator::xFromBinary:
            return 2;
        case InitialXVGenerator::xvFromAscii:
            return 3;
        case InitialXVGenerator::xvFromBinary:
            return 4;
    }
}

TrajectoryFileFormat trajectoryFileFormatFromInt(int ntpw) {
    if (ntpw == 0)
        return TrajectoryFileFormat::binary;
    else if (ntpw == 2)
        return TrajectoryFileFormat::ascii;
    else
        throw std::runtime_error("Invalid value for TrajectoryOutputFormat");
}

int trajectoryFileFormatToInt(TrajectoryFileFormat ntpw) {
    switch (ntpw) {
        case TrajectoryFileFormat::binary:
            return 0;
        case TrajectoryFileFormat::ascii:
            return 2;
    }
}

SimulationType simulationTypeFromInt(int ntt) {
    if (ntt == 0)
        return SimulationType::constantEnergy;
    else if (ntt == 1)
        return SimulationType::constantTemperature;
    else
        throw std::runtime_error("Invalid value for MDType");
}

int simulationTypeToInt(SimulationType ntt) {
    switch (ntt) {
        case SimulationType::constantEnergy:
            return 0;
        case SimulationType::constantTemperature:
            return 1;
    }
}
