//
// Created by mariond on 09.05.17.
//

#include "TotalPotential.h"
#include "MorsePotential.h"


TotalPotential::TotalPotential(double r, bool useAngleTerms, const MDParameters &par) : Potential(r), angleterms(useAngleTerms),
                                                                                                par(par) {
    cov = new CovalentPotential(r, par, useAngleTerms);
   // vdw = new LJPotential(r, par.sigmaLJ, par.epsilonLJ);
    vdw = new MorsePotential(r, par.equilibriumDistance, par.dissociationEnergy, par.inflexibility);
    coul = new CoulombPotential(r, 1, 1); //TODO implement q1, q2
}

double TotalPotential::computePotential() {
    return cov->computePotential() + vdw->computePotential() + coul->computePotential();
}

double TotalPotential::computeForceMagnitude() {
    return cov->computeForceMagnitude() + vdw->computeForceMagnitude() + coul->computeForceMagnitude();
}

TotalPotential::~TotalPotential() {
    delete cov;
    delete vdw;
    delete coul;

}
