//
// Created by lea on 08.05.17.
//

#include "LJPotential.h"
#include "MDParameters.h"

#include <math.h>


LJPotential::LJPotential(double r, double sigma, double epsilon) : Potential(r), sigma(sigma), epsilon(epsilon) {}


double LJPotential::computePotential() {

    double r6 = 1./pow(r,6);
    double sigma6 = pow(sigma, 6);

    double r12 = r6 * r6;
    double sigma12 = sigma6 * sigma6;

    potential = 4.0 * epsilon * ((sigma12 * r12) - (sigma6 * r6));
    return potential;
}

/*
 * Kraft ist grundsätzlich die Ableitung des Potentials... Bei JL ist dies:
   f_x = 4epsilon [12(sigma/r)^12 + 6 (sigma/r)^6] * 1/r^2
 *
 */
double LJPotential::computeForceMagnitude() {
    return 4 * epsilon * (12 * pow((sigma/r), 12) - 6*pow((sigma/r),6))*1.0/(r*r);
}
