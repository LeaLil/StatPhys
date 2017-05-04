#ifndef AVERAGEDRADIALDISTRIBUTION_H
#define AVERAGEDRADIALDISTRIBUTION_H

#include "RadialDistribution.h"
#include "InstantaneousRadialDistribution.h"

/*!
 * This class allows to average a radial distribution from multiple InstantaneousRadialDistribution's.
 */
class AveragedRadialDistribution : public RadialDistribution {
  public:
    AveragedRadialDistribution(int numberOfPoints, double cutoffRadius);

    void addInstantaneousDistribution(const InstantaneousRadialDistribution& distr);
    std::vector<double> calculateNormalizedDistribution(int numberAtoms, double boxVolume) const;

  private:
    int numberTimeSteps = 0;
};

#endif // AVERAGEDRADIALDISTRIBUTION_H
