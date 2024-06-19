#ifndef LOCATION_H
#define LOCATION_H

#include "observer.h"
#include "identifier.h"
#include <string>
using namespace std;

class Location : public Observer{
    int BoardPosition;
    Block block;
    string name;

    public:
    Location(int BP, Block b, string n);
    void setPosition(int newPos);
    void setBlock(Block block);
    void setName(string newName);
    int getPosition();
    Block getBlock();
    string getName();
    virtual int getPrice();
    virtual int getImprovePrice();
    virtual int getImproveCount();
    virtual string getOwner();
    virtual bool setImprove(int improves);
    virtual void changeOwners(string newOwner);
    virtual bool isMortgaged();
    virtual bool mortgage();
    virtual bool unmortgage();
    void Notify(Subject&s) override;
};

#endif
