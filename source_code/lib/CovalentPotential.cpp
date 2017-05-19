//
// Created by mariond on 09.05.17.
//

#include "CovalentPotential.h"
#include "MorsePotential.h"


CovalentPotential::CovalentPotential(double r, MDParameters par, bool withangle) : Potential(r),
                                                                                              par(par),
                                                                                              withangle(withangle) {

   /*  bonds = new HarmonicPotential(r, par.equilibriumDistance, par.forceConstant);*/
    bonds = new MorsePotential(r, par.equilibriumDistance, par.dissociationEnergy,
                           par.inflexibility);

    angles = new HarmonicPotential(r, par.equilibriumDistance, par.forceConstant); //TODO: Spring constant same for Angles and bonds?
    //dihedral = new TorsionPotential(r, 1, par.equilibriumAngle); //TODO: implement omega and gamma in MDParameters
}

double CovalentPotential::computePotential() {
    withangle = false; //TODO entfernen
    if (withangle) {
        potential = bonds->computePotential() + angles->computePotential();
        return potential;
    }
    potential = bonds->computePotential();
    return potential;
}

double CovalentPotential::computeForceMagnitude() {
    return bonds->computeForceMagnitude() /*+ angles->computeForceMagnitude()*/;
}

CovalentPotential::~CovalentPotential() {
    delete bonds;
    //delete angles;
    //delete dihedral;

}
