//
// Created by lea on 15.05.17.
//

#include "Molecule.h"
#include "Element.h"


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
double Molecule::computeDistanceToMolecule(Molecule m) {
    Point p = computeGravityCenter();
    Point p2 = m.computeGravityCenter();

    p.computeDistanceToOtherPoint(p2);
}