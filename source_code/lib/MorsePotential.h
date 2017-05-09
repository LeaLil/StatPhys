//
// Created by lea on 09.05.17.
//

#ifndef MDATOM_MORSEPOTENTIAL_H
#define MDATOM_MORSEPOTENTIAL_H


#include "Potential.h"

class MorsePotential : public Potential{
public:
    MorsePotential(double r, double r0, double d_e, double a);

    double d_e;
    double a; //a = sqrt(kr/2d_e)

    double computePotential() override;

    double computeForceMagnitude() override ;
};


#endif //MDATOM_MORSEPOTENTIAL_H
