//
// Created by mariond on 09.05.17.
//

#ifndef MDATOM_COULOMBPOTENTIAL_H
#define MDATOM_COULOMBPOTENTIAL_H


#include "Potential.h"
#define _USE_MATH_DEFINES

#include <math.h>

class CoulombPotential : public Potential {

public:
    double q1;
    double q2;

    // TODO find correct values and dimensions: nm, ps, e...
    double e_0 = 8.85418782e-12; //in SI
    double k_c = 1./4*M_PI*1745.914*e_0;     //in e, ps, nm, u:


    CoulombPotential(double r, double q1, double q2);

    double computePotential() override;

    double computeForceMagnitude() override;



};


#endif //MDATOM_COULOMBPOTENTIAL_H
