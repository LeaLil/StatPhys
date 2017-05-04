#ifndef MDRUNOUTPUT_H
#define MDRUNOUTPUT_H

#include <string>
#include <iostream>
#include "MDParameters.h"
#include "Timer.h"
#include <array>

/*!
 * This class takes care of the output of the simulation.
 * The constructor takes a std::ostream that can be, for instance, a std::ofstream, or std::cout.
 */
class MDRunOutput {
    static const int numberProperties = 6;

  public:
    using PropertyArray = std::array<double, numberProperties>;

    explicit MDRunOutput(std::ostream& outputStream);

    void printHeader();
    void printParameters(const MDParameters &parameters);
    void printXVInitializationHeader();
    void printXInitializationWithLattice();
    void printVInitializationWithMaxwellianDistribution();
    void printCoordinateFileTitle(const std::string& title);
    void printInitialTemperature(double temperature);
    void printIterationStart();
    void printPropertiesHeader();
    void printProperties(int nstep, double time, const PropertyArray& properties);
    void printAverages(int nstlim, double time, const PropertyArray& averages);
    void printRMSFluctuations(int nstlim, double time, const PropertyArray& fluctuations);
    void printAverageAndRMSTemperature(double average, double rmsFluctuation);
    void printCenterOfMassAndCoordinates(double totalMass, double centerOfMass[]);
    void printCenterOfMassTranslation(double velocity[], double kineticEnergy);
    void printTiming(const Timer& timer);
    void printRadialDistribution(int nPoints, double binSize, double points[]);

  private:
    std::ostream& out;
};

#endif // MDRUNOUTPUT_H