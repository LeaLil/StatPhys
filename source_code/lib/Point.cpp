//
// Created by lea on 15.05.17.
//

#include <cmath>
#include "Point.h"


double Point::computeDistanceToOtherPoint(Point otherPoint) {
    double deltaX = otherPoint.x - x;
    double deltaY = otherPoint.y - y;
    double deltaZ = otherPoint.z - z;

    return sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
}

Point &Point::operator*=(const double multiplyByConstant) {
    x *= multiplyByConstant;
    y *= multiplyByConstant;
    z *= multiplyByConstant;

    return *this;
}


Point operator*(const Point &num1, const double factor) {
    Point p;
    p.x = num1.x * factor;
    p.y = num1.y * factor;
    p.z = num1.z * factor;
    return p;
}

Point &Point::operator+=(const Point point1) {
    x = point1.x;
    y = point1.y;
    z = point1.z;
    return *this;
}