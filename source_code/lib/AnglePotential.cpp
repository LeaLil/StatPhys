//
// Created by mariond on 19.05.17.
//

#include "AnglePotential.h"
#include <math.h>

// call with ri... = e1.Position etc
AnglePotential::AnglePotential(Point& ri, Point& rj, Point& rk, double r, double theta_0, double ka) : Potential(r), theta_0(theta_0), ka(ka), ri(ri), rj(rj), rk(rk) {}

double AnglePotential::computePotential() {
    // TODO in molecule: calculate angle theta between i and the next two atoms j, k
    Point rij = (rj-ri);
    Point rkj = (rj-rk);
    double costheta = rij*rkj/(rij.computeLength()*rkj.computeLength());
    theta = acos(costheta);
    potential = (1./2.) * ka * (theta - theta_0) * (theta -theta_0);

    return potential;
}

double AnglePotential::computeForceMagnitude() {
    return 0;
}

Point AnglePotential::computeForce() {
    Point rij = (rj-ri);
    Point rkj = (rj-rk);
    double costheta = rij*rkj/(rij.computeLength()*rkj.computeLength());
    theta = acos(costheta);

    if (theta > 3.1 && theta < 3.2 ) {
        return Point(0,0,0);
    }

    double d = ka* (theta -theta_0) / sin(theta);
    double dn = d * 1./rij.computeLength();
    const Point &pointij = rij * (1. / rkj.computeLength());
    const Point &pointkj = rkj * (1. / rkj.computeLength());
    
    return (pointij - pointkj*costheta) * dn;
}