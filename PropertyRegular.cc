#include "PropertyRegular.h"
#include <iostream>


PropertyRegular::PropertyRegular(int BP, Block b, string n, int price, int improvePrice, 
    int T0, int T1, int T2, int T3, int T4, int T5)
    : Property{BP, b, n, price}, improvePrice{improvePrice}, improveCount{0}, Tuition {{T0, T1, T2, T3, T4, T5}} {}


int PropertyRegular::getImprovePrice(){
    return improvePrice;
}


int PropertyRegular::getImproveCount(){
    return improveCount;
}


int PropertyRegular::getTuition(bool isMonopoly){
    if (isMonopoly && improveCount == 0){
        return 2 * Tuition.at(0);
    }
    return Tuition.at(improveCount);
}


bool PropertyRegular::mortgage(){
    if (isMortgaged() || improveCount > 0){
        cout << "Unable to Mortgage, Propery has Improvements!" << endl;
        return false;
    }
    Property::mortgage();
    return true;
}


bool PropertyRegular::addImprove(){
    if (improveCount == 5){
        return false;
    }
    improveCount++;
    return true;
}


bool PropertyRegular::removeImprove(){
    if (improveCount == 0){
        return false;
    }
    improveCount--;
    return true;
}


bool PropertyRegular::setImprove(int improves){
    if (improves < 0 || improves > 5) return false;
    improveCount = improves;
    return true;
}

