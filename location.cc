#include "location.h"
#include <iostream>


Location::Location(int BP, Block b, string n) : BoardPosition{BP}, block{b}, name{n} {}

void Location::setPosition(int newPos){
    BoardPosition = newPos;
}

void Location::setBlock(Block newBlock){
    block = newBlock;
}

void Location::setName(string newName){
    name = newName;
}   

int Location::getPosition(){
    return BoardPosition;
}

Block Location::getBlock(){
    return block;
}

string Location::getName(){
    return name;
}
int Location::getPrice(){
    cout << "Something Went Wrong: Attempting to get Price of NonProperty Location!" << endl;
    
    return 0;
}

int Location::getImprovePrice(){
    cout << "Something Went Wrong: Attempting to get Improve Price of NonProperty Location!" << endl;
    return 0;
}

int Location::getImproveCount(){
    cout << "Something Went Wrong: Attempting to get Improve Count of NonProperty Location!" << endl;
    return 0;
}

string Location::getOwner(){
    cout << "Something Went Wrong: Attempting to Get Owner of NonProperty Location!" << endl;
    return "BANK";
};

bool Location::setImprove(int improves){
    cout << "Something Went Wrong: Attempting to set Improve Count of NonProperty Location!" << endl;
    return false;
}

void Location::changeOwners(string newOwner){
    cout << "Something Went Wrong: Attempting to change Owner of NonProperty Location!" << endl;
}

bool Location::isMortgaged(){
    cout << "Something Went Wrong: Attempting to get mortgage of NonProperty Location!" << endl;
    return false;
}

bool Location::mortgage(){
    cout << "Something Went Wrong: Attempting to mortgage NonProperty Location!" << endl;
    return false;
}

bool Location::unmortgage(){
    cout << "Something Went Wrong: Attempting to unmortgage NonProperty Location!" << endl;
    return false;
}

void Location::Notify(Subject &s){

}
