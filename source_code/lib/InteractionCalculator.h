#ifndef INTERACTIONCALCULATOR_H
#define INTERACTIONCALCULATOR_H

#include "MDParameters.h"
#include "InstantaneousRadialDistribution.h"
#include "Molecule.h"

/*!
 * This class calculates the interactions for the atoms in the systems.
 * It updates the atomic forces and also calculates the potential energy, virial, and instantaneous radial distribution.
 *
 * The interaction implemented here follows a Lennard-Jones potential
 *     v(rij)  =  4*epslj*((siglj/rij)^12 - (siglj/rij)^6)
 * for all pairs (i<j) of atoms i and j at a distance rij.
 * The pairs are selected using a cut-off radius rcutf.
 * Rectangular periodic boundary conditions are applied, that is, only nearest periodic images are included in the interaction.
 */
class InteractionCalculator{
  public:
    explicit InteractionCalculator(const MDParameters& parameters);
    void calculate(const std::vector<double>& positions, std::vector<double>& forces, std::vector<Molecule>& moleculeList);
    double getPotentialEnergy() const;
    const InstantaneousRadialDistribution& getInstantaneousRadialDistribution() const;

  private:
    void initializeValues();
    void resetVariablesToZero(std::vector<double>& forces);
    const MDParameters& par;
    InstantaneousRadialDistribution radialDistribution;

    double potentialEnergy;

};

#endif // INTERACTIONCALCULATOR_H
