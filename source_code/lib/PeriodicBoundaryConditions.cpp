#include "PeriodicBoundaryConditions.h"

inline int nearestInteger(double x) {
    return x > 0 ? static_cast<int>(x + 0.5) : static_cast<int>(x - 0.5);
}

void PeriodicBoundaryConditions::recenterAtoms(int nat, std::vector<double>& positions, double const *box){
    double origin[3];
    for (int m = 0; m < 3; m++) {
        origin[m] = 0;
    }
    recenterAtoms(nat, positions, box, origin);
}

void PeriodicBoundaryConditions::recenterAtoms(int nat, std::vector<double>& positions,
                                               double const *box, double const *origin) {
    double inverseBoxLength[3], boxCenter[3];

    for (int i = 0; i < 3; i++) {
        inverseBoxLength[i] = 1. / box[i];
        boxCenter[i] = origin[i] + box[i] / 2.;
    }
    for (int j = 0; j < nat; j++) {
        int j3 = 3 * j;
        for (int i = 0; i < 3; i++) {
            double xh = (positions[j3 + i] - boxCenter[i]) * inverseBoxLength[i];
            positions[j3 + i] -= nearestInteger(xh) * box[i];
        }
    }
}
