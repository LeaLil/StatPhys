//
// Created by mariond on 09.05.17.
//

#ifndef MDATOM_TOTALPOTENTIAL_H
#define MDATOM_TOTALPOTENTIAL_H


#include "Potential.h"
#include "LJPotential.h"
#include "CoulombPotential.h"
#include "CovalentPotential.h"

class TotalPotential : Potential {

public:
    bool angleterms;
    LJPotential *vdw;
    CoulombPotential *coul;
    CovalentPotential *cov;
    MDParameters par;

    TotalPotential(double r, double r0, bool angleterms, const MDParameters &par);

    double computePotential() override;

    double computeForceMagnitude() override;


};


#endif //MDATOM_TOTALPOTENTIAL_H
