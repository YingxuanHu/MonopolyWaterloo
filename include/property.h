#ifndef PROPERTY_H
#define PROPERTY_H

#include "location.h"



class Property : public Location{
    int price;
    bool mortgaged;
    string OwnedBy;
    
    protected:
    Property(int BP, Block b, string n, int price);

    void setPrice(int newPrice);

    public:
    int getPrice() override;
    bool isMortgaged() override;
    bool mortgage() override; //if already mortgaged, returns false
    bool unmortgage() override; //if already unmortgaged, returns false
    string getOwner() override;
    void changeOwners(string newOwner) override;
};

#endif
