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
    double weight;
    std::vector<Element> bondedWith;

    Point position;


};




#endif //MDATOM_ELEMENT_H
