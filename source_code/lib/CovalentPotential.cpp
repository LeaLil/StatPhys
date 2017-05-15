//
// Created by mariond on 09.05.17.
//

#include "CovalentPotential.h"


CovalentPotential::CovalentPotential(double r, MDParameters par, bool withangle) : Potential(r),
                                                                                              par(par),
                                                                                              withangle(withangle) {

    bonds = new HarmonicPotential(r, par.equilibriumDistance, par.forceConstant);
    angles = new HarmonicPotential(r, par.equilibriumDistance, par.forceConstant); //TODO: Spring constant same for Angles and bonds?
    dihedral = new TorsionPotential(r, 1, par.equilibriumAngle); //TODO: implement omega and gamma in MDParameters
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

CovalentPotential::~CovalentPotential() {
    delete bonds;
    delete angles;
    delete dihedral;

}
