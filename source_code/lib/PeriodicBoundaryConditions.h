#ifndef PERIODICBOUNDARYCONDITIONS_H
#define PERIODICBOUNDARYCONDITIONS_H

#include <vector>

/*!
 * This class verifies whether all atoms are located in the simulation box.
 * It will translate atoms that are not, following periodic boundary conditions.
 */
class PeriodicBoundaryConditions {
  public:
    // Keep atoms in central periodic box
    static void recenterAtoms(int nat, std::vector<double>& positions, double const * box);
    static void recenterAtoms(int nat, std::vector<double>& positions, double const * box, double const * origin);
};

#endif // PERIODICBOUNDARYCONDITIONS_H