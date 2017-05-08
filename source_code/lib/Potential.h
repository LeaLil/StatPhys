//
// Created by lea on 08.05.17.
//

#ifndef MDATOM_POTENTIAL_H
#define MDATOM_POTENTIAL_H


class Potential {
public:

    Potential(double r, double r0);

    double r; //Variable radius
    double r0; //Equilibrium radius / Bond length

    double potential = 0;

    virtual double computePotential();
    virtual double computeForceMagnitude();
};


#endif //MDATOM_POTENTIAL_H
