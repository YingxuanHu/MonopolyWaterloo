#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "PropertyRegular.h"
#include "PropertyResidence.h"
#include "PropertyGym.h"
using namespace std;


class Game {
    vector <Location *> WATOPOLYBoard;
    vector <Player *> GamePlayers;
    int CurrentPlayer;
    bool canMove;
    bool hasMoved;
    int DoublesCount;
    vector <int> DiceRoll;
    int RUTRCardCount;
    bool HR_OSAP;
    bool HR_Goose;
    int GooseNest;

    public:
    friend class Display;

    ~Game();

    void DisplayGame();
    bool StartGame(vector <Location *> & WATOPOLYBoard, vector <Player*> players, bool osap, bool goose, int MoneyStart, int GooseStart, bool ChangeMoney);
    bool LoadGame(vector <Location *> & WATOPOLYBoard, vector <Player*> &players, string file_name);
    void SaveGame(string file_name);

    bool getMove();
    int getPlayerPos(string playername);
    int getPropertyPos(string propertyname);
    string getCurPlayerName();

    void Roll(unsigned int i = 6);
    bool RolledDoubles();

    void StartTurn();
    void DoTurn();
    void RegTurn();
    void EndTurn();
    void UnownedProperty();
    void PayRent();
    bool Debt(int amount, int reason); //return true if out of debt at end
    
    bool Trade(string CurrPlayerAsset, string OtherPlayer, string OtherPlayerAsset);
    bool Improve(string PropertyName, string action);  //action must be "Buy" or "Sell"
    bool Mortgage(string PropertyName);
    bool Unmortgage(string PropertyName);
    void GoToTims();

    void TimsLine();

    void LandOnSLC();
    void LandOnTuition();
    void LandOnNH();

    bool PartOfMonopoly(int Pos);
    
    
    void RollUpTheRim();
    void BeginAuction(int loc);
    bool DropOut(int reason);
    bool assets();
    void assetsAll();
};


#endif

