//
// Created by mariond on 09.05.17.
//

#ifndef MDATOM_COVALENTPOTENTIAL_H
#define MDATOM_COVALENTPOTENTIAL_H


#include "Potential.h"
#include "HarmonicPotential.h"
#include "TorsionPotential.h"
#include "MDParameters.h"

class CovalentPotential : public Potential{

public:
    bool withangle;

    HarmonicPotential *bonds;
    HarmonicPotential *angles;
    TorsionPotential *dihedral;
    MDParameters par;

    CovalentPotential(double r, MDParameters par, bool withangle);

    double computePotential() override;

    double computeForceMagnitude() override;

    virtual ~CovalentPotential();


};


#endif //MDATOM_COVALENTPOTENTIAL_H
