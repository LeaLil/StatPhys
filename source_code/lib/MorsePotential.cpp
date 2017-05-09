//
// Created by lea on 09.05.17.
//

#include "MorsePotential.h"
#include <math.h>

MorsePotential::MorsePotential(double r, double r0, double d_e, double a) : Potential(r, r0), d_e(d_e), a(a) {}

// calculate potential
double MorsePotential::computePotential() {

    return d_e * pow((1 - exp(-a * (r-r0))), 2);

};

//calculate force = - derivative of potential

double MorsePotential::computeForceMagnitude() {
    return 2 * a * d_e * exp(a * (r0 - r)) * (exp(a * (r0 - r)) - 1 );
} ;