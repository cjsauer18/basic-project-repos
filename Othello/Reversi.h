#pragma once
#include <vector>
#include <iostream>

class Reversi {
private:
    const static int ROWS = 8;
    const static int COLS = 8;
    char board[ROWS][COLS];
public:
    Reversi();
    int count (char color);
    void setDisk (int row, int col, char color);//need to edit to place only diagonal from opponent piece
    void resultOfMove (int row, int col, char color);//flips over disks as a result of move
    void bestMove(int& row, int& col, int& flipped, char color);//greedy algorithm
    void printBoard ( );
    void resetBoard ( );
   //additional methods
    void printBoard(std::vector<std::pair<int,int>> index);//override of printBoard
    int resultCount (int row, int col, char color);//auxillary
    bool checkWin(char p1, char p2);
    void displayMove(char color);
    std::vector<std::pair<int, int>> getIndex(char color);//auxillary
};

