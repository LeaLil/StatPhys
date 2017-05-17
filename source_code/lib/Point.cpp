//
// Created by lea on 15.05.17.
//

#include <cmath>
#include "Point.h"


Point::Point() {}

Point::Point(double x, double y, double z) : x(x), y(y), z(z) {}

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

double& Point::getPointByNumber(int i) {
        switch(i){

            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
        }

}