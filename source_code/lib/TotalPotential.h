//
// Created by mariond on 09.05.17.
//

#ifndef MDATOM_TOTALPOTENTIAL_H
#define MDATOM_TOTALPOTENTIAL_H


#include "Potential.h"
#include "LJPotential.h"
#include "CoulombPotential.h"
#include "CovalentPotential.h"

class TotalPotential : public Potential {

public:
    bool angleterms;
    Potential *vdw;
    Potential *coul;
    Potential *cov;
    MDParameters par;

    TotalPotential(double r, bool useAngleTerms, const MDParameters &par);

    double computePotential() override;

    double computeForceMagnitude() override;

    virtual ~TotalPotential();


};


#endif //MDATOM_TOTALPOTENTIAL_H
