//
// Created by lea on 08.05.17.
//

#ifndef MDATOM_HARMONICPOTENTIAL_H
#define MDATOM_HARMONICPOTENTIAL_H


#include "Potential.h"

class HarmonicPotential : public Potential {
public:
    double kr;
    double r0;

    HarmonicPotential(double r, double r0, double kr);

    double computePotential() override;


    double computeForceMagnitude() override;


};


#endif //MDATOM_HARMONICPOTENTIAL_H
