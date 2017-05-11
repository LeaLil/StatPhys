//
// Created by mariond on 09.05.17.
//

#include "TotalPotential.h"


TotalPotential::TotalPotential(double r, double r0, bool angleterms, const MDParameters &par) : Potential(r, r0),
                                                                                                angleterms(angleterms),
                                                                                                par(par) {
    cov = new CovalentPotential(r, r0, par, angleterms);
    vdw = new LJPotential(r, r0, par.sigmaLJ, par.epsilonLJ);
    coul = new CoulombPotential(r, r0, 1, 1); //TO DO implement q1, q2 in MDParameters
}

double TotalPotential::computePotential() {
    return cov->computePotential() + vdw->computePotential() + coul->computePotential();
}

double TotalPotential::computeForceMagnitude() {
    return cov->computeForceMagnitude() + vdw->computeForceMagnitude() + coul->computeForceMagnitude();
}

