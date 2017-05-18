#include "CenterOfMassCalculator.h"
#include "Molecule.h"
#include <cmath>
#include <vector>

CenterOfMassCalculator::CenterOfMassCalculator(bool calculateCMPosition, bool calculateCMTranslation)
  :  calculatePosition(calculateCMPosition),
     calculateTranslation(calculateCMTranslation) {
}

void CenterOfMassCalculator::update(std::vector<Molecule>& moleculeList) {

    totalMass = 0;
    for(Molecule& m : moleculeList){
        for(Element&e : m.elementList) {
            totalMass += e.weight;
        }
    }

    if (calculatePosition) {
        calculateCenterOfMassCoordinates(moleculeList);
    }

    if (calculateTranslation) {
        calculateVelocityAndKineticEnergy(moleculeList);
    }
}

void CenterOfMassCalculator::calculateVelocityAndKineticEnergy(std::vector<Molecule>& moleculeList) {
    ekcm = 0;

    averageVelocity = Point(0,0,0);

    for(Molecule& m : moleculeList) {
        for(Element& e: m.elementList) {
            averageVelocity += e.velocityVector * e.weight;
        }
    }
    averageVelocity = averageVelocity * (1./totalMass);
    ekcm += averageVelocity * averageVelocity * totalMass * 0.5;
}

void CenterOfMassCalculator::calculateCenterOfMassCoordinates(std::vector<Molecule>& moleculeList) {
    centerOfMass = Point(0,0,0);

    for(Molecule& m : moleculeList) {
        for(Element& e: m.elementList) {
            centerOfMass += e.position * e.weight;
        }
    }
    centerOfMass *= (1./totalMass);
}

void CenterOfMassCalculator::printResults(MDRunOutput &output) {
    if (calculatePosition) {
        double t[3] = {centerOfMass.x, centerOfMass.y, centerOfMass.z};
        output.printCenterOfMassAndCoordinates(totalMass,t);
        if (calculateTranslation) {
            double v[3] = {averageVelocity.x, averageVelocity.y, averageVelocity.z};
            output.printCenterOfMassTranslation(v, ekcm);
        }
    }
}
