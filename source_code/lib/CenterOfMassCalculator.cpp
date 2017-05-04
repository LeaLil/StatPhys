#include "CenterOfMassCalculator.h"
#include <cmath>

CenterOfMassCalculator::CenterOfMassCalculator(bool calculateCMPosition, bool calculateCMTranslation)
  :  calculatePosition(calculateCMPosition),
     calculateTranslation(calculateCMTranslation) {
}

void CenterOfMassCalculator::update(int numberAtoms, const std::vector<double>& positions,
                                    const std::vector<double>& velocities, double atomicMass) {
    totalMass = numberAtoms * atomicMass;

    if (calculatePosition) {
        calculateCenterOfMassCoordinates(numberAtoms, positions, atomicMass);
    }

    if (calculateTranslation) {
        calculateVelocityAndKineticEnergy(numberAtoms, velocities, atomicMass);
    }
}

void CenterOfMassCalculator::calculateVelocityAndKineticEnergy(int numberAtoms, const std::vector<double>& velocities,
                                                               double atomicMass) {
    ekcm = 0;
    for (int m = 0; m < 3; m++)
        vcm[m] = 0.;

    for (int j = 0; j < 3 * numberAtoms; j += 3) {
        for (int m = 0; m < 3; m++)
            vcm[m] += atomicMass * velocities[j + m];
    }
    for (int m = 0; m < 3; m++) {
        vcm[m] /= totalMass;
        ekcm += vcm[m] * vcm[m];
    }
    ekcm *= (totalMass / 2.);
}

void CenterOfMassCalculator::calculateCenterOfMassCoordinates(int numberAtoms, const std::vector<double>& positions,
                                                              double atomicMass) {
    for (int m = 0; m < 3; m++)
        xcm[m] = 0.;

    for (int j = 0; j < 3 * numberAtoms; j += 3) {
        for (int m = 0; m < 3; m++)
            xcm[m] += atomicMass * positions[j + m];
    }
    for (int m = 0; m < 3; m++)
        xcm[m] /= totalMass;
}

void CenterOfMassCalculator::printResults(MDRunOutput &output) {
    if (calculatePosition) {
        output.printCenterOfMassAndCoordinates(totalMass, xcm);
        if (calculateTranslation) {
            output.printCenterOfMassTranslation(vcm, ekcm);
        }
    }
}

void CenterOfMassCalculator::getPosition(double *x) const {
    for (int i = 0; i < 3; ++i)
        x[i] = xcm[i];
}

void CenterOfMassCalculator::getVelocity(double *v) const {
    for (int i = 0; i < 3; ++i)
        v[i] = vcm[i];
}

double CenterOfMassCalculator::getKineticEnergy() const {
    return ekcm;
}


