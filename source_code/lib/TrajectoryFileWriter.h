#ifndef TRAJECTORYFILEWRITER_H
#define TRAJECTORYFILEWRITER_H

#include "MDParameters.h"
#include "Molecule.h"
#include <string>
#include <vector>

/*!
 * This class is responsible for writing out the atom coordinates during a MD simulation.
 */
class TrajectoryFileWriter {
  public:
    TrajectoryFileWriter(const MDParameters& parameters,
                         std::string finalCoordFilename,
                         std::string trajFilename);
    void writeBeforeRun();
    void writeFinalCoordinates(std::vector<Molecule>& moleculeLIst);
    void writeOutTrajectoryStep(std::vector<Molecule>& moleculeLIst);

  private:
    void writeFinalCoordinatesInBinaryForm(std::vector<Molecule>& moleculeLIst);
    void writeFinalCoordinatesInAsciiForm(std::vector<Molecule>& moleculeLIst);
    void writeOutTrajectoryStepInBinaryForm(Point& p);
    void writeOutTrajectoryStepInAsciiForm(Point& point);

    const MDParameters& par;
    const std::string finalCoordinatesFilename;
    const std::string trajectoryCoordinatesFilename;
};

#endif // TRAJECTORYFILEWRITER_H
