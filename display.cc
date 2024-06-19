#include "display.h"
#include <iostream>
#include <iomanip>


void Display::DisplayBoard(Game & g){
    DisplayTopBlockRow(g);
    DisplayMiddleBlockRow(g, 19, 31);
    DisplayBottomRowMiddle();
    DisplayMiddleBlockRow(g, 18, 32);
    DisplayBottomRowMiddle();
    DisplaySLCBlockRow(g);
    DisplayNameRows(g);
    DisplayMiddleBlockRow(g, 13, 37);
    DisplayBottomRowMiddle();
    DisplayPACBlockRow(g); 
    DisplayMiddleBlockRow(g, 11, 39);
    DisplayBottomBlockRow(g);

    for (auto i = 0; i < (int) g.GamePlayers.size(); i++){
        string player = g.GamePlayers.at(i)->getPlayerName();
        int ploc = g.GamePlayers.at(i)->getPosition();
        cout << "Player " << player << " is at " << ploc << endl;
    }
    cout << g.getCurPlayerName() << "'s turn:";
}


void Display::DisplayImprove(int ImproveCount){
    if (ImproveCount < 0 || ImproveCount > 5){
        ImproveCount = 0;
    }
    cout << "  ";
    if (ImproveCount == 0){
        cout << "     ";
    } else if(ImproveCount == 1){
        cout << "  I  ";
    } else if(ImproveCount == 2){
        cout << " II  ";
    } else if(ImproveCount == 3){
        cout << " III ";
    } else if(ImproveCount == 4){
        cout << "IIII ";
    } else{
        cout << "IIIII";
    }
    cout << " |";
}


void Display::DisplayPlayerBlock(int loc, Game & g){
    string PlayersHere = "";
    for (auto player : g.GamePlayers){
        if(player->getPosition() == loc){
            PlayersHere += player->getPlayerToken();
        }
    }
    int edge = 8 - PlayersHere.length();
    if (edge % 2 == 0){
        cout << setfill(' ') << setw(edge/2) << "";
        cout << PlayersHere;
        cout << setfill(' ') << setw(edge/2) << "";
    } else{
        edge -= 1;
        cout << setfill(' ') << setw(edge/2) << "";
        cout << PlayersHere;
        cout << setfill(' ') << setw(edge/2) << "";
        cout << " ";
    }
    cout << "|"; 
}


void Display::DisplayEmptyBlock(){
    cout << setfill(' ') << setw(8) << "" << "|";
}


void Display::DisplayEmptyRow(){
    cout << "|";
    for (int i = 0; i < 11; i++){
        DisplayEmptyBlock();
    }
    cout << endl;
}


void Display::DisplayEmptyRowMiddle(){
    cout << "|";
    DisplayEmptyBlock();
    cout << setfill(' ') << setw(80) << "";
    cout << "|";
    DisplayEmptyBlock();
    cout << endl;
}


void Display::DisplayBottomRow(){
    cout << "|";
    for (int i = 0; i < 11; i++){
        cout << setfill('_') << setw(8) << "" << "|";
    }
    cout << endl;
}


void Display::DisplayBottomRowMiddle(){
    cout << "|";
    cout << setfill('_') << setw(8) << "" << "|";
    cout << setfill(' ') << setw(80) << "" << "|";
    cout << setfill('_') << setw(8) << "" << "|";
    cout << endl;
}


void Display::DisplayTopBlockRow(Game &g){
    cout << setfill('_') << setw(100) << "" << endl;

    cout << "|Goose   |";
    DisplayImprove(g.WATOPOLYBoard.at(21)->getImproveCount());
    cout << "NEEDLES |";
    DisplayImprove(g.WATOPOLYBoard.at(23)->getImproveCount());
    DisplayImprove(g.WATOPOLYBoard.at(24)->getImproveCount());
    cout << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(25)->getName() << "|";
    DisplayImprove(g.WATOPOLYBoard.at(26)->getImproveCount());
    DisplayImprove(g.WATOPOLYBoard.at(27)->getImproveCount());
    cout << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(28)->getName() << "|";
    DisplayImprove(g.WATOPOLYBoard.at(29)->getImproveCount());
    cout << "GO TO   |" << endl;

    cout << "|Nesting |";
    cout << setfill('-') << setw(8) << "" << "|";
    cout << "HALL    |";
    cout << setfill('-') << setw(8) << "" << "|";
    cout << setfill('-') << setw(8) << "" << "|";
    cout << setfill(' ') << setw(8) << "" << "|";
    cout << setfill('-') << setw(8) << "" << "|";
    cout << setfill('-') << setw(8) << "" << "|";
    cout << setfill(' ') << setw(8) << "" << "|";
    cout << setfill('-') << setw(8) << "" << "|";
    cout << "TIMS    |" << endl;

    cout << "|";
    DisplayEmptyBlock();
    cout << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(21)->getName() << "|";
    DisplayEmptyBlock();
    cout << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(23)->getName() << "|";
    cout << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(24)->getName() << "|";
    DisplayEmptyBlock();
    cout << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(26)->getName() << "|";
    cout << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(27)->getName() << "|";
    DisplayEmptyBlock();
    cout << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(29)->getName() << "|";
    DisplayEmptyBlock();
    cout << endl;
    
    cout << "|";
    for (int i = 20; i <= 30; i++){
        DisplayPlayerBlock(i, g);
    }
    cout << endl;

    DisplayBottomRow();
}


void Display::DisplayMiddleBlockRow(Game & g, int left, int right){
    cout << "|";
    DisplayImprove(g.WATOPOLYBoard.at(left)->getImproveCount());
    cout << setfill(' ') << setw(80) << "" << "|";
    DisplayImprove(g.WATOPOLYBoard.at(right)->getImproveCount());
    cout << endl;

    cout << "|";
    cout << setfill('-') << setw(8) << "" << "|";
    cout << setfill(' ') << setw(80) << "" << "|";
    cout << setfill('-') << setw(8) << "" << "|";
    cout << endl;

    cout << "|";
    cout << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(left)->getName() << "|";
    cout << setfill(' ') << setw(80) << "" << "|";
    cout << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(right)->getName() << "|";
    cout << endl;

    cout << "|";
    DisplayPlayerBlock(left, g);
    cout << setfill(' ') << setw(80) << "" << "|";
    DisplayPlayerBlock(right, g);
    cout << endl;
}


void Display::DisplaySLCBlockRow(Game &g){
    cout << "|";
    cout << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(17)->getName() << "|";
    cout << setfill(' ') << setw(80) << "" << "|";
    cout << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(33)->getName() << "|";
    cout << endl;

    DisplayEmptyRowMiddle();
    DisplayEmptyRowMiddle();

    cout << "|";
    DisplayPlayerBlock(17, g);
    cout << setfill(' ') << setw(80) << "" << "|";
    DisplayPlayerBlock(33, g);
    cout << endl;

    DisplayBottomRowMiddle();
}


void Display::DisplayNameRows(Game &g){
    //Block 16/34
    cout << "|";
    DisplayImprove(g.WATOPOLYBoard.at(16)->getImproveCount());
    cout << setfill(' ') << setw(80) << "" << "|";
    DisplayImprove(g.WATOPOLYBoard.at(34)->getImproveCount());
    cout << endl;

    cout << "|";
    cout << setfill('-') << setw(8) << "" << "|";
    cout << setfill(' ') << setw(80) << "" << "|";
    cout << setfill('-') << setw(8) << "" << "|";
    cout << endl;

    cout << "|";
    cout << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(16)->getName() << "|";
    cout << setfill(' ') << setw(80) << "" << "|";
    cout << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(34)->getName() << "|";
    cout << endl;

    cout << "|";
    DisplayPlayerBlock(16, g);
    cout << setfill(' ') << setw(14) << "";
    cout << setfill('_') << setw(52) << "";
    cout << setfill(' ') << setw(14) << "" << "|";
    DisplayPlayerBlock(34, g);
    cout << endl;

    cout << "|";
    cout << setfill('_') << setw(8) << "" << "|";
    cout << setfill(' ') << setw(13) << "" << "|";
    cout << setfill(' ') << setw(52) << "" << "|";
    cout << setfill(' ') << setw(13) << "" << "|";
    cout << setfill('_') << setw(8) << "" << "|";
    cout << endl;

    //Block 15/35
    cout << "|" << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(15)->getName() << "|";
    cout << setfill(' ') << setw(13) << "";
    cout << "| #   #   ##   #####  ###   ####    ###   #    #   # |";
    cout << setfill(' ') << setw(13) << "";
    cout << "|" << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(35)->getName() << "|" << endl;

    cout << "|" << setfill(' ') << setw(8) << "" << "|";
    cout << setfill(' ') << setw(13) << "";
    cout << "| #   #  #  #    #   #   #  #   #  #   #  #    #   # |";
    cout << setfill(' ') << setw(13) << "";
    cout << "|" << setfill(' ') << setw(8) << "" << "|" << endl;

    cout << "|" << setfill(' ') << setw(8) << "" << "|";
    cout << setfill(' ') << setw(13) << "";
    cout << "| # # #  ####    #   #   #  ####   #   #  #     # #  |";
    cout << setfill(' ') << setw(13) << "";
    cout << "|" << setfill(' ') << setw(8) << "" << "|" << endl;

    cout << "|";
    DisplayPlayerBlock(15, g);
    cout << setfill(' ') << setw(13) << "";
    cout << "| # # #  #  #    #   #   #  #      #   #  #      #   |";
    cout << setfill(' ') << setw(13) << "" << "|";
    DisplayPlayerBlock(35, g);
    cout << endl;

    cout << "|";
    cout << setfill('_') << setw(8) << "" << "|";
    cout << setfill(' ') << setw(13) << "";
    cout << "| # # #  #  #    #    ###   #       ###   ####   #   |";
    cout << setfill(' ') << setw(13) << "" << "|";
    cout << setfill('_') << setw(8) << "" << "|";
    cout << endl;

    //Block 14/36
    cout << "|";
    DisplayImprove(g.WATOPOLYBoard.at(14)->getImproveCount());
    cout << setfill(' ') << setw(14) << "";
    cout << setfill('_') << setw(52) << "";
    cout << setfill(' ') << setw(14) << "" << "|";
    cout << setfill(' ') << setw(8) << "NEEDLES" << "|";
    cout << endl;

    cout << "|";
    cout << setfill('-') << setw(8) << "" << "|";
    cout << setfill(' ') << setw(80) << "" << "|";
    cout << setfill(' ') << setw(8) << "HALL" << "I";
    cout << endl;

    cout << "|";
    cout << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(14)->getName() << "|";
    cout << setfill(' ') << setw(80) << "" << "|";
    cout << setfill(' ') << setw(8) << "" << "|";
    cout << endl;

    cout << "|";
    DisplayPlayerBlock(14, g);
    cout << setfill(' ') << setw(80) << "" << "|";
    DisplayPlayerBlock(36, g);
    cout << endl;

    DisplayBottomRowMiddle();
}


void Display::DisplayPACBlockRow(Game&g){
    cout << "|";
    cout << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(12)->getName() << "|";
    cout << setfill(' ') << setw(80) << "" << "|";
    cout << setfill(' ') << setw(8) << "COOP" << "|";
    cout << endl;

    cout << "|";
    cout << setfill(' ') << setw(8) << "" << "|";
    cout << setfill(' ') << setw(80) << "" << "|";
    cout << setfill(' ') << setw(8) << "FEE" << "|";
    cout << endl;

    DisplayEmptyRowMiddle();

    cout << "|";
    DisplayPlayerBlock(12, g);
    cout << setfill(' ') << setw(80) << "" << "|";
    DisplayPlayerBlock(38, g);
    cout << endl;

    DisplayBottomRowMiddle();
}


void Display::DisplayBottomBlockRow(Game &g){
    cout << "|" << setfill('_') << setw(8) << "" << "|";
    cout << setfill('_') << setw(80) << "";
    cout << "|" << setfill('_') << setw(8) << "" << "|" << endl;

    cout << "|DC Tims |";
    DisplayImprove(g.WATOPOLYBoard.at(9)->getImproveCount());
    DisplayImprove(g.WATOPOLYBoard.at(8)->getImproveCount());
    cout << "NEEDLES |";
    DisplayImprove(g.WATOPOLYBoard.at(6)->getImproveCount());
    cout << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(5)->getName() << "|";
    cout << "TUITION |";
    DisplayImprove(g.WATOPOLYBoard.at(3)->getImproveCount());
    cout << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(2)->getName() << "|";
    DisplayImprove(g.WATOPOLYBoard.at(1)->getImproveCount());
    cout << "COLLECT |" << endl;

    cout << "|" << setfill(' ') << setw(8) <<"Line" << "|";
    cout << setfill('-') << setw(8) << "" << "|";
    cout << setfill('-') << setw(8) << "" << "|";
    cout << setfill(' ') << setw(8) << "HALL" << "|";
    cout << setfill('-') << setw(8) << "" << "|";
    cout << setfill(' ') << setw(8) << "" << "|";
    cout << setfill(' ') << setw(8) << "" << "|";
    cout << setfill('-') << setw(8) << "" << "|";
    cout << setfill(' ') << setw(8) << "" << "|";
    cout << setfill('-') << setw(8) << "" << "|";
    cout << setfill(' ') << setw(8) << "OSAP" << "|" << endl;

    cout << "|";
    DisplayEmptyBlock();
    cout << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(9)->getName() << "|";
    cout << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(8)->getName() << "|";
    DisplayEmptyBlock();
    cout << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(6)->getName() << "|";
    DisplayEmptyBlock();
    DisplayEmptyBlock();
    cout << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(3)->getName() << "|";
    DisplayEmptyBlock();
    cout << setfill(' ') << setw(8) << g.WATOPOLYBoard.at(1)->getName() << "|";
    DisplayEmptyBlock();
    cout << endl;
    
    cout << "|";
    for (int i = 10; i >= 0; i--){
        DisplayPlayerBlock(i, g);
    }
    cout << endl;

    DisplayBottomRow();
}
