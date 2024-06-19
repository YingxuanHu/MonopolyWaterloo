#include "game.h"
#include "display.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>


Game::~Game(){
    for (auto i = 0; i < (int) WATOPOLYBoard.size(); i++){
        delete WATOPOLYBoard.at(i);
    }
    WATOPOLYBoard.clear();

    for (auto i = 0; i < (int) GamePlayers.size(); i++){
        delete GamePlayers.at(i);
    }
    GamePlayers.clear();
}


void Game::DisplayGame(){
    Display d {};
    d.DisplayBoard(*this);
}


bool Game::StartGame(vector <Location *> & WatopolyBoard, vector <Player*> players, bool osap, bool goose, int MoneyStart, int GooseStart, bool ChangeMoney){

    // Start Game
    for (int i = 0; i < 40; i++){
        WATOPOLYBoard.emplace_back(WatopolyBoard.at(i));
    }

    for (auto i = 0; i < (int) players.size(); i++){
        GamePlayers.emplace_back(players.at(i));
        if (ChangeMoney){
            GamePlayers.at(i)->setMoney(MoneyStart);    
        }
    }

    CurrentPlayer = 0;
    canMove = true;
    hasMoved = false;
    DoublesCount = 0;
    DiceRoll = {0,0};
    RUTRCardCount = 0;
    HR_OSAP = osap;
    HR_Goose = goose;
    GooseNest = GooseStart;

    return true;
}


bool Game::LoadGame(vector <Location *> & WATOPOLYBoard, vector <Player*> &players, string file_name){
    ifstream File(file_name);
    string input;
    int PlayerCount = 0;
    int i = 0;

    if(getline (File, input)){
        if(input.length() != 1 || !isdigit(input[0])){
            return false;
        }
        PlayerCount = stoi(input);
    }

    if(PlayerCount < 2 || PlayerCount > 8){
        return false;
    }

    vector <string> names;
    vector <string> tokens;
    vector <int> TimsCups;
    vector <int> PlayerMoney;
    vector <int> Positions;
    vector <int> InLine;
    vector <int> TurnsInLine;

    // Read Players
    while (i < PlayerCount && getline (File, input)){
        stringstream SS(input);
        string ss;
        // Get PlayerName
        if (SS >> ss){
            if(find(names.begin(), names.end(), ss) != names.end()){
                return false;
            }
            names.emplace_back(ss);
        } else{
            return false;
        }

        // Get PlayerToken
        if (SS >> ss){
            if(ss.length() != 1){
                return false;
            } if(find(tokens.begin(), tokens.end(), ss) != tokens.end()){
                return false;
            }
            tokens.emplace_back(ss);
        } else{
            return false;
        }

        // RUTR Cards
        int intInput = 0;
        if (SS >> ss){
            if(ss.length() != 1 || !isdigit(ss[0])){
                return false;
            }
            intInput = stoi(ss);
            TimsCups.emplace_back(intInput);
        } else{
            return false;
        }

        // Money
        if(SS >> ss){
            for (int j = 0; j < (int) ss.length(); j++){
                if(!isdigit(ss[j])){
                    return false;
                }
            }
            intInput = stoi(ss);
            PlayerMoney.emplace_back(intInput);
        } else{
            return false;
        }

        // Position
        if(SS >> ss){
            for (int j = 0; j < (int) ss.length(); j++){
                if(!isdigit(ss[j])){
                    return false;
                }
            }
            intInput = stoi(ss);
            if (intInput >= 40){
                return false;
            }
            Positions.emplace_back(intInput);
        } else{
            return false;
        }

        // InLine
        if(SS >> ss){
            if (intInput != 10){ //if not At Tims
                return false;
            } if(ss.length() != 1 || !isdigit(ss[0])){
                return false;
            }
            intInput = stoi(ss);
            if (intInput > 1){
                return false;
            }
            InLine.emplace_back(intInput);
        } else{
            InLine.emplace_back(-1);
        }

        // TurnsInLine
        if(SS >> ss){
            if (intInput != 1){ //if InLine
                return false;
            } if(ss.length() != 1 || !isdigit(ss[0])){
                return false;
            }
            intInput = stoi(ss);
            if (intInput > 2){
                return false;
            }
            InLine.emplace_back(intInput);
        } else{
            InLine.emplace_back(-1);
        }

        // Too much input
        if(SS >> ss){
            return false;
        }

        i++;
    }

    if (i != PlayerCount){
        return false;
    }

    int TotalTimsCup = 0;
    for (auto i = 0; i < (int) TimsCups.size(); i++){
        TotalTimsCup += TimsCups.at(i);
    }

    if (TotalTimsCup > 4){
        return false;
    }

    players.erase(players.begin() + PlayerCount, players.end());
    
    for (int i = 0 ; i < PlayerCount; i++){
        players.at(i)->setName(names.at(i));
        players.at(i)->setToken(tokens.at(i).at(0));
        players.at(i)->setRUTRCards(TimsCups.at(i));
        players.at(i)->setMoney(PlayerMoney.at(i));
        players.at(i)->setPosition(Positions.at(i));
        if (Positions.at(i)==10){
            if (InLine.at(i) == 0){
                players.at(i)->setTimsLine(TimsLineup::JustVisiting);
            } else if (TurnsInLine.at(i) == 0){
                players.at(i)->setTimsLine(TimsLineup::Turn1);
            } else if (TurnsInLine.at(i) == 2){
                players.at(i)->setTimsLine(TimsLineup::Turn2);
            } else{
                players.at(i)->setTimsLine(TimsLineup::Turn3);
            }
        } else{
            players.at(i)->setTimsLine(TimsLineup::NotAtTims);
        }
    }

    StartGame(WATOPOLYBoard, players, HR_OSAP, HR_Goose, 1500, 0, false);

    //Update Properties
    for (int j = 0; j < 40; j++){
        if (j==2 || j==4 || j==7 || j==10 || j==17 || j==20 || j==22 || j==30 || j==33 || j==36 || j==38){
            continue;
        }
        if (getline (File, input)) {
            
            stringstream SS(input);
            string ss;

            // PropertyName
            if (SS >> ss){
                if (ss.length() > 8){
                    ss = ss.substr(0,8);
                }
                WATOPOLYBoard.at(j)->setName(ss);
            } else{
                return false;
            }

            // PropertyOwner
            if (SS >> ss){
                if (find(names.begin(), names.end(), ss) != names.end()){
                    WATOPOLYBoard.at(j)->changeOwners(ss);
                } else if(ss == "BANK"){
                    WATOPOLYBoard.at(j)->changeOwners(ss);
                } else {
                    return false;
                }
            } else{
                return false;
            }

            // Improvements
            if (SS >> ss){
                if(ss == "-1"){
                    WATOPOLYBoard.at(j)->mortgage();
                } else if(ss.length() != 1 || !isdigit(ss[0])){
                    return false;
                } else{
                    int intInput = stoi(ss);
                    if (intInput > 5){
                        return false;
                    }
                    WATOPOLYBoard.at(j)->setImprove(intInput);
                }   
            } else{
                return false;
            }

            // Too much input
            if (SS >> ss){
                return false;
            }
        } else{
            return false;
        }
    }

    // Too much input
    if (getline (File, input)) {
        return false;
    }

    //Update Player Information
    for (auto i = 0; i < (int) names.size(); i++){
        GamePlayers.at(i)->setMoney(PlayerMoney.at(i));
        GamePlayers.at(i)->setPosition(Positions.at(i));
        if(Positions.at(i) == 10){
            if (InLine.at(i) == 0){
                GamePlayers.at(i)->setTimsLine(TimsLineup::JustVisiting);
            } else{
                if (TurnsInLine.at(i) == 0){
                    GamePlayers.at(i)->setTimsLine(TimsLineup::Turn1);
                } else if (TurnsInLine.at(i) == 2){
                    GamePlayers.at(i)->setTimsLine(TimsLineup::Turn2);
                } else{
                    GamePlayers.at(i)->setTimsLine(TimsLineup::Turn3);
                }
            } 
        } else{
            GamePlayers.at(i)->setTimsLine(TimsLineup::NotAtTims);
        }
    }

    return true;
}


void Game::SaveGame(string file_name){
    ofstream file{file_name};

    file << GamePlayers.size() << endl;
    for (auto i = 0; i < (int) GamePlayers.size(); i++){
        file << GamePlayers.at(i)->getPlayerName() << " ";
        file << GamePlayers.at(i)->getPlayerToken() << " ";
        file << GamePlayers.at(i)->getRUTRCards() << " ";
        file << GamePlayers.at(i)->getMoney() << " ";
        file << GamePlayers.at(i)->getPosition();

        if (GamePlayers.at(i)->getPosition() == 10){
            if(GamePlayers.at(i)->getTims() == TimsLineup::JustVisiting){
                file << " 0";
            } else {
                file << " 1";
                if (GamePlayers.at(i)->getTims() == TimsLineup::Turn1){
                    file << " 0";
                } else if (GamePlayers.at(i)->getTims() == TimsLineup::Turn2){
                        file << " 1";
                } else {
                    file << " 2";
                }
            }
        }
        file << endl;
    }

    for (auto i = 0; i <  (int) WATOPOLYBoard.size(); i++){
        // Skip non property locations
        if (i==2 || i==4 || i==7 || i==10 || i==17 || i==20 || i==22 || i==30 || i==33 || i==36 || i==38){
            continue;
        }

        file << WATOPOLYBoard.at(i)->getName() << " ";
        file << WATOPOLYBoard.at(i)->getOwner() << " ";
        file << WATOPOLYBoard.at(i)->getImproveCount() << endl;
    }
    file.close();
}


bool Game::getMove(){
    return canMove;
}


string Game::getCurPlayerName(){
    return GamePlayers.at(CurrentPlayer)->getPlayerName();
}


int Game::getPlayerPos(string playername){
    for (int i = 0; i < (int) GamePlayers.size(); i++){
        if (GamePlayers.at(CurrentPlayer)->getPlayerName() == playername){
            return i;
        }
    }
    return -1;
}


int Game::getPropertyPos(string propertyname){
    for (int i = 0; i < 40; i++){
        if(WATOPOLYBoard.at(i)->getName() == propertyname){
            return i;
        }
    }
    return -1;
}


void Game::Roll(unsigned int i){
    vector <int> die;
    for (int j = 1; j < (int) i; j++){
        die.emplace_back(j);
    }

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();

	default_random_engine rng{seed};

	for ( int i = 0; i < 2; i++ ) {
		shuffle( die.begin(), die.end(), rng );
		DiceRoll.at(i) = die.at(0); 		
	}

    cout << "Rolled " << DiceRoll.at(0) << " + " << DiceRoll.at(1) << " = ";
    cout << DiceRoll.at(0) + DiceRoll.at(1) << endl;
}


bool Game::RolledDoubles(){
    return (DiceRoll.at(0) == DiceRoll.at(1));
}



void Game::StartTurn(){
    DoublesCount = 0;
    hasMoved = false;
    if(GamePlayers.at(CurrentPlayer)->getTims() == TimsLineup::NotAtTims 
    || GamePlayers.at(CurrentPlayer)->getTims() == TimsLineup::JustVisiting){
        canMove = true;
    }
    else{
        canMove = false;
    }
}


void Game::DoTurn(){
    if (!canMove && hasMoved){
        EndTurn();
    }
    if (canMove){
        Roll();
        if (RolledDoubles()){
            DoublesCount++;
            canMove = true;
            if(DoublesCount >= 3){
                GoToTims();
                hasMoved = true;
                return;
            }
        } else{
            canMove = false;
        }
        RegTurn();
    } else if (!hasMoved && GamePlayers.at(CurrentPlayer)->getPosition() == 10){
        TimsLine();
    }
    hasMoved = true;
}


void Game::RegTurn(){
    int newPos = GamePlayers.at(CurrentPlayer)->getPosition() + DiceRoll.at(0) + DiceRoll.at(1);
    if (newPos ==  30){
        GoToTims();
    }
    if (newPos >= 40){
        newPos -= 40;
        cout << "Passed OSAP, Collect $200" << endl;
        GamePlayers.at(CurrentPlayer)->changeMoney(200);
    }
    GamePlayers.at(CurrentPlayer)->setPosition(newPos);

    cout << "Landed at " << WATOPOLYBoard.at(newPos)->getName() << endl;

    if(newPos == 0){ //LandOnOsap
        if(HR_OSAP){
            cout << "Collect from OSAP Doubled!" << endl;
            GamePlayers.at(CurrentPlayer)->changeMoney(200);
        }
    } else if (newPos == 2 || newPos == 17 || newPos == 33){
        LandOnSLC();
    } else if (newPos == 4){
        LandOnTuition();
    } else if (newPos == 7 || newPos == 22 || newPos == 36){
        LandOnNH();
    } else if (newPos == 10){
        cout << "Just Visting!" << endl;
    } else if (newPos == 20){ //LandOnGooseNesting
        cout << getCurPlayerName() << " is attacked by a flock of nesting geese";
        if(HR_Goose && GooseNest > 0){    
            cout << ", but they find $" << GooseNest << " in the Nest";
            GamePlayers.at(CurrentPlayer)->changeMoney(GooseNest);
            GooseNest = 0;
        }
        cout << "!" << endl;
    } else if(newPos == 38){ //LandOnCoOpFee
        cout << "Pay $150" << endl;
        int Fee = GamePlayers.at(CurrentPlayer)->changeMoney(-150);
        GooseNest += 150;
        if (Fee > 0){
            Debt(Fee, -1);
        }
    } else{
        string player = GamePlayers.at(CurrentPlayer)->getPlayerName();
        string owner = WATOPOLYBoard.at(newPos)->getOwner();
        if (owner == "BANK"){
            UnownedProperty();
        }
        else if (owner == player) {
            cout << player << " owns this property, no Rent required!" << endl;
        } else if(WATOPOLYBoard.at(newPos)->isMortgaged()){
            cout << "This property is mortgaged, no Rent required!" << endl;
        } else{
            PayRent();
        }
    }
}


void Game::EndTurn(){
    CurrentPlayer++;
    if (CurrentPlayer >= (int) GamePlayers.size()){
        CurrentPlayer -= (int) GamePlayers.size();
    }
    StartTurn();
}


void Game::UnownedProperty(){
    int newPos = GamePlayers.at(CurrentPlayer)->getPosition();
    cout << WATOPOLYBoard.at(newPos)->getName() << " is UnOwned. Purchase it? (Y/N)" << endl;
    int price = WATOPOLYBoard.at(newPos)->getPrice();
    string player = GamePlayers.at(CurrentPlayer)->getPlayerName();
    bool SuccessInput = false;
    string input;
    while (!SuccessInput && cin >> input){
        if(input == "Y"){
            if (GamePlayers.at(CurrentPlayer)->getMoney() < price){
                cout << player << " Does Not Have Enough Money! Property Moves to Auction!" << endl;
                BeginAuction(newPos);
            } else{
                GamePlayers.at(CurrentPlayer)->changeMoney(0 - price);
                cout << "Purchase Successful!" << endl;
                WATOPOLYBoard.at(newPos)->changeOwners(player);
                GamePlayers.at(CurrentPlayer)->attach(WATOPOLYBoard.at(newPos));
                }
            SuccessInput = true;
        } else if (input == "N"){
            cout << "Property Moves to Auction!" << endl;
            SuccessInput = true;
            BeginAuction(newPos);
        } else{
            cout << "Invalid Input, Try Again" << endl;
        }
    }
    if(!SuccessInput){
       cout << "No Input Detected" << endl;
    }
}


void Game::PayRent(){
    int loc = GamePlayers.at(CurrentPlayer)->getPosition();
    string pname = WATOPOLYBoard.at(loc)->getName();
    int rent = WATOPOLYBoard.at(loc)->getPrice();
    string player = GamePlayers.at(CurrentPlayer)->getPlayerName();
    string owner = WATOPOLYBoard.at(loc)->getOwner();
    cout << owner << " owns " << pname << ".  Rent is " << rent << "!" << endl;

    GamePlayers.at(getPlayerPos(owner))->changeMoney(rent);
    int rentLeftover = GamePlayers.at(CurrentPlayer)->changeMoney(0 - rent);
    if (rentLeftover > 0 ){
        
        Debt (rentLeftover, getPlayerPos(owner));
    }
}


bool Game::Debt(int amount, int reason){
    string player = getCurPlayerName();
    string owner = "The Bank";
    if (reason >= 0){
        owner = GamePlayers.at(reason)->getPlayerName();
    }
    cout << player << " owes " << amount << " to " << owner << "!" << endl;
    cout << "Enter T to Attempt a Trade, M to Mortgage a Property, " << endl;
    cout << " I to remove an Improvement, or D to Declare Bankruptcy" << endl;

    bool SuccessInput = false;
    string input;
    while (!SuccessInput && cin >> input){
        cout << player << " owes " << amount << " to " << owner << "!" << endl;
        if(input == "D"){
            cout << "Declared Bankruptcy!" << endl;
            DropOut(reason);
            return false;
        } else if (input == "T"){
            cout << "Enter Your Offer, Other Player, and What you Want" << endl;
            string asset1;
            string player2;
            string asset2;
            if (cin >> asset1 && cin >> player2 && cin >> asset2){
                Trade(asset1, player2, asset2);
            } else{
                DropOut(reason);
                return false;
            }
        } else if (input == "M"){
            cout << "Enter Property to Mortgage" << endl;
            string asset1;
            if (cin >> asset1){
                Mortgage(asset1);
            } else{
                DropOut(reason);
                return false;
            } 
        } else if (input == "I"){
            cout << "Enter Property to Remove Improvements From" << endl;
            string asset1;
            if (cin >> asset1){
                Improve(asset1, "sell");
            } else{
                DropOut(reason);
                return false;
            }
        } else{
            cout << "Invalid Input Try Again" << endl;
        }
        amount = GamePlayers.at(CurrentPlayer)->changeMoney(-amount);
        if (amount == 0){
            return true;
        }
    }
    if(!SuccessInput){
        DropOut(reason);
        return false;
    }
    return false;
}


bool Game::Trade(string CurrPlayerAsset, string OtherPlayer, string OtherPlayerAsset){
    string player = GamePlayers.at(CurrentPlayer)->getPlayerName();
    if (player == OtherPlayer){
        cout << "You cannot trade with yourself!" << endl;
        return false;
    }

    int OPlayerPos = getPlayerPos(OtherPlayer);
    if (OPlayerPos < 0 || OPlayerPos > (int) GamePlayers.size()){
        cout << "Player " << OtherPlayer << " does not exist!" << endl;
        return false;
    }
    
    bool OfferMoney = true;
    int PPos = 0;
    bool ReceiveMoney = true;
    int oPPos = 0;

    for (int i = 0; i < (int) CurrPlayerAsset.length(); i++){
        if (!isdigit(CurrPlayerAsset[i])){
            OfferMoney = false;
            break;
        }
    }
    for (int i = 0; i < (int) OtherPlayerAsset.length(); i++){
        if (!isdigit(OtherPlayerAsset[i])){
            ReceiveMoney = false;
            break;
        }
    }

    if(!OfferMoney){
        PPos = getPropertyPos(CurrPlayerAsset);
        if (PPos < 0 ){
            cout << "Property " << CurrPlayerAsset << " Does Not Exist!" << endl;
            return false;
        }
        if (WATOPOLYBoard.at(PPos)->getOwner() != player){
            cout << player << " Does Not Own " << CurrPlayerAsset << "!" << endl;
            return false;
        }
    } else{
        PPos = stoi(CurrPlayerAsset);
        if (GamePlayers.at(CurrentPlayer)->getMoney() < PPos){
            cout << player << " Does Not Have Enough Money!" << endl;
            return false;
        }
    }
    if(!ReceiveMoney){
        oPPos = getPropertyPos(OtherPlayerAsset);
        if (PPos < 0 ){
            cout << "Property " << OtherPlayerAsset << " Does Not Exist!" << endl;
            return false;
        }
        if (WATOPOLYBoard.at(oPPos)->getOwner() != OtherPlayer){
            cout << OtherPlayer << " Does Not Own " << OtherPlayerAsset << "!" << endl;
            return false;
        }
    } else{
        oPPos = stoi(OtherPlayerAsset);
        if (GamePlayers.at(OPlayerPos)->getMoney() < oPPos){
            cout << OtherPlayer << " Does Not Have Enough Money!" << endl;
            return false;
        }
    }

    cout << player << "is offering " << CurrPlayerAsset << " for " << OtherPlayerAsset << "." << endl;
    cout << OtherPlayer << ", do you accept? (Y/N)" << endl;

    bool SuccessInput = false;
    string input;
    while (!SuccessInput && cin >> input){
        if(input == "Y"){
            cout << "Trade Accepted!" << endl;
            SuccessInput = true;
        } else if (input == "N"){
            cout << "Trade Rejected!" << endl;
            return false;
        } else{
            cout << "Invalid Input Try Again" << endl;
        }
    }
    if(!SuccessInput){
        return false;
    }

    // Do the Trade
    if (OfferMoney){
        GamePlayers.at(CurrentPlayer)->changeMoney(0 - PPos);
        GamePlayers.at(OPlayerPos)->changeMoney(PPos);
    } else{
        WATOPOLYBoard.at(PPos)->changeOwners(OtherPlayer);
        GamePlayers.at(CurrentPlayer)->detach(WATOPOLYBoard.at(PPos));
        GamePlayers.at(OPlayerPos)->attach(WATOPOLYBoard.at(PPos));
    }
    if (ReceiveMoney){
        GamePlayers.at(CurrentPlayer)->changeMoney(oPPos);
        GamePlayers.at(OPlayerPos)->changeMoney(0 - oPPos);
    } else{
        WATOPOLYBoard.at(oPPos)->changeOwners(player);
        GamePlayers.at(CurrentPlayer)->attach(WATOPOLYBoard.at(oPPos));
        GamePlayers.at(OPlayerPos)->detach(WATOPOLYBoard.at(oPPos));
    }
    return true;
}

bool Game::Improve(string PropertyName, string action){
    string player = GamePlayers.at(CurrentPlayer)->getPlayerName();
    int loc = getPropertyPos(PropertyName);
    if (action != "buy" || action != "sell"){
        cout << "Invalid Improve Action!" << endl;
        return false;
    }
    //validate PropertyName
    if (loc == -1){
        cout << "Property Not Found" << endl;
        return false;
    } else if (loc==2 || loc==4 || loc==7 || loc==10 || loc==17 || loc==20 || loc==22 || loc==30 || loc==33 || loc==36 || loc==38){
        cout << "Attempting to Improve NonProperty Location!" << endl;
        return false;
    } else if (loc==5 || loc == 15 || loc == 25 || loc == 35 || loc == 12 || loc ==28){
        cout << "Attempting to Improve a Residence or Gym!" << endl;
        return false;
    } else if (WATOPOLYBoard.at(loc)->getOwner() != player){
        cout << player << " does not own " << PropertyName << "!" << endl;
        return false;
    }

    //monopoly
    if (!PartOfMonopoly(loc)){
        cout << player << " does not own " << PropertyName << "'s Monopoly!" << endl;
        return false;
    }

    //buy
    int improves = WATOPOLYBoard.at(loc)->getImproveCount();
    int improvesPrice = WATOPOLYBoard.at(loc)->getImprovePrice();
    if (action == "buy"){
        if (improves == 5){
            cout << PropertyName << " has Maxmium Improvements!" << endl;
            return false;
        }
        if (improvesPrice > GamePlayers.at(CurrentPlayer)->getMoney()){
            cout << player << " does not have enough money to improve!" << endl;
            return false;
        }
        WATOPOLYBoard.at(loc)->setImprove(improves+1);
        GamePlayers.at(CurrentPlayer)->changeMoney(-improvesPrice);
        return true;
    }
    //sell
    if (improves == 0){
        cout << PropertyName << " has No Improvements!" << endl;
        return false;
    }
    WATOPOLYBoard.at(loc)->setImprove(improves-1);
    GamePlayers.at(CurrentPlayer)->changeMoney(improvesPrice/2);
    return true;

}
    





bool Game::Mortgage(string PropertyName){
    string player = GamePlayers.at(CurrentPlayer)->getPlayerName();
    int loc = getPropertyPos(PropertyName);
    if (loc == -1){
        cout << "Property Not Found" << endl;
        return false;
    } else if (loc==2 || loc==4 || loc==7 || loc==10 || loc==17 || loc==20 || loc==22 || loc==30 || loc==33 || loc==36 || loc==38){
        cout << "Attempting to Mortgage NonProperty Location!" << endl;
        return false;
    } else if (WATOPOLYBoard.at(loc)->getOwner() != player){
        cout << player << " does not own " << PropertyName << "!" << endl;
        return false;
    } else if (WATOPOLYBoard.at(loc)->getImproveCount() > 0){
        cout << "Must remove Improvements before Mortgaging!" << endl;
        return false;
    }
    bool SMort = WATOPOLYBoard.at(loc)->mortgage();
    if (!SMort){
        return false;
    }
    int price = WATOPOLYBoard.at(loc)->getPrice();
    GamePlayers.at(CurrentPlayer)->changeMoney(price/2);
    return true;
}


bool Game::Unmortgage(string PropertyName){
    string player = GamePlayers.at(CurrentPlayer)->getPlayerName();
    int loc = getPropertyPos(PropertyName);
    if (loc == -1){
        cout << "Property Not Found" << endl;
        return false;
    } else if (loc==2 || loc==4 || loc==7 || loc==10 || loc==17 || loc==20 || loc==22 || loc==30 || loc==33 || loc==36 || loc==38){
        cout << "Attempting to Unmortgage NonProperty Location!" << endl;
        return false;
    } else if (WATOPOLYBoard.at(loc)->getOwner() != player){
        cout << player << " does not own " << PropertyName << "!" << endl;
        return false;
    } else if (GamePlayers.at(CurrentPlayer)->getMoney() < WATOPOLYBoard.at(loc)->getPrice() * 0.6){
        cout << player << " does not have enough money to unmortgage!" << endl;
        return false;
    }
    bool SMort = WATOPOLYBoard.at(loc)->unmortgage();
    if (!SMort){
        return false;
    }
    int price = WATOPOLYBoard.at(loc)->getPrice() * 0.6;
    int change = -price * 0.6;
    GamePlayers.at(CurrentPlayer)->changeMoney(change);
    return true;
}


void Game::GoToTims(){
    canMove = false;
    GamePlayers.at(CurrentPlayer)->setPosition(10);
    GamePlayers.at(CurrentPlayer)->setTimsLine(TimsLineup::Turn1);
}


void Game::TimsLine(){

}


void Game::LandOnSLC(){

}

void Game::LandOnTuition(){

}

void Game::LandOnNH(){

}

bool Game::PartOfMonopoly(int Pos){
    if (Pos < 0 || Pos > 40){
        //cout << "Invalid Position!" << endl;
        return false;
    }
    if (Pos==2||Pos==4||Pos==5||Pos==7||Pos==10||Pos==12||Pos==15||Pos==17||Pos==20
        ||Pos==22||Pos==25||Pos==28||Pos==30||Pos==33||Pos==35||Pos==36||Pos==38){
        //cout << "Property is Part of NonRegular Location!" << endl;
        return false; 
    }
    int MonopolySize = 0;
    int MonopolyCount = 0;
    if (Pos==1||Pos==3||Pos==37||Pos==39){
        MonopolySize = 2;
    } else{
        MonopolySize = 3;
    }
    string owner = WATOPOLYBoard.at(Pos)->getName();
    int LB = max(0, Pos-5);
    int UB = min(39, Pos+5);
    for (int i = LB; i < UB; i++){
        if (owner == WATOPOLYBoard.at(i)->getName()){
            MonopolyCount++;
        } if (MonopolyCount == MonopolySize){
            return true;
        }
    }
    return false;
}


void Game::RollUpTheRim(){

}
void Game::BeginAuction(int loc){

}
bool Game::DropOut(int reason){
    return false;
}
bool Game::assets(){
    return false;
}
void Game::assetsAll(){


}

