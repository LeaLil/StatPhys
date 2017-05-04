#ifndef RADIALDISTRIBUTION_H
#define RADIALDISTRIBUTION_H

#include <algorithm>
#include <vector>

/*!
 * This class describes some radial probability distribution.
 * It is the base class for AveragedRadialDistribution and InstantaneousRadialDistribution.
 */
class RadialDistribution {
  public:
    RadialDistribution(int numberOfPoints, double cutoffRadius)
      : numberIntervals(numberOfPoints),
        maximalDistance(cutoffRadius),
        squaredMaximalDistance(cutoffRadius*cutoffRadius),
        radialCount(numberOfPoints, 0),
        binSize(cutoffRadius / numberOfPoints) {
    }

    void setZero() {
        std::fill(radialCount.begin(), radialCount.end(), 0);
    }

    int getNumberBins() const {
        return numberIntervals;
    }

    double getBinSize() const {
        return binSize;
    }

  protected:
    const int numberIntervals;
    const double maximalDistance;
    const double squaredMaximalDistance;
    const double binSize;
    std::vector<int> radialCount;
};

#endif // RADIALDISTRIBUTION_H
