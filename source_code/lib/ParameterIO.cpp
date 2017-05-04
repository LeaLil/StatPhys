#include "ParameterIO.h"
#include <fstream>
#include <iomanip>
#include <stdexcept>

using namespace std;

MDParameters ParameterIO::readParameters(const std::string &fileName) {
    ifstream fin;
    fin.open(fileName, std::ios::in);
    if (fin.bad())
        throw std::runtime_error("can't open " + fileName);

    MDParameters par;
    int ntxi, ntxo, ntpw, ntt, ntwxm;
    std::string dummy;

    getline(fin, dummy);
    getline(fin, par.title);

    getline(fin, dummy);
    fin >> par.numberAtoms
        >> par.atomicMass
        >> ntt;

    fin.ignore();
    getline(fin, dummy);
    fin >> par.boxSize[0]
        >> par.boxSize[1]
        >> par.boxSize[2];

    fin.ignore();
    getline(fin, dummy);
    fin >> par.numberMDSteps
        >> par.initialTime
        >> par.timeStep;

    fin.ignore();
    getline(fin, dummy);
    fin >> par.initialTemperature
        >> par.targetTemperature
        >> par.temperatureCouplingTime;

    fin.ignore();
    getline(fin, dummy);
    fin >> par.randomSeed;

    fin.ignore();
    getline(fin, dummy);
    fin >> ntxi
        >> par.coordInitializationSpread
        >> ntxo;

    fin.ignore();
    getline(fin, dummy);
    fin >> par.numberAtomsOnBoxEdge[0]
        >> par.numberAtomsOnBoxEdge[1]
        >> par.numberAtomsOnBoxEdge[2];

    fin.ignore();
    getline(fin, dummy);
    fin >> par.epsilonLJ
        >> par.sigmaLJ
        >> par.interactionCutoffRadius;

    fin.ignore();
    getline(fin, dummy);
    fin >> par.propertyPrintingInterval
        >> par.numberRadialDistrPoints
        >> par.radialDistrCutoffRadius;

    fin.ignore();
    getline(fin, dummy);
    fin >> ntwxm
        >> ntpw
        >> par.trajectoryOutputInterval;

    par.xvInitialization = initialXVGeneratorFromInt(ntxi);
    par.finalXVOutput = finalCoordinateFileFormatFromInt(ntxo);
    par.trajectoryOutput = ntwxm > 0;
    par.trajectoryOutputFormat = trajectoryFileFormatFromInt(ntpw);
    par.mdType = simulationTypeFromInt(ntt);

    return par;
}

void ParameterIO::saveParameters(const std::string &fileName, const MDParameters &par) {
    ofstream fout;
    fout.open(fileName, std::ios::out);
    if (fout.bad())
        throw std::runtime_error("can't open " + fileName);
    outputParameters(fout, par);
}

void ParameterIO::outputParameters(std::ostream &out, const MDParameters &par) {
    const int fieldWidth = 27;
    std::string separation = "";
    std::string labelLinePrefix = "# ";

    out << labelLinePrefix
        << "Title" << endl
        << par.title << endl;

    out << separation << labelLinePrefix
        << setw(fieldWidth) << "NumberAtoms"
        << setw(fieldWidth) << "AtomicMass"
        << setw(fieldWidth) << "MDType"
        << endl << "  "
        << setw(fieldWidth) << par.numberAtoms
        << setw(fieldWidth) << par.atomicMass
        << setw(fieldWidth) << simulationTypeToInt(par.mdType)
        << endl;

    out << separation << labelLinePrefix
        << setw(fieldWidth) << "BoxSize(x)"
        << setw(fieldWidth) << "BoxSize(y)"
        << setw(fieldWidth) << "BoxSize(z)"
        << endl << "  "
        << setw(fieldWidth) << par.boxSize[0]
        << setw(fieldWidth) << par.boxSize[1]
        << setw(fieldWidth) << par.boxSize[2]
        << endl;

    out << separation << labelLinePrefix
        << setw(fieldWidth) << "NumberMDSteps"
        << setw(fieldWidth) << "InitialTime"
        << setw(fieldWidth) << "TimeStep"
        << endl << "  "
        << setw(fieldWidth) << par.numberMDSteps
        << setw(fieldWidth) << par.initialTime
        << setw(fieldWidth) << par.timeStep
        << endl;

    out << separation << labelLinePrefix
        << setw(fieldWidth) << "InitialTemperature"
        << setw(fieldWidth) << "TargetTemperature"
        << setw(fieldWidth) << "TemperatureCouplingTime"
        << endl << "  "
        << setw(fieldWidth) << par.initialTemperature
        << setw(fieldWidth) << par.targetTemperature
        << setw(fieldWidth) << par.temperatureCouplingTime
        << endl;

    out << separation << labelLinePrefix
        << setw(fieldWidth) << "RandomSeed"
        << endl << "  "
        << setw(fieldWidth) << par.randomSeed
        << endl;

    out << separation << labelLinePrefix
        << setw(fieldWidth) << "XVInitialization"
        << setw(fieldWidth) << "CoordInitializationSpread"
        << setw(fieldWidth) << "FinalXVOutput"
        << endl << "  "
        << setw(fieldWidth) << initialXVGeneratorToInt(par.xvInitialization)
        << setw(fieldWidth) << par.coordInitializationSpread
        << setw(fieldWidth) << finalCoordinateFileFormatToInt(par.finalXVOutput)
        << endl;

    out << separation << labelLinePrefix
        << setw(fieldWidth) << "NAtomsOnBoxEdge(x)"
        << setw(fieldWidth) << "NAtomsOnBoxEdge(y)"
        << setw(fieldWidth) << "NAtomsOnBoxEdge(z)"
        << endl << "  "
        << setw(fieldWidth) << par.numberAtomsOnBoxEdge[0]
        << setw(fieldWidth) << par.numberAtomsOnBoxEdge[1]
        << setw(fieldWidth) << par.numberAtomsOnBoxEdge[2]
        << endl;

    out << separation << labelLinePrefix
        << setw(fieldWidth) << "EpsilonLJ"
        << setw(fieldWidth) << "SigmaLJ"
        << setw(fieldWidth) << "InteractionCutoffRadius"
        << endl << "  "
        << setw(fieldWidth) << par.epsilonLJ
        << setw(fieldWidth) << par.sigmaLJ
        << setw(fieldWidth) << par.interactionCutoffRadius
        << endl;

    out << separation << labelLinePrefix
        << setw(fieldWidth) << "PropertyPrintingInterval"
        << setw(fieldWidth) << "NumberRadialDistrPoints"
        << setw(fieldWidth) << "RadialDistrCutoffRadius"
        << endl << "  "
        << setw(fieldWidth) << par.propertyPrintingInterval
        << setw(fieldWidth) << par.numberRadialDistrPoints
        << setw(fieldWidth) << par.radialDistrCutoffRadius
        << endl;

    out << separation << labelLinePrefix
        << setw(fieldWidth) << "TrajectoryOutput"
        << setw(fieldWidth) << "TrajectoryOutputFormat"
        << setw(fieldWidth) << "TrajectoryOutputInterval"
        << endl << "  "
        << setw(fieldWidth) << par.trajectoryOutput
        << setw(fieldWidth) << trajectoryFileFormatToInt(par.trajectoryOutputFormat)
        << setw(fieldWidth) << par.trajectoryOutputInterval
        << endl;

}
