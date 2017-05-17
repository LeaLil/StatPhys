//
// Created by lea on 15.05.17.
//

#ifndef MDATOM_MOLECULE_H
#define MDATOM_MOLECULE_H


#include <vector>
#include "Point.h"
#include "Element.h"
#include "MDParameters.h"

class Molecule {


public:
    Molecule(std::vector<Element> elementList);

    std::vector<Element> elementList;

    Point computeGravityCenter();
    double computeDistanceToMolecule(Molecule& m);
    void calculateInteraction(Molecule& m, const MDParameters& mdParameters);

    virtual ~Molecule();

    void applyBoundaryCondition(Molecule &m);
};


#endif //MDATOM_MOLECULE_H
