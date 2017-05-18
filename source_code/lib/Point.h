//
// Created by lea on 15.05.17.
//

#ifndef MDATOM_POINT_H
#define MDATOM_POINT_H

#include <vector>

class Point {

public:
    Point();

    Point(double x, double y, double z);
    Point getInversePoint();

    double computeDistanceToOtherPoint(Point p);

    Point &operator*=(const double multiplyByConstant);
    friend Point operator * (const Point &num1, const double factor);

    friend double operator * (const Point &num1, const Point &num2);
    friend Point operator-(const Point &num1, const Point &num2);

    friend Point operator+(const Point &num1, const Point &num2);
    Point &operator+=(const Point point1);
    Point &operator-=(const Point point1);
    double& getPointByNumber(int i);

    virtual ~Point();
    Point( const Point &obj);  // copy constructor

    double x;
    double y;
    double z;;

    double computeLength();
    std::vector<double> getAsArray();
};


#endif //MDATOM_POINT_H
