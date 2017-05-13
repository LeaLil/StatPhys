//
// Created by mariond on 09.05.17.
//

#include "TorsionPotential.h"

//Gamma is equilibriumAngle

TorsionPotential::TorsionPotential(double r, double omega, double equilibriumAngle) : Potential(r), omega(omega), equilibriumAngle(equilibriumAngle) {}

double TorsionPotential::computePotential(){
    return 0;
};

double TorsionPotential::computeForceMagnitude() {
    return 0;
} ;
