//
// Created by mariond on 09.05.17.
//

#ifndef MDATOM_TORSIONPOTENTIAL_H
#define MDATOM_TORSIONPOTENTIAL_H


#include "Potential.h"

class TorsionPotential : public Potential {

public:

    double omega;
    double gamma;

    TorsionPotential(double r, double r0, double omega, double gamma);

    double computePotential() override;

    double computeForceMagnitude() override ;

};


#endif //MDATOM_TORSIONPOTENTIAL_H
