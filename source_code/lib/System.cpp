
//
// Created by lea on 17.05.17.
//

#include "System.h"
bool System::isOutOfRadius(double r) {
    return r*r > cutoffRadiusSquared;
}