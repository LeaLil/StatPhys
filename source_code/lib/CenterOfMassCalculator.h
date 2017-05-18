#ifndef CENTEROFMASSCALCULATOR_H
#define CENTEROFMASSCALCULATOR_H

#include <vector>
#include "MDRunOutput.h"
#include "Molecule.h"

/*!
 * This class calculates the center of mass and its velocity.
 */
class CenterOfMassCalculator {
public:
    CenterOfMassCalculator(bool calculateCMPosition = true, bool calculateCMTranslation = true);

    void update(std::vector<Molecule> &moleculeList);

    void printResults(MDRunOutput &output);

private:
    void calculateCenterOfMassCoordinates(std::vector<Molecule> &moleculeList);

    void calculateVelocityAndKineticEnergy(std::vector<Molecule> &moleculeList);

    Point averageVelocity;
    Point centerOfMass;


    double totalMass;
    double ekcm;
    bool calculatePosition;
    bool calculateTranslation;
};

#endif // CENTEROFMASSCALCULATOR_H