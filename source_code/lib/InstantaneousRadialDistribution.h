#ifndef INSTANTANEOUSRADIALDISTRIBUTION_H
#define INSTANTANEOUSRADIALDISTRIBUTION_H

#include "RadialDistribution.h"
#include <assert.h>
#include <vector>

/*!
 * This class represents an instantaneous radial probability distribution for some frozen state of the system.
 */
class InstantaneousRadialDistribution : public RadialDistribution {
  public:
    InstantaneousRadialDistribution(int numberOfPoints, double cutoffRadius);
    void addPairAtDistance(double r);
    void addPairAtSquaredDistance(double r2);
    int getCount(int intervalIndex) const;

  private:
    void addPair(double dist);
};

inline int InstantaneousRadialDistribution::getCount(int intervalIndex) const {
    assert(intervalIndex >= 0 && intervalIndex < numberIntervals);
    return radialCount[intervalIndex];
}


#endif // INSTANTANEOUSRADIALDISTRIBUTION_H
