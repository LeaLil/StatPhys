//
// Created by mariond on 09.05.17.
//

#include "CoulombPotential.h"
#include <math.h>


CoulombPotential::CoulombPotential(double r, double q1, double q2) : Potential(r), q1(q1), q2(q2) {}

double CoulombPotential::computePotential() {

    //double radius = r * pow(10, -9);
    //double q1c = q1 / (1.6021 * pow(10, -19));
    //double q2c = q2 / (1.6021 * pow(10, -19));

   //return k_c * q1 * q2 * (1/r);
   return 0;
};

double CoulombPotential::computeForceMagnitude() {
    return k_c * q1 * q2 * (1/r) * (1/r);
};