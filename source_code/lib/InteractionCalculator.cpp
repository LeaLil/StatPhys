#include "InteractionCalculator.h"
#include "LJPotential.h"
#include "HarmonicPotential.h"
#include "MorsePotential.h"
#include "TotalPotential.h"
#include "Molecule.h"
#include <cmath>

inline int nearestInteger(double x) {
    return x > 0 ? static_cast<int>(x + 0.5) : static_cast<int>(x - 0.5);
}

InteractionCalculator::InteractionCalculator(const MDParameters &parameters)
        : par(parameters),
          radialDistribution(parameters.numberRadialDistrPoints, parameters.radialDistrCutoffRadius) {
    initializeValues();
}

void InteractionCalculator::initializeValues() {

}

void InteractionCalculator::calculate(const std::vector<double> &positions, std::vector<double> &forces,
                                      std::vector<Molecule> &moleculeList) {
    potentialEnergy = 0;
    radialDistribution.setZero();
    for (int i = 0; i < moleculeList.size(); i++) {
        for (int j = i + 1; j < moleculeList.size(); j++) {
            potentialEnergy += moleculeList[i].calculateInter(moleculeList[j], par,
                                                              radialDistribution);
        }
        potentialEnergy += moleculeList[i].calculateIntra(par, radialDistribution);
    }
}


double InteractionCalculator::getPotentialEnergy() const {
    return potentialEnergy;
}

const InstantaneousRadialDistribution &InteractionCalculator::getInstantaneousRadialDistribution() const {
    return radialDistribution;
}
