//
// Created by lea on 15.05.17.
//

#include "Molecule.h"
#include "Element.h"
#include "TotalPotential.h"

Molecule::Molecule(std::vector<Element> elementList) : elementList(elementList) {}

Point Molecule::computeGravityCenter() {
    Point gravityCenter;
    double totalWeight = 0;
    for (int i = 0; i < elementList.size(); i++) {
        Element element = elementList[i];

        gravityCenter += element.position * element.weight;

        totalWeight += element.weight;
    }

    gravityCenter *= totalWeight;
    return gravityCenter;
}

double Molecule::computeDistanceToMolecule(Molecule &m) {
    Point p = computeGravityCenter();
    Point p2 = m.computeGravityCenter();

    return p.computeDistanceToOtherPoint(p2);
}

void Molecule::calculateInteraction(Molecule &m, const MDParameters &mdParameters) {

    //Apply boundary conditions



    //Compute
    double r = computeDistanceToMolecule(m);
    Potential *potential = new TotalPotential(r, true,
                                              mdParameters); //You forgot a "public" beim Erben :-) Please don't use 1/0 for true/false
    //Avogadro
    double eij = potential->computePotential();
    double dij = potential->computeForceMagnitude();

    //Compute new distance
    //calculate force and magnitude
    //calculateForceAndVirialContributions
}

Molecule::~Molecule() {
    //delete &elementList;

}
