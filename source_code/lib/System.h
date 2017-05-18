//
// Created by lea on 17.05.17.
//

#ifndef MDATOM_SYSTEM_H
#define MDATOM_SYSTEM_H


#include "MDParameters.h"
#include "Point.h"

class System {
public:

    double totalPotentialEnergy;
    double totalKineticEnergy;
    double oldTotalKineticEnergy;
    double virial;
    double totalTotalEnergy;

    double cutoffRadiusSquared;

    MDParameters* mdParameters;


    Point boxLength;

    bool isOutOfRadius(double r);
};


#endif //MDATOM_SYSTEM_H
