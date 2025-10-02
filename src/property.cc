#include "property.h"


Property::Property(int BP, Block b, string n, int price)
 : Location{BP,b,n}, price {price}, mortgaged{false}, OwnedBy{"BANK"} {}

void Property::setPrice(int newPrice){
    price = newPrice;
}

int Property::getPrice(){
    return price;
}

bool Property::isMortgaged(){
    return mortgaged;
}

bool Property::mortgage(){
    if (mortgaged){
        return false;
    }
    mortgaged = true;
    return true;
}

bool Property::unmortgage(){
    if (!mortgaged){
        return false;
    }
    mortgaged = false;
    return true;
};

string Property::getOwner(){
    return OwnedBy;
}

void Property::changeOwners(string newOwner){
    OwnedBy = newOwner;
}
