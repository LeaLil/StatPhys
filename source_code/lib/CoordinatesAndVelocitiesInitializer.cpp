#include "CoordinatesAndVelocitiesInitializer.h"
#include "BinaryIO.h"
#include "RandomNumberGenerator.h"
#include <cmath>
#include <stdexcept>

CoordinatesAndVelocitiesInitializer::CoordinatesAndVelocitiesInitializer(MDRunOutput& mdOutput, const MDParameters &parameters, std::string coordinatesFileName)
  : output(mdOutput),
    par(parameters),
    fileName(coordinatesFileName) {
}

void CoordinatesAndVelocitiesInitializer::initialize(std::vector<double>& positions, std::vector<double>& velocities) {
    output.printXVInitializationHeader();

    if (par.xvInitialization != InitialXVGenerator::generateInitialX) {
        fin.open(fileName, std::ios::in);
        if (fin.bad()) {
            throw std::runtime_error("can't open " + fileName);
        }
    }

    int nat3 = 3 * par.numberAtoms;
    positions.resize(nat3);
    velocities.resize(nat3);

    char title1_carray [MAXTITLE];
    std::string title1;
    switch (par.xvInitialization) {
        case InitialXVGenerator::generateInitialX:
            generateAtomicConfiguration(positions);
            output.printXInitializationWithLattice();
            for (int j3 = 0; j3 < nat3; j3++) {
                velocities[j3] = 0;
            }
            break;

        case InitialXVGenerator::xFromAscii:
            getline(fin,title1);
            int natom;
            fin >> natom;
            output.printCoordinateFileTitle(title1);
            fin.get();
            if (natom < par.numberAtoms) {
                throw std::runtime_error("NATOM (" + fileName + ") = " + std::to_string(natom) + " < NAT");
            }

            for (int j3 = 0; j3 < nat3; j3 += 3) {
                for (int m = 0; m < 3; m++) {
                    fin >> positions[j3 + m];
                }
            }
            fin.get();
            for (int j3 = 0; j3 < nat3; j3++) {
                velocities[j3] = 0;
            }
            break;

        case InitialXVGenerator::xFromBinary:
            fin.read(title1_carray, MAXTITLE);
            title1 = title1_carray;
            output.printCoordinateFileTitle(title1);
            BinaryIO::read(fin, positions);
            for (int j3 = 0; j3 < nat3; j3++)
                velocities[j3] = 0;
            break;

        case InitialXVGenerator::xvFromAscii:
            getline(fin,title1);
            output.printCoordinateFileTitle(title1);
            fin >> natom;
            fin.get();
            if (natom < par.numberAtoms) {
                throw std::runtime_error("NATOM (" + fileName + ") = " + std::to_string(natom) + " < NAT");
            }
            for (int j3 = 0; j3 < nat3; j3 += 3) {
                int atomNumber;
                fin >> atomNumber;
                for (int m = 0; m < 3; m++) {
                    fin >> positions[j3 + m];
                }
                for (int m = 0; m < 3; m++) {
                    fin >> velocities[j3 + m];
                }
            }
            fin.get();
            break;

        case InitialXVGenerator::xvFromBinary:
            fin.read(title1_carray, MAXTITLE);
            title1 = title1_carray;
            output.printCoordinateFileTitle(title1);
            BinaryIO::read(fin, positions);
            BinaryIO::read(fin, velocities);
            break;
    }

    /*
     * take the velocities from a maxwellian, when required
     */
    if (par.initialTemperature >= 1e-6) {
        output.printVInitializationWithMaxwellianDistribution();
        const double boltzmannConstant = 8.3144598e-3; // units: K^-1 ps^-2 u nm^2
        double sd = sqrt(boltzmannConstant * par.initialTemperature / par.atomicMass);
        for (int j3 = 0; j3 < nat3; j3++) {
            velocities[j3] = RandomNumberGenerator::gauss(0.0, sd);
        }
    }
}

void CoordinatesAndVelocitiesInitializer::generateAtomicConfiguration(std::vector<double>& positions) {
    /*
        This function puts nat = nbox(1)*nbox(2)*nbox(3) atoms on a periodic lattice, such that nbox(m) atoms will lie along each side (m=1..3) of length box(m).
        The box lies in the positive quadrant with respect to an origin latticeOrigin(1..3), here initialized to zero.
        Uniformly distributed random displacements of maximum size coordInitializationSpread/2 are be added to the atomic positions in each direction.
     */

    double latticeOrigin[3];
    double atomSeparation[3];
    int index[3];

    /*
     * initialise variables
     */
    for (int m = 0; m < 3; m++)
        latticeOrigin[m] = 0;
    for (int m = 0; m < 3; m++)
        atomSeparation[m] = par.boxSize[m] / par.numberAtomsOnBoxEdge[m];

    /*
     * put the atoms on a lattice and add random displacements
     */
    int atomIndex = 0;
    for (int nx = 0; nx < par.numberAtomsOnBoxEdge[0]; nx++) {
        index[0] = nx + 1;
        for (int ny = 0; ny < par.numberAtomsOnBoxEdge[1]; ny++) {
            index[1] = ny + 1;
            for (int nz = 0; nz < par.numberAtomsOnBoxEdge[2]; nz++) {
                index[2] = nz + 1;
                // return if the coordinates of all atoms have been set
                if (atomIndex >= par.numberAtoms)
                    return;
                for (int m = 0; m < 3; m++) {
                    double rand = RandomNumberGenerator::uniform();
                    double randomDisplacement = (rand - 0.5) * par.coordInitializationSpread;
                    positions[3 * atomIndex + m] = latticeOrigin[m] + index[m] * atomSeparation[m] + randomDisplacement;
                }
                atomIndex++;
            }
        }
    }
}

