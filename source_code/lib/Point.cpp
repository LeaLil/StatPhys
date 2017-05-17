//
// Created by lea on 15.05.17.
//

#include <cmath>
#include "Point.h"


Point::Point() {}

Point::Point(double x, double y, double z) : x(x), y(y), z(z) {}


Point Point::getInversePoint() {
    return Point(1/x, 1/y, 1/z);
}
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


Point operator *(const Point &num1, const double factor) {
    Point p;
    p.x = num1.x * factor;
    p.y = num1.y * factor;
    p.z = num1.z * factor;
    return p;
}


double operator * (const Point &num1, const Point &num2) {
    return num1.x * num2.x + num1.y * num2.y+ num1.z * num2.z;
}
Point operator-(const Point &num1, const Point &num2) {
    Point p = Point(num1.x - num2.x, num1.y - num2.y, num1.z - num2.z);
    return p;
}


Point operator+(const Point &num1, const Point &num2) {
    Point p = Point(num1.x + num2.x, num1.y + num2.y, num1.z + num2.z);
    return p;
}

Point &Point::operator+=(const Point point1) {
    x += point1.x;
    y += point1.y;
    z += point1.z;
    return *this;
}
Point &Point::operator-=(const Point point1) {
    x -= point1.x;
    y -= point1.y;
    z -= point1.z;
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


Point::~Point() {


}

double Point::computeLength() {
    return x*x + y*y + z*z;
}
