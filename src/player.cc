#include "player.h"
#include "subject.h"
#include <string>

using namespace std;

Player::Player(string pn, char pt, int money)
: PlayerName(pn), PlayerToken(pt), Money(money), CurrentPosition(0), RUTRCards(0), AtTims(){}
//how to initialize this to true/false

bool Player::setMoney(int newMoney) {
    if (newMoney < 0){
        return false;
    }
    Money = newMoney;
    return true;
}

bool Player::setPosition(int newPos) {
    if (newPos < 0 || newPos >= 40){
        return false;
    }
    CurrentPosition = newPos;
    return true;
}

bool Player::setName(string pn){
    PlayerName = pn;
    return true;
}

bool Player::setToken(char pt){
    PlayerToken = pt;
    return true;
}

bool Player::setRUTRCards(int newCards) {
    if (newCards < 0 || newCards > 4){
        return false;
    }
    RUTRCards = newCards;
    return true;
}

bool Player::setTimsLine(TimsLineup NewTims) {
    AtTims = NewTims;
    return true;
}

string Player::getPlayerName() {
    return PlayerName;
}

char Player::getPlayerToken() {
    return PlayerToken;
}

int Player::getMoney() {
    return Money;
}

int Player::getPosition() {
    return CurrentPosition;
}

int Player::getRUTRCards() {
    return RUTRCards;
}

TimsLineup Player::getTims() {
    return AtTims;
}

bool Player::useRUTRCard() {
    if (RUTRCards > 0) {
        RUTRCards--;
        return true;
    }
    return false;
}

int Player::changeMoney(int change) {
    int newMoney = Money + change;
    if (newMoney < 0) {
        int amountLeftToPay = -newMoney;
        Money = 0;
        return amountLeftToPay;
    }
    Money = newMoney;
    return 0;
}

