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
    rcutf2 = par.interactionCutoffRadius * par.interactionCutoffRadius;
    for (int m = 0; m < 3; m++)
        inverseBoxLength[m] = 1.0 / par.boxSize[m];
}

void InteractionCalculator::calculate(const std::vector<double> &positions, std::vector<double> &forces,
                                      std::vector<Molecule> &moleculeList) {
    potentialEnergy = 0;
    radialDistribution.setZero();
    //TODO: Interactions for molecules:
    for (int i = 0; i < moleculeList.size(); i++) {
        for (int j = i + 1; j < moleculeList.size(); j++) {
            potentialEnergy += moleculeList[i].calculateInteraction(moleculeList[j], par, radialDistribution);
        }
    }


}


double InteractionCalculator::getPotentialEnergy() const {
    return potentialEnergy;
}

const InstantaneousRadialDistribution &InteractionCalculator::getInstantaneousRadialDistribution() const {
    return radialDistribution;
}
