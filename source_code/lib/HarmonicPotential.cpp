//
// Created by lea on 08.05.17.
//

#include "HarmonicPotential.h"

double HarmonicPotential::computePotential() {
    return (1./2.) * kr * (r - r0) * (r-r0);
}

HarmonicPotential::HarmonicPotential(double r, double r0, double kr) : Potential(r) {
    this->r0 = r0;
    this->kr = kr;
}


double HarmonicPotential::computeForceMagnitude() {
    return - kr * (r-r0);
}

