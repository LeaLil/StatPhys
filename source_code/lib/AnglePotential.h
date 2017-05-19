//
// Created by mariond on 19.05.17.
//

#ifndef MDATOM_ANGLEPOTENTIAL_H
#define MDATOM_ANGLEPOTENTIAL_H


#include "Potential.h"
#include "Molecule.h"

class AnglePotential : public Potential {

public:

    Point &ri;
    Point &rj;
    Point &rk;
    Point rij;
    Point rkj;
    double costheta = 0;
    double theta = 0;
    double theta_0 = 0;
    double ka = 0;

    AnglePotential(Point &ri, Point &rj, Point &rk, double r, double theta_0, double ka);

    double computePotential() override;


    double computeForceMagnitude() override;

    Point computeForce();


};


#endif //MDATOM_ANGLEPOTENTIAL_H
