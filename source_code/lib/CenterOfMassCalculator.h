#ifndef CENTEROFMASSCALCULATOR_H
#define CENTEROFMASSCALCULATOR_H

#include <vector>
#include "MDRunOutput.h"

/*!
 * This class calculates the center of mass and its velocity.
 */
class CenterOfMassCalculator {
  public:
    CenterOfMassCalculator(bool calculateCMPosition = true, bool calculateCMTranslation = true);
    void update(int numberAtoms, const std::vector<double> &positions, const std::vector<double> &velocities, double atomicMass);
    void printResults(MDRunOutput& output);
    void getPosition(double x[]) const;
    void getVelocity(double v[]) const;
    double getKineticEnergy() const;

  private:
    void calculateCenterOfMassCoordinates(int numberAtoms, const std::vector<double>& positions, double atomicMass);
    void calculateVelocityAndKineticEnergy(int numberAtoms, const std::vector<double>& velocities, double atomicMass);

    double totalMass;
    double ekcm;
    double xcm[3];
    double vcm[3];
    bool calculatePosition;
    bool calculateTranslation;
};

#endif // CENTEROFMASSCALCULATOR_H