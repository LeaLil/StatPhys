//
// Created by lea on 15.05.17.
//

#ifndef MDATOM_MOLECULE_H
#define MDATOM_MOLECULE_H


#include <vector>
#include "Point.h"
#include "Element.h"

class Molecule {


public:
    Molecule(const std::vector<Element> &elementList);

    std::vector<Element> elementList;

    Point computeGravityCenter();
    double computeDistanceToMolecule(Molecule m);


};


#endif //MDATOM_MOLECULE_H
