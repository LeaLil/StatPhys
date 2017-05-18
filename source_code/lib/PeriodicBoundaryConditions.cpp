#include "PeriodicBoundaryConditions.h"
#include "Molecule.h"

inline int nearestInteger(double x) {
    return x > 0 ? static_cast<int>(x + 0.5) : static_cast<int>(x - 0.5);
}

void PeriodicBoundaryConditions::recenterAtoms(int nat, std::vector<double>& positions, double const *box, std::vector<Molecule>& moleculeList){
    double origin[3];
    for (int m = 0; m < 3; m++) {
        origin[m] = 0;
    }
    recenterAtoms(nat, positions, box, origin, moleculeList);
}

void PeriodicBoundaryConditions::recenterAtoms(int nat, std::vector<double>& positions,
                                               double const *box, double const *origin, std::vector<Molecule>& moleculeList) {
    double inverseBoxLength[3], boxCenter[3];

    for (int i = 0; i < 3; i++) {
        inverseBoxLength[i] = 1. / box[i];
        boxCenter[i] = origin[i] + box[i] / 2.;
    }
    for(Molecule& m: moleculeList) {
        for(Element& e: m.elementList) {
            //Lalalala... Ja, ich weiss, dass sieht schlecht aus :-)
            double xh = (e.position.x - boxCenter[0]) * inverseBoxLength[0];
            e.position.x -= nearestInteger(xh) * box[0];

            double yh = (e.position.y - boxCenter[1]) * inverseBoxLength[1];
            e.position.y -= nearestInteger(yh) * box[1];

            double zh = (e.position.z - boxCenter[2]) * inverseBoxLength[2];
            e.position.z -= nearestInteger(zh) * box[2];
        }

    }
}
