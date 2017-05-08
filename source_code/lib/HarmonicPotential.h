//
// Created by lea on 08.05.17.
//

#ifndef MDATOM_HARMONICPOTENTIAL_H
#define MDATOM_HARMONICPOTENTIAL_H


#include "Potential.h"

class HarmonicPotential : public Potential {
public:
    double kr;

    HarmonicPotential(double kr, double r, double r0);

    double computePotential() override;


    double computeForceMagnitude() override;


};


#endif //MDATOM_HARMONICPOTENTIAL_H
