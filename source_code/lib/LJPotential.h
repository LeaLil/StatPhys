//
// Created by lea on 08.05.17.
//

#ifndef MDATOM_LJPOTENTIAL_H
#define MDATOM_LJPOTENTIAL_H


#include "Potential.h"

/*
 * Intermolekular!
 */
class LJPotential : public Potential {
public:

    double sigma;
    double epsilon;


    LJPotential(double r, double sigma, double epsilon);


    double computePotential() override;

    double computeForceMagnitude() override ;
};


#endif //MDATOM_LJPOTENTIAL_H
