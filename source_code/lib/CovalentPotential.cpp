//
// Created by mariond on 09.05.17.
//

#include "CovalentPotential.h"


CovalentPotential::CovalentPotential(double r, double r0, MDParameters par, bool withangle) : Potential(r, r0),
                                                                                              par(par),
                                                                                              withangle(withangle) {

    bonds = new HarmonicPotential(1, r, r0); //TO DO: implement kr in MDParameters
    angles = new HarmonicPotential(1, r, r0); // "
    dihedral = new TorsionPotential(r, r0, 1, 1); //TO DO: implement omega and gamma in MDParameters
}

double CovalentPotential::computePotential() {
    if (withangle) {
        return bonds->computePotential() + angles->computePotential() + dihedral->computePotential();
    }
    return bonds->computePotential() + dihedral->computePotential();
}

double CovalentPotential::computeForceMagnitude() {
    return bonds->computeForceMagnitude() + angles->computeForceMagnitude() + dihedral->computeForceMagnitude();
}

