//
// Created by lea on 15.05.17.
//

#ifndef MDATOM_ELEMENT_H
#define MDATOM_ELEMENT_H


#include <vector>
#include "Point.h"

class Element {
public:
    virtual ~Element();

public:
    double weight = 1;
    std::vector<Element> bondedWith;

    Point position;
    Point appliedForce;
    Point velocityVector = Point(0,0,0);

    double charge = 1.0;

};




#endif //MDATOM_ELEMENT_H
