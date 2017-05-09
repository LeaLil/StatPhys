//
// Created by mariond on 09.05.17.
//

#include "TorsionPotential.h"



TorsionPotential::TorsionPotential(double r, double r0, double omega, double gamma) : Potential(r, r0), omega(omega), gamma(gamma) {}

double TorsionPotential::computePotential(){
    return 0;
};

double TorsionPotential::computeForceMagnitude() {
    return 0;
} ;
