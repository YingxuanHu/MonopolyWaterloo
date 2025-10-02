#ifndef PROPERTY_REG_H
#define PROPERTY_REG_H

#include "property.h"
#include "identifier.h"
#include <vector>
using namespace std;


class PropertyRegular : public Property {
    int improvePrice;
    int improveCount;
    vector <int> Tuition;
    
    public:
    PropertyRegular(int BP, Block b, string n, int price, int improvePrice, 
        int T0, int T1, int T2, int T3, int T4, int T5);

    int getImprovePrice() override;
    int getImproveCount() override;
    int getTuition(bool isMonopoly);
    bool addImprove();
    bool removeImprove();
    bool setImprove(int improves) override;
    bool mortgage() override;
};


#endif


