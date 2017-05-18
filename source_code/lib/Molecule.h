//
// Created by lea on 15.05.17.
//

#ifndef MDATOM_MOLECULE_H
#define MDATOM_MOLECULE_H


#include <vector>
#include "Point.h"
#include "Element.h"
#include "MDParameters.h"
#include "System.h"

#include "InstantaneousRadialDistribution.h"

class Molecule {


public:
    Molecule(std::vector<Element> elementList, System& s);
    System& s;

    std::vector<Element> elementList;

    Point computeGravityCenter();
    double computeDistanceToMolecule(Molecule& m);
    double calculateInter(Molecule &m, const MDParameters &mdParameters,
                          InstantaneousRadialDistribution &distribution);


    double calculateIntra(const MDParameters &mdParameters,
                          InstantaneousRadialDistribution &distribution);

    virtual ~Molecule();


    void applyForces(const MDParameters &mdParameters, double d);

    void computeViral();
};


#endif //MDATOM_MOLECULE_H
