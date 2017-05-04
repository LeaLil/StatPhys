#ifndef COORDINATESANDVELOCITIESINITIALIZER_H
#define COORDINATESANDVELOCITIESINITIALIZER_H

#include "MDParameters.h"
#include "MDRunOutput.h"
#include <string>
#include <fstream>
#include <vector>
const int MAXTITLE = 200; /* Maximum number of characters for file titles */

/*!
 * This class initializes the coordinates and the velocities from the specifications in the parameters and, optionally, a file.
 * When no coordinate file is needed, coordinatesFileName can be an empty string.
 */
class CoordinatesAndVelocitiesInitializer {
  public:
    CoordinatesAndVelocitiesInitializer(MDRunOutput& mdOutput, const MDParameters& parameters, std::string coordinatesFileName);
    void initialize(std::vector<double>& positions, std::vector<double>&velocities);

  private:
    void generateAtomicConfiguration(std::vector<double>& positions);

    MDRunOutput& output;
    const MDParameters& par;
    std::string fileName;
    std::ifstream fin;
};

#endif // COORDINATESANDVELOCITIESINITIALIZER_H