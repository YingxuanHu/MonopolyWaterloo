#ifndef PROPERTY_RES_H
#define PROPERTY_RES_H

#include "property.h"
using namespace std;

class PropertyResidence : public Property {
    int BaseTuition;

    public:
    PropertyResidence(int BP, Block b, string n, int price, int Tuition);
    int getTuition(int ResCount);
};

#endif


