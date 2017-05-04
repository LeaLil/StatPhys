#include "InstantaneousRadialDistribution.h"
#include <cmath>


InstantaneousRadialDistribution::InstantaneousRadialDistribution(int numberOfPoints, double cutoffRadius)
  : RadialDistribution(numberOfPoints, cutoffRadius) {
}


void InstantaneousRadialDistribution::addPairAtDistance(double r) {
    if (r < maximalDistance) {
        addPair(r);
    }
}

void InstantaneousRadialDistribution::addPairAtSquaredDistance(double r2) {
    if (r2 < squaredMaximalDistance) {
        double r = std::sqrt(r2); // Inter-particle distance
        addPair(r);
    }
}

void InstantaneousRadialDistribution::addPair(double dist) {
    int n = static_cast<int>(dist / binSize);
    n = (n > numberIntervals) ? numberIntervals : n;
    radialCount[n]++;
}
