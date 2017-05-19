//
// Created by lea on 15.05.17.
//

#include "Molecule.h"
#include "Element.h"
#include "TotalPotential.h"
#include "MorsePotential.h"
#include "InstantaneousRadialDistribution.h"
#include "AnglePotential.h"

inline int nearestInteger(double x) {
    return x > 0 ? static_cast<int>(x + 0.5) : static_cast<int>(x - 0.5);
}


Molecule::Molecule(std::vector<Element> elementList, System &s) : elementList(elementList), s(s) {}

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

/*
 * Let's compute intra and inter molecular energies and forces between every atom inside this Molecule and the molecule m.
 * Saves the appliedForced in e.applicedForce
 * Take boundary condition into account.
 */
double Molecule::calculateInter(Molecule &m, const MDParameters &mdParameters,
                                InstantaneousRadialDistribution &radialDistribution) {
    double interMolecular = 0.;
    Point inversePoint = s.boxLength.getInversePoint();

    for (Element &e : elementList) {
        for (Element &e2 : m.elementList) {

            //Apply boundary conditions
            Point delta = (e.position - e2.position);

            double x = nearestInteger(delta.x * inversePoint.x) * mdParameters.boxSize[0];
            double y = nearestInteger(delta.y * inversePoint.y) * mdParameters.boxSize[1];
            double z = nearestInteger(delta.z * inversePoint.z) * mdParameters.boxSize[2];
            delta -= Point(x, y, z);
            //End apply boundary conditions


            double r = delta.computeLength();
            if (s.isOutOfRadius(r)) {
                continue;
            }

            LJPotential hp = LJPotential(r, mdParameters.sigmaLJ,
                                         mdParameters.epsilonLJ); //You forgot a "public" beim Erben :-) Please don't use 1/0 for true/false


            CoulombPotential coulomb = CoulombPotential(r, e.charge, e2.charge);

            interMolecular += (hp.computePotential() + coulomb.computePotential());
            double interMolecularForce = hp.computeForceMagnitude() + coulomb.computeForceMagnitude();

            delta *= interMolecularForce;
            e.appliedForce += delta;
            e2.appliedForce -= delta;
            s.virial -= (delta.x + delta.y + delta.z) * interMolecularForce;
            radialDistribution.addPairAtSquaredDistance(r * r);
        }
    }


    return interMolecular;


    //Compute new distance
    //calculate force and magnitude
    //calculateForceAndVirialContributions
}

double Molecule::calculateIntra(const MDParameters &mdParameters, InstantaneousRadialDistribution &distribution) {
    /* Intramolekular */
    double intra = 0;
    Point inversePoint = s.boxLength.getInversePoint();

    for (int i = 1; i < elementList.size(); i++) {
        Element &middleElement = elementList[i];
        Element &leftElement = elementList[i-1];


        Point deltaLeftMiddle = (middleElement.position - leftElement.position);
        double x = nearestInteger(deltaLeftMiddle.x * inversePoint.x) * s.boxLength.x;
        double y = nearestInteger(deltaLeftMiddle.y * inversePoint.y) * s.boxLength.y;
        double z = nearestInteger(deltaLeftMiddle.z * inversePoint.z) * s.boxLength.z;
        deltaLeftMiddle -= Point(x, y, z);
        double rDeltaLeftMiddle = deltaLeftMiddle.computeLength();
        HarmonicPotential harmonicLeftMiddle = HarmonicPotential(rDeltaLeftMiddle, mdParameters.equilibriumAngle,
                                                                 mdParameters.forceConstant);

        //LJPotential harmonicLeftMiddle =  LJPotential(rDeltaLeftMiddle, mdParameters.sigmaLJ, mdParameters.epsilonLJ);*/

        if((i+1) < elementList.size()) {
            //Not at end of list -> you can still compute the angle...
            //Compute angle... and potential
            Element &rightElement = elementList[i+1];

            AnglePotential ang = AnglePotential(leftElement.position, middleElement.position, rightElement.position, 0, mdParameters.equilibriumAngle, mdParameters.angleforceConstant);

            double AnglePotEnery = ang.computePotential();
            intra += AnglePotEnery;

            Point af = ang.computeForce();
            leftElement.appliedForce += af;
            rightElement.appliedForce -= af;
        }

        intra += harmonicLeftMiddle.computePotential();
        double forceMagnitude = harmonicLeftMiddle.computeForceMagnitude();
        deltaLeftMiddle *= forceMagnitude;

        middleElement.appliedForce += deltaLeftMiddle;
        leftElement.appliedForce -= deltaLeftMiddle;
//radialDistribution.addPairAtSquaredDistance(r * r);

    }
    return intra;

}

void Molecule::computeViral() {
    for (Element &e : elementList) {
        s.virial -= (e.appliedForce * e.position);
    }
}

void Molecule::applyForces(const MDParameters &mdParameters, double d) {
    double totalWeight = 0;
    for (Element &e : elementList) {
        Point oldVelocityVector = e.velocityVector;

        Point newVelocityVector = (oldVelocityVector + e.appliedForce * (mdParameters.timeStep / e.weight)) * d;

        s.oldTotalKineticEnergy += newVelocityVector * newVelocityVector;
        s.totalKineticEnergy +=
                (oldVelocityVector + newVelocityVector) * (oldVelocityVector + newVelocityVector);
        totalWeight += (e.weight);

        e.velocityVector = newVelocityVector;
        e.position += newVelocityVector * mdParameters.timeStep;

        //Reset
        e.appliedForce = Point(0, 0, 0);
    }
    s.oldTotalKineticEnergy *= totalWeight * 0.5;
    s.totalKineticEnergy *= totalWeight * 0.125;
}

Molecule::~Molecule() {
    //delete &elementList;

}
