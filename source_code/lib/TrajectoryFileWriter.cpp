#include "TrajectoryFileWriter.h"
#include "BinaryIO.h"
#include "CoordinatesAndVelocitiesInitializer.h" // For MAXTITLE value
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <iomanip>

using namespace std;

TrajectoryFileWriter::TrajectoryFileWriter(const MDParameters &parameters,
                                           std::string finalCoordFilename,
                                           std::string trajFilename)
        : par(parameters),
          finalCoordinatesFilename(finalCoordFilename),
          trajectoryCoordinatesFilename(trajFilename) {
}

void TrajectoryFileWriter::writeBeforeRun() {
    ofstream fout1; // trajectory output
    if (par.trajectoryOutput) {
        fout1.open(trajectoryCoordinatesFilename, ios::out);
        if (fout1.bad()) {
            throw std::runtime_error("can't open " + trajectoryCoordinatesFilename);
        }
        fout1 << par.title << endl;
    }
}

void TrajectoryFileWriter::writeFinalCoordinates(std::vector<Molecule> &moleculeList){
    if (par.finalXVOutput == FinalCoordinateFileFormat::ascii) {
        writeFinalCoordinatesInAsciiForm(moleculeList);
    } else {
        writeFinalCoordinatesInBinaryForm(moleculeList);
    }
}

void TrajectoryFileWriter::writeFinalCoordinatesInBinaryForm(std::vector<Molecule> &moleculeList) {
    ofstream fout2;
    fout2.open(finalCoordinatesFilename, ios::out | ios::binary);
    if (fout2.bad()) {
        throw std::runtime_error("can't open " + finalCoordinatesFilename);
    }
    fout2.write(par.title.c_str(), MAXTITLE);
    for ( Molecule &m: moleculeList) {
        for (Element &e: m.elementList) {

            BinaryIO::write(fout2, e.position.getAsArray());
            BinaryIO::write(fout2, e.velocityVector.getAsArray());
        }
    }
}

void TrajectoryFileWriter::writeFinalCoordinatesInAsciiForm(std::vector<Molecule> &moleculeList) {
    ofstream fout2;
    fout2.open(finalCoordinatesFilename, ios::out);
    if (fout2.bad()) {
        throw std::runtime_error("can't open " + finalCoordinatesFilename);
    }
    fout2 << par.title << "\n";
    fout2 << par.numberAtoms << "\n";

    for (Molecule &m : moleculeList) {
        for (Element &element: m.elementList) {
            fout2 << setw(15) << element.position.x;
            fout2 << setw(15) << element.position.y;
            fout2 << setw(15) << element.position.z;


            fout2 << setw(15) << element.velocityVector.x;
            fout2 << setw(15) << element.velocityVector.y;
            fout2 << setw(15) << element.velocityVector.z;


            fout2 << "\n";
        }
    }
}

void TrajectoryFileWriter::writeOutTrajectoryStep(std::vector<Molecule> &positions) {
    if (par.trajectoryOutput) {

        for (Molecule &m: positions) {
            for (Element &e: m.elementList) {
                if (par.trajectoryOutputFormat == TrajectoryFileFormat::binary) {
                    writeOutTrajectoryStepInBinaryForm(e.position);
                } else if (par.trajectoryOutputFormat == TrajectoryFileFormat::ascii) {
                    writeOutTrajectoryStepInAsciiForm(e.position);
                }
            }
        }
    }
}

void TrajectoryFileWriter::writeOutTrajectoryStepInBinaryForm(Point &point) {
    ofstream fileBW;
    fileBW.open(trajectoryCoordinatesFilename, ios::out | ios::app | ios::binary);
    if (fileBW.bad()) {
        throw runtime_error("I/O ERROR: cannot write to file: " + trajectoryCoordinatesFilename);
    }
    BinaryIO::write(fileBW, point.getAsArray());
}

void TrajectoryFileWriter::writeOutTrajectoryStepInAsciiForm(Point& point) {
    ofstream fileFW;
    fileFW.open(trajectoryCoordinatesFilename, ios::out | ios::app);
    if (fileFW.bad()) {
        throw runtime_error("I/O ERROR: cannot write to file: " + trajectoryCoordinatesFilename);
    }
    /*
    int ntot = 3 * par.numberAtoms;
    for (int i = 0; i < ntot; i += 10) {
        for (int j = i; (j < i + 10 && j < ntot); j++) {
            fileFW << setw(10) << positions[j];
        }
        fileFW << endl;
    }
     */
}
