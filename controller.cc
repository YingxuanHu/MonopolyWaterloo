#include "controller.h"
#include <algorithm>
#include <iostream>


bool Controller::CommandArgs(int argc, char * argv[], bool &testing, bool &load, string &loadfile){
    if (argc > 4){
        cout << "ERROR: Too Many Command Line Arguments" << endl;
        return false;
    } else if (argc == 2){
        string s = argv[1];
        if (s == "-testing"){
            testing = true;
        } else if (s == "-load"){
            cout << "ERROR: No Load File Given" << endl;
            return false;
        } else{
            cout << "ERROR: Invalid Comand Line Argument" << endl;
            return false;
        }
    } else if (argc == 3){
        string s = argv[1];
        if (s == "-testing"){
            testing = true;
            s = argv[2];
            if (s == "-load"){
                cout << "ERROR: No Load File Given" << endl;
                return false;
            }
        } else if (s == "-load"){
            load = true;
            loadfile = argv[2];
        } else{
            cout << "ERROR: Invalid Comand Line Argument" << endl;
            return false;
        }
    } else if (argc == 4){
        string s = argv[1];
        if (s == "-testing"){
            testing = true;

            s = argv[2];
            if (s == "-load"){
                load = true;
                loadfile = argv[3];
            } else{
                cout << "ERROR: Invalid Comand Line Argument" << endl;
                return false;
            }
        } else if (s == "-load"){
            load = true;
            loadfile = argv[2];

            string s = argv[3];
            if (s == "-testing"){
                testing = true;
            } else{
                cout << "ERROR: Invalid Comand Line Argument" << endl;
                return false;
            }
        } else{
            cout << "ERROR: Invalid Comand Line Argument" << endl;
        }
    }
    return true;
}


bool Controller::GameSetUp(vector <Location *> &WATOPOLYBoard, vector <Player*> &players, Game &g, bool testing, bool load, string loadfile){
    cout << "Welcome to Watopoly!" << endl;
    if (testing){
        cout << "---TESTING ENABLED---" << endl;;
    }
    if (load){
        cout << "---LOAD ENABLED---" << endl;
        cout << "loading file: " << loadfile << endl;
        bool LoadGame = g.LoadGame(WATOPOLYBoard, players, loadfile);
        if (!LoadGame){
            cout << "ERROR: LOAD FAILED" << endl;
            return false;
        }
    } else{
        return NewGame(WATOPOLYBoard, players, g);
    }
    return true;
}
    

bool Controller::NewGame(vector <Location *> &WATOPOLYBoard, vector <Player*> & players, Game &g){
    string input;
    vector <string> names;
    vector <string> tokens;
    int PlayerCount = 0;
    bool SuccessInput = false;
    bool HR_OSAP = false;
    bool HR_Goose = false;
    int Goose = 0;
    int StartCash = 1500;

    cout << "Enter Number of Players" << endl;
    while (!SuccessInput && cin >> input){
        if(input.length() != 1 || !isdigit(input[0])){
            cout << "Invalid Input: Please Enter a Number Between 2 and 8" << endl;
            continue;
        }
        PlayerCount = stoi(input);
        if (PlayerCount >=2 && PlayerCount <= 8){
            SuccessInput = true;
        } else{
            cout << "Invalid Input: Please Enter a Number Between 2 and 8" << endl;
        }
    }
    if(!SuccessInput){
        return false;
    }

    for (int i = 1; i <= PlayerCount; i++){
        SuccessInput = false;
        cout << "Player " << i << ", Enter Your Name" << endl;
        while (!SuccessInput && cin >> input){
            if(find(names.begin(), names.end(), input) != names.end()){
                cout << "Player Name Already Taken. Try Again" << endl;
            } else{
                SuccessInput = true;
                names.emplace_back(input);
            }
        }
        if (!SuccessInput){
            return false;
        }

        SuccessInput = false;
        cout << "Player " << i << ", Choose Your Token" << endl;;
        while (!SuccessInput && cin >> input){
            if(input.length() != 1){
                cout << "Invalid Token. Try Again" << endl;
            } else if(find(tokens.begin(), tokens.end(), input) != tokens.end()){
                cout << "Token Already Taken. Try Again" << endl;
            } else{
                SuccessInput = true;
                tokens.emplace_back(input);
            }
        }
        if (!SuccessInput){
            return false;
        }
    }

    // Enable HR
    SuccessInput = false;
    cout << "Enable House Rules? (Y/N)" << endl;
    while (!SuccessInput && cin >> input){
        if(input == "Y"){
            cout << "---House Rules Enabled---" << endl;

            // Double OSAP
            cout << "(House Rules) Enable Double Rent on OSAP? (Y/N)" << endl;
            SuccessInput = false;
            while (!SuccessInput && cin >> input){
                if(input == "Y"){
                    cout << "---Double Rent on OSAP Enabled---" << endl;
                    HR_OSAP = true;
                    SuccessInput = true;
                } else if (input == "N"){
                    cout << "---Double Rent on OSAP Disabled---" << endl;
                    SuccessInput = true;
                } else{
                    cout << "Invalid Input Try Again" << endl;
                }
            }
            if(!SuccessInput){
                return false;
            }

            // Goose Landing
            cout << "(House Rules) Enable Receive Taxes at Goose Landing? (Y/N)" << endl;
            SuccessInput = false;
            while (!SuccessInput && cin >> input){
                if(input == "Y"){
                    cout << "---Receive Taxes at Goose Landing Enabled---" << endl;
                    HR_Goose = true;
                    SuccessInput = true;
                    cout << "(House Rules) Enter Amount at Goose Landing at Start of Game" << endl;
                    if (cin >> input){
                        for (int i = 0; i < (int) input.length(); i++){
                            if (!isdigit(input[i])){
                                cout << "Invalid Input, Starting Amount at Goose Landing set to 0" << endl;
                                SuccessInput = false;
                                break;
                            }
                        }
                        if (SuccessInput){
                            Goose = stoi(input);
                            cout << "Starting Amount at Goose Landing set to " << Goose << endl;
                        }
                        SuccessInput = true;
                    } else {
                        return false;
                    }
                } else if (input == "N"){
                    cout << "---Receive Taxes at Goose Landing Disabled---" << endl;
                    SuccessInput = true;
                } else{
                    cout << "Invalid Input Try Again" << endl;
                }
            }
            if(!SuccessInput){
                return false;
            }

            // Starting Cash
            cout << "(House Rules) Enter Amount Each Player Should start with" << endl;
            if (cin >> input){
                SuccessInput = true;
                for (int i = 0; i < (int) input.length(); i++){
                    if (!isdigit(input[i])){
                        cout << "Invalid Input, Starting Amount set to 1500" << endl;
                        SuccessInput = false;
                        break;
                    }
                }
                if (SuccessInput){
                    StartCash = stoi(input);
                    cout << "Starting Amount set to " << StartCash << endl;
                }
                SuccessInput = true;
            } else {
                return false;
            }
        } else if (input == "N"){
            cout << "---House Rules Disabled---" << endl;
            SuccessInput = true;
        } else{
            cout << "Invalid Input Try Again" << endl;
        }
    }

    players.erase(players.begin() + PlayerCount, players.end());
    for (int i = 0; i < (int) players.size(); i++){
        players.at(i)->setMoney(StartCash);
        players.at(i)->setName(names.at(i));
        players.at(i)->setToken(tokens.at(i).at(0));
    }

    g.StartGame(WATOPOLYBoard, players, HR_OSAP, HR_Goose, StartCash, Goose, true);
    return true;
}

void Controller::FailInput(Game &g){
    cout << "Not Enough Input" << endl;
    g.SaveGame("Autosave.txt");
    cout << "Exiting, Autosaved" << endl;
}

