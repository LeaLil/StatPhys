#ifndef MDPARAMETERS_H
#define MDPARAMETERS_H

#include <string>

enum class FinalCoordinateFileFormat {
    binary,
    ascii
};

enum class TrajectoryFileFormat {
    binary,
    ascii
};

enum class InitialXVGenerator {
    generateInitialX,
    xFromAscii,
    xFromBinary,
    xvFromAscii,
    xvFromBinary
};

enum class SimulationType {
    constantEnergy,
    constantTemperature
};

/*!
 * This struct contains the parameters for a MD simulation for the Lennard-Jones model.
 */
struct MDParameters {
    static MDParameters defaultParameters();

    std::string title;
    int numberAtoms;
    double atomicMass;
    SimulationType mdType;
    double boxSize[3];
    int numberMDSteps;
    double initialTime;
    double timeStep;
    double initialTemperature;
    double targetTemperature;
    double temperatureCouplingTime;
    int randomSeed;
    InitialXVGenerator xvInitialization;
    double coordInitializationSpread;
    FinalCoordinateFileFormat finalXVOutput;
    int numberAtomsOnBoxEdge[3];
    double epsilonLJ;
    double sigmaLJ;
    double interactionCutoffRadius;
    int propertyPrintingInterval;
    int numberRadialDistrPoints;
    double radialDistrCutoffRadius;
    bool trajectoryOutput;
    TrajectoryFileFormat trajectoryOutputFormat;
    int trajectoryOutputInterval;
};

FinalCoordinateFileFormat finalCoordinateFileFormatFromInt(int ntxo);
int finalCoordinateFileFormatToInt(FinalCoordinateFileFormat ntxo);

InitialXVGenerator initialXVGeneratorFromInt(int ntxi);
int initialXVGeneratorToInt(InitialXVGenerator ntxi);

TrajectoryFileFormat trajectoryFileFormatFromInt(int ntpw);
int trajectoryFileFormatToInt(TrajectoryFileFormat ntpw);

SimulationType simulationTypeFromInt(int ntt);
int simulationTypeToInt(SimulationType ntt);

#endif // MDPARAMETERS_H
