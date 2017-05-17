//
// Created by lea on 15.05.17.
//

#include "Molecule.h"
#include "Element.h"
#include "TotalPotential.h"
#include "MorsePotential.h"

inline int nearestInteger(double x) {
    return x > 0 ? static_cast<int>(x + 0.5) : static_cast<int>(x - 0.5);
}


Molecule::Molecule(std::vector<Element> elementList, System& s) : elementList(elementList), s(s) {}

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
}


/*
 * Let's compute intra and inter molecular energies and forces between every atom inside this Molecule and the molecule m.
 * Saves the appliedForced in e.applicedForce
 * Take boundary condition into account.
 */
double Molecule::calculateInteraction(Molecule &m, const MDParameters &mdParameters) {
    double interMolecular = 0.;
    double intraMolecular = 0.;

    //Apply boundary condition

    Point inversePoint = s.boxLength.getInversePoint();
    double inverseBoxLength[3] = {inversePoint.x, inversePoint.y, inversePoint.z};
        
    for (Element e : elementList) {
        for (Element e2 : m.elementList) {

            //TODO Apply boundary condition here
            //Apply boundary conditions
            Point delta = (e.position - e2.position);

            double x = nearestInteger(delta.x * inversePoint.x) * mdParameters.boxSize[0];
            double y = nearestInteger(delta.y * inversePoint.y) * mdParameters.boxSize[1];
            double z = nearestInteger(delta.z * inversePoint.z) * mdParameters.boxSize[2];
            delta -= Point(x, y, z );



            //End apply boundary conditions
            double r = delta.computeLength();
          /*  LJPotential lj = LJPotential(r, mdParameters.sigmaLJ,
                                       mdParameters.epsilonLJ); //You forgot a "public" beim Erben :-) Please don't use 1/0 for true/false
            */
            MorsePotential hp = MorsePotential(r, mdParameters.equilibriumDistance, mdParameters.dissociationEnergy, mdParameters.inflexibility);
            CoulombPotential coulomb = CoulombPotential(r, e.charge, e2.charge);

            interMolecular += (hp.computePotential() + coulomb.computePotential());
            double interMolecularForce = hp.computeForceMagnitude() + coulomb.computeForceMagnitude();

            delta *= interMolecularForce;
            e.appliedForce += delta;
            e2.appliedForce -= delta;
        }
    }


    /* Intramolekular */
    for (int i = 0; i < elementList.size(); i++) {
        for (int j = i+1; j < elementList.size(); j++) {
            Element e1 = elementList[i];
            Element e2 = elementList[j];

            Point delta = (e1.position - e2.position);
            double x = nearestInteger(delta.x * inversePoint.x) * mdParameters.boxSize[0];
            double y = nearestInteger(delta.y * inversePoint.y) * mdParameters.boxSize[1];
            double z = nearestInteger(delta.z * inversePoint.z) * mdParameters.boxSize[2];
            delta -= Point(x, y, z );


            double r = delta.computeLength();
            CovalentPotential cvp = CovalentPotential(r, mdParameters, true);


            intraMolecular += cvp.computePotential();
            double intraMolecularForce = cvp.computeForceMagnitude();
            delta *= intraMolecularForce;
            e1.appliedForce += delta;
            e2.appliedForce -= delta;
        }
    }

    return interMolecular+ intraMolecular;


    //Compute new distance
    //calculate force and magnitude
    //calculateForceAndVirialContributions
}



void Molecule::applyForces(const MDParameters &mdParameters, double d) {
    for(Element& e : elementList) {
        Point newVelocityVector = (e.velocityVector + e.appliedForce * (mdParameters.timeStep / e.weight))*d;
        Point oldVelocityVector = e.velocityVector;

        s.oldTotalKineticEnergy += newVelocityVector * newVelocityVector * e.weight * 0.5;
        s.totalKineticEnergy += (oldVelocityVector + newVelocityVector) * (oldVelocityVector + newVelocityVector) * (e.weight * 0.125);


        e.velocityVector = newVelocityVector;
        e.position += newVelocityVector * s.mdParameters->timeStep;

        //Reset
        e.appliedForce = Point(0,0,0);
    }
}

Molecule::~Molecule() {
    //delete &elementList;

}
