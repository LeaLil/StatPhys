//
// Created by lea on 15.05.17.
//

#ifndef MDATOM_POINT_H
#define MDATOM_POINT_H


class Point {

public:
    double computeDistanceToOtherPoint(Point p);

    Point &operator*=(const double multiplyByConstant);
    friend Point operator * (const Point &num1, const double factor);
    Point &operator+=(const Point point1);




    double x;
    double y;
    double z;;
};


#endif //MDATOM_POINT_H
