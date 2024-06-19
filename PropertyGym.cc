#include "PropertyGym.h"

PropertyGym::PropertyGym(int BP, Block b, string n, int price, int Rate1, int Rate2)
    : Property{BP, b, n, price}, Rate1{Rate1}, Rate2{Rate2} {}

int PropertyGym::getTuition(int GymCount, int DiceTotal){
    if (GymCount == 1){
        return Rate1 * DiceTotal;
    }
    return Rate2 * DiceTotal;
}
