//
// Created by lea on 08.05.17.
//

#include "HarmonicPotential.h"

double HarmonicPotential::computePotential() {
    return (1./2.) * kr * (r - r0) * (r-r0);
}

HarmonicPotential::HarmonicPotential(double kr, double r, double r0) : Potential(r, r0) {
    this->kr = kr;
}


double HarmonicPotential::computeForceMagnitude() {
    return 0.0;
}