#include "PropertyResidence.h"


PropertyResidence::PropertyResidence(int BP, Block b, string n, int price, int Tuition)
    : Property{BP, b, n, price}, BaseTuition{Tuition} {}

int PropertyResidence::getTuition(int ResCount){
    int tuition = BaseTuition;
    for (int i = 0; i < ResCount; i++){
        tuition = tuition * 2;
    }
    return tuition;
}

