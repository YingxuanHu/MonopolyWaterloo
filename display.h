#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"
using namespace std;

//class Game;

class Display {
    public:
    void DisplayBoard(Game & g);  //Displays whole board
    
    void DisplayImprove(int ImproveCount); //Displays improvements given count
    void DisplayPlayerBlock(int loc, Game & g); //Displays Players at a Location
    void DisplayEmptyBlock();
    void DisplayEmptyRow();
    void DisplayEmptyRowMiddle();
    void DisplayBottomRow();
    void DisplayBottomRowMiddle();
    
    void DisplayTopBlockRow(Game &g);
    void DisplayMiddleBlockRow(Game &g, int left, int right);
    void DisplaySLCBlockRow(Game &g);
    void DisplayNameRows(Game &g);
    void DisplayPACBlockRow(Game&g);
    void DisplayBottomBlockRow(Game &g);
};


#endif

