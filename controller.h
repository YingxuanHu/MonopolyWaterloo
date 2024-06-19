#include "game.h"
class Controller {
    public:
    bool CommandArgs(int argc, char * argv[], bool &testing, bool &load, string &loadfile);
    bool GameSetUp(vector <Location *> &WATOPOLYBoard, vector <Player*> &players, Game &g, bool testing, bool load, string loadfile);
    bool NewGame(vector <Location *> &WATOPOLYBoard, vector <Player*> &players, Game &g);
    void FailInput(Game &g);


};



