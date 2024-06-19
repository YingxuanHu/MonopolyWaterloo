#ifndef PROPERTY_GYM_H
#define PROPERTY_GYM_H

#include "property.h"
using namespace std;

class PropertyGym : public Property {
    int Rate1;
    int Rate2;

    public:
    PropertyGym(int BP, Block b, string n, int price, int Rate1, int Rate2);
    int getTuition(int GymCount, int DiceTotal);
};

#endif

