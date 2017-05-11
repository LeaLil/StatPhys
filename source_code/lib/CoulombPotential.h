//
// Created by mariond on 09.05.17.
//

#ifndef MDATOM_COULOMBPOTENTIAL_H
#define MDATOM_COULOMBPOTENTIAL_H


#include "Potential.h"

class CoulombPotential : public Potential {

public:
    double q1;
    double q2;

    // k_c = 1/4*pi*e_0; using electric field constant e_0 in C²/Nm² wrong?
    // TO DO find correct values and dimensions: nm, ps, e...
    double k_c = 1;

    CoulombPotential(double r, double r0, double q1, double q2);

    double computePotential() override;

    double computeForceMagnitude() override;



};


#endif //MDATOM_COULOMBPOTENTIAL_H
