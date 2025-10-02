#ifndef PLAYER_H
#define PLAYER_H

#include "identifier.h"
#include "subject.h"
#include <string>
using namespace std;

class Player : public Subject{
    string PlayerName;
    char PlayerToken; 
    int Money;
    int CurrentPosition;
    int RUTRCards;
    TimsLineup AtTims;

    public:
    Player(string pn, char pt, int money);

    bool setMoney(int newMoney);
    bool setPosition(int newPos);
    bool setName(string pn);
    bool setToken(char pt);
    bool setRUTRCards(int newCards);
    bool setTimsLine (TimsLineup NewTims);

    string getPlayerName();
    char getPlayerToken();
    int getMoney();
    int getPosition();
    int getRUTRCards();
    TimsLineup getTims();

    bool useRUTRCard();
    int changeMoney(int change); // if money + change < 0, return amount left to pay, otherwise return 0
};

#endif

