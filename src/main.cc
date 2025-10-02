#include "controller.h"
#include <algorithm>
#include <iostream>
#include <string>

namespace {
void PrintCommandHelp(){
    using std::cout;
    using std::endl;
    cout << "Available commands:" << endl;
    cout << "  roll        - Roll the dice and move. You may roll again if you get doubles." << endl;
    cout << "  next        - End your turn once you have finished all actions." << endl;
    cout << "  trade NAME GIVE RECEIVE - Offer a trade to another player." << endl;
    cout << "  improve PROPERTY buy|sell - Buy or sell an improvement on a property you own." << endl;
    cout << "  mortgage PROPERTY - Mortgage a property for cash." << endl;
    cout << "  unmortgage PROPERTY - Pay to unmortgage a property." << endl;
    cout << "  bankrupt    - Declare bankruptcy if you cannot pay what you owe." << endl;
    cout << "  assets      - Show your current money, properties, and improvements." << endl;
    cout << "  save FILE   - Save the current game state to FILE." << endl;
    cout << "  help        - Display this command list again." << endl;
}
}

int main( int argc, char * argv[] ) {
    Controller c {};
    bool testing = false;
    bool load = false;
    string loadfile = "";

    bool valid = c.CommandArgs(argc, argv, testing, load, loadfile);
    if (!valid){
        return -1;
    }

    vector <Location *> WATOPOLYBoard;
    Location L0 {0, Block::OSAP, "COLLECT OSAP"};
    PropertyRegular L1 {1, Block::Arts1, "AL", 40, 50, 2, 10, 30, 90, 160, 250};
    Location L2 {2, Block::SLC, "SLC"};
    PropertyRegular L3 {3, Block::Arts1, "ML", 60, 50, 4, 20, 60, 180, 320, 450};
    Location L4 {4, Block::Tuition, "TUITION"};
    PropertyResidence L5 {5, Block::Residence, "MKV", 200, 25};
    PropertyRegular L6 {6, Block::Arts2, "ECH", 100, 50, 6, 30, 90, 270, 400, 550};
    Location L7 {7, Block::NH, "NEEDLES HALL"};
    PropertyRegular L8 {8, Block::Arts2, "PAS", 100, 50, 6, 30, 90, 270, 400, 550};
    PropertyRegular L9 {9, Block::Arts2, "HH", 120, 50, 8, 40, 100, 300, 450, 600};
    Location L10 {10, Block::Tims, "DC Tims Line"};
    PropertyRegular L11 {11, Block::Eng, "RCH", 140, 100, 10, 50, 150, 450, 625, 750};
    PropertyGym L12 {12, Block::Gym, "PAC", 150, 4, 10};
    PropertyRegular L13 {13, Block::Eng, "DWE", 140, 100, 10, 50, 150, 450, 625, 750};
    PropertyRegular L14 {14, Block::Eng, "CPH", 160, 100, 12, 60, 180, 500, 700, 900};
    PropertyResidence L15 {15, Block::Residence, "UWP", 200, 25};
    PropertyRegular L16 {16, Block::Health, "LHI", 180, 100, 14, 70, 200, 550, 750, 950};
    Location L17 {17, Block::SLC, "SLC"};
    PropertyRegular L18 {18, Block::Health, "BMH", 180, 100, 14, 70, 200, 550, 750, 950};
    PropertyRegular L19 {19, Block::Health, "OPT", 200, 100, 16, 80, 220, 600, 800, 1000};
    Location L20 {20, Block::GooseNesting, "Goose Nesting"};
    PropertyRegular L21 {21, Block::Env, "EV1", 220, 150, 18, 90, 250, 700, 875, 1050};
    Location L22 {22, Block::NH, "NEEDLES HALL"};
    PropertyRegular L23 {23, Block::Env, "EV2", 220, 150, 18, 90, 250, 700, 875, 1050};
    PropertyRegular L24 {24, Block::Env, "EV3", 240, 150, 20, 100, 300, 750, 925, 1100};
    PropertyResidence L25 {25, Block::Residence, "V1", 200, 25};
    PropertyRegular L26 {26, Block::Sci1, "PHYS", 260, 150, 22, 110, 330, 800, 975, 1150};
    PropertyRegular L27 {27, Block::Sci1, "B1", 260, 150, 22, 110, 330, 800, 975, 1150};
    PropertyGym L28 {28, Block::Gym, "CIF", 150, 4, 10};
    PropertyRegular L29 {29, Block::Sci1, "B2", 280, 150, 24, 120, 360, 850, 1025, 1200};
    Location L30 {30, Block::GoToTims, "Go To Tims"};
    PropertyRegular L31 {31, Block::Sci2, "EIT", 300, 200, 26, 130, 390, 900, 1100, 1275};
    PropertyRegular L32 {32, Block::Sci2, "ESC", 300, 200, 26, 130, 390, 900, 1100, 1275};
    Location L33 {33, Block::SLC, "SLC"};
    PropertyRegular L34 {34, Block::Sci2, "C2", 320, 200, 28, 150, 450, 1000, 1200, 1400};
    PropertyResidence L35 {35, Block::Residence, "REV", 200, 25};
    Location L36 {36, Block::NH, "NEEDLES HALL"};
    PropertyRegular L37 {37, Block::Math, "MC", 350, 200, 35, 175, 500, 1100, 1300, 1500};
    Location L38 {38, Block::CoopFee, "COOP FEE"};
    PropertyRegular L39 {39, Block::Math, "DC", 400, 200, 50, 200, 600, 1400, 1700, 2000};
    WATOPOLYBoard.emplace_back(&L0);
    WATOPOLYBoard.emplace_back(&L1);
    WATOPOLYBoard.emplace_back(&L2);
    WATOPOLYBoard.emplace_back(&L3);
    WATOPOLYBoard.emplace_back(&L4);
    WATOPOLYBoard.emplace_back(&L5);
    WATOPOLYBoard.emplace_back(&L6);
    WATOPOLYBoard.emplace_back(&L7);
    WATOPOLYBoard.emplace_back(&L8);
    WATOPOLYBoard.emplace_back(&L9);
    WATOPOLYBoard.emplace_back(&L10);
    WATOPOLYBoard.emplace_back(&L11);
    WATOPOLYBoard.emplace_back(&L12);
    WATOPOLYBoard.emplace_back(&L13);
    WATOPOLYBoard.emplace_back(&L14);
    WATOPOLYBoard.emplace_back(&L15);
    WATOPOLYBoard.emplace_back(&L16);
    WATOPOLYBoard.emplace_back(&L17);
    WATOPOLYBoard.emplace_back(&L18);
    WATOPOLYBoard.emplace_back(&L19);
    WATOPOLYBoard.emplace_back(&L20);
    WATOPOLYBoard.emplace_back(&L21);
    WATOPOLYBoard.emplace_back(&L22);
    WATOPOLYBoard.emplace_back(&L23);
    WATOPOLYBoard.emplace_back(&L24);
    WATOPOLYBoard.emplace_back(&L25);
    WATOPOLYBoard.emplace_back(&L26);
    WATOPOLYBoard.emplace_back(&L27);
    WATOPOLYBoard.emplace_back(&L28);
    WATOPOLYBoard.emplace_back(&L29);
    WATOPOLYBoard.emplace_back(&L30);
    WATOPOLYBoard.emplace_back(&L31);
    WATOPOLYBoard.emplace_back(&L32);
    WATOPOLYBoard.emplace_back(&L33);
    WATOPOLYBoard.emplace_back(&L34);
    WATOPOLYBoard.emplace_back(&L35);
    WATOPOLYBoard.emplace_back(&L36);
    WATOPOLYBoard.emplace_back(&L37);
    WATOPOLYBoard.emplace_back(&L38);
    WATOPOLYBoard.emplace_back(&L39);

    Game WATOPOLY {};

    vector <Player *> players {};
    Player Player1 {"A", 'a', 1500};
    Player Player2 {"B", 'b', 1500};
    Player Player3 {"C", 'c', 1500};
    Player Player4 {"D", 'd', 1500};
    Player Player5 {"E", 'e', 1500};
    Player Player6 {"F", 'f', 1500};
    Player Player7 {"G", 'g', 1500};
    Player Player8 {"H", 'h', 1500};

    players.emplace_back(&Player1);
    players.emplace_back(&Player2);
    players.emplace_back(&Player3);
    players.emplace_back(&Player4);
    players.emplace_back(&Player5);
    players.emplace_back(&Player6);
    players.emplace_back(&Player7);
    players.emplace_back(&Player8);
    

    valid = c.GameSetUp(WATOPOLYBoard, players, WATOPOLY, testing, load, loadfile);
    if (!valid){
        return -1;
    }

    vector <string> Commands {};
    Commands.emplace_back("roll");
    Commands.emplace_back("next");
    Commands.emplace_back("trade");
    Commands.emplace_back("improve");
    Commands.emplace_back("mortgage");
    Commands.emplace_back("unmortgage");
    Commands.emplace_back("bankrupt");
    Commands.emplace_back("assets");
    Commands.emplace_back("save");
    Commands.emplace_back("help");

    cout << "Starting Game" << endl;
    WATOPOLY.DisplayGame();
    cout << endl;
    cout << "Type commands to play, or enter 'help' for a reminder." << endl;
    PrintCommandHelp();
    cout << "Command? (type 'help' for options)" << endl;

    string input;
    bool Action = false;

    while (cin >> input){
        Action = false;
        if(find(Commands.begin(), Commands.end(), input) != Commands.end()){
            if (input == "help"){
                PrintCommandHelp();
            } else if (input == "roll"){
                if (WATOPOLY.getMove()){
                    WATOPOLY.DoTurn();
                } else{
                    cout << WATOPOLY.getCurPlayerName() << " cannot Roll" << endl;
                }
            } else if (input == "next"){
                if (WATOPOLY.getMove()){
                    cout << WATOPOLY.getCurPlayerName() << " can still roll" << endl;
                } else{
                    WATOPOLY.EndTurn();
                }
            } else if (input == "trade"){
                string tname;
                string tgive;
                string treceive;
                if (cin >> tname && cin >> tgive && cin >> treceive){
                    Action = WATOPOLY.Trade(tname, tgive, treceive);
                    if (!Action){
                        cout << "Trade Failed" << endl;
                    } else{
                        cout << "Trade Successful" << endl;
                    }
                } else{
                    c.FailInput(WATOPOLY);
                    return -1;
                }
            } else if (input == "improve"){
                string iProperty;
                string iAction;
                if (cin >> iProperty && cin >> iAction){
                    if (iAction != "buy" && iAction != "sell"){
                        cout << "Invalid Improve Action" << endl;
                        continue;
                    }
                    Action = WATOPOLY.Improve(iProperty, iAction);
                    if (!Action){
                        cout << "Improve Failed" << endl;
                    } else{
                        cout << "Improve Successful" << endl;
                    }
                } else{
                    c.FailInput(WATOPOLY);
                    return -1;
                }    
            } else if (input == "mortgage"){
                string mProperty;
                if (cin >> mProperty){
                    Action = WATOPOLY.Mortgage(mProperty);
                    if (!Action){
                        cout << "Mortgage Failed" << endl;
                    } else{
                        cout << "Mortgage Successful" << endl;
                    }
                } else{
                    c.FailInput(WATOPOLY);
                    return -1;
                } 
            } else if (input == "unmortgage"){
                string mProperty;
                if (cin >> mProperty){
                    Action = WATOPOLY.Unmortgage(mProperty);
                    if (!Action){
                        cout << "Unmortgage Failed" << endl;
                    } else{
                        cout << "Unmortgage Successful" << endl;
                    }
                } else{
                    c.FailInput(WATOPOLY);
                    return -1;
                }
            } else if (input == "bankrupt"){
                Action = WATOPOLY.DropOut(-1);
                if (!Action){
                    cout << "Bankruptcy Failed: Not in Debt" << endl;
                } else{
                    cout << "Declare Bankruptcy Successful" << endl;
                }
            } else if (input == "assets"){
                Action = WATOPOLY.assets();
                if (!Action){
                    cout << "assets Failed: Player in Debt" << endl;
                }
            } else if (input == "save"){
                string filename;
                if (cin >> filename){
                    WATOPOLY.SaveGame(filename);
                    cout << "Game saved to " << filename << endl;
                } else{
                    c.FailInput(WATOPOLY);
                    return -1;
                }
            }
        } else{
            cout << "Invalid input. Type 'help' to see all available commands." << endl;
        }
        WATOPOLY.DisplayGame();
        cout << "Command? (type 'help' for options)" << endl;
    }

    return 0;
}
