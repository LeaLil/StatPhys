//
// Created by mariond on 09.05.17.
//

#ifndef MDATOM_TORSIONPOTENTIAL_H
#define MDATOM_TORSIONPOTENTIAL_H


#include "Potential.h"

class TorsionPotential : public Potential {

public:

    double omega;
    double equilibriumAngle; //equilibriumAngle

    TorsionPotential(double r, double omega, double equilibriumAngle);

    double computePotential() override;

    double computeForceMagnitude() override ;

};


#endif //MDATOM_TORSIONPOTENTIAL_H
