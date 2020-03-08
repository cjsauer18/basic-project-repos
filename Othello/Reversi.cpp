#include <iostream>
#include "Reversi.h"
#include <string>
#include <vector>
using namespace std;

//Constructor initialized board upon call.
//Default constructor
//Post: returns initialized board of ' ' values (empty board)
Reversi::Reversi(){
    for(int row = 0; row < 8; ++row){
        for(int col = 0; col < 8; ++col){
            board[row][col] = ' ';//set equal to ' '
        }
    }
    //standard initialized values
    board[3][3] = {'b'};
    board[3][4] = {'w'};
    board[4][4] = {'b'};
    board[4][3] = {'w'};
}


//Method sorts through array and counts how many values of color are present..
//Returns incremented counter. (player score)
//pre: board must be initialized.
int Reversi::count (char color){
    int temp = 0;
    for(int row = 0; row < 8; ++row){
        for(int col = 0; col < 8; ++col){
            if(board[row][col] == color){
                temp++;//increment if found
            }
        }
    }
    return temp;//return value
}
//Post: returns amout of disks (corresponding to individual player).

//Method takes row/col from user input, and places tile in board array.
//Pre: board must be initlaized, user input of row/col must be supplied.
//Post: if valid disk space is selected by user, disk will be placed.
//if tile is open, disk is placed in tile positon.
void Reversi::setDisk (int row, int col, char color){
    vector<pair<int,int>>index = getIndex(color);
    vector<pair<int,int>>::iterator it;
    int counter = static_cast<int>(index.size());
    if(board[row][col] == ' '){
        for(it = index.begin(); it != index.end(); ++it){
            if(it->first == row && it->second == col){
                board[row][col] = {color};//
                counter--;//a matching value is found, disk is placed
            }
        }
        if(counter == index.size()){
            throw exception();//disk is not placed
        }
    }else{
        throw exception();
    }
}

//Upon user row/col input in gameEngine, this method is called to sort through the
//region that the disk was placed and find possible flipped disks.
//If opponent disk is found, function keeps seaching and indexes found values to be set to new color.
//Pre: board must be initialized, user input of row and col must be supplied.
//Post: board is changed in that the player flips the disks of the opponent.
void Reversi::resultOfMove (int row, int col, char color){
    pair<int, int> index;
    vector<pair<int, int>> indexList;//vector of pairs (index)
    vector<pair<int, int>>::iterator it;//iterate through vector of pairs
    int tempRow = 0;
    int tempCol = 0;
    for(int i = -1; i < 2; i++){//locator within one space region
        for(int j = -1; j < 2; j++){//column locator
            if(board[row+i][col+j] != color && board[row+i][col+j] != ' '){//if opponent color is found
                tempRow = row;
                tempCol = col;
                while(board[tempRow+i][tempCol+j] != color && board[tempRow+i][tempCol+j] != ' '){//search via current increment
                    tempRow = tempRow+i;//keep searching that pathway
                    tempCol = tempCol+j;//keep searching that pathway
                    if((tempRow > 7 || tempCol > 7) || (tempRow < 0 || tempCol < 0)){//error handling (index out of range of board);
                        break;
                    }else{
                        index.first = tempRow;
                        index.second = tempCol;
                        indexList.push_back(index);//index row/col value found
                    }
                }
                if(board[tempRow+i][tempCol+j] == color){//if end result is valid (disk of same color)
                    for(it = indexList.begin(); it != indexList.end(); ++it){//set previous disks to color
                        board[it->first][it->second] = {color};
                    }
                }else{
                    indexList.clear();//error handle (if inconclusive)
                }
                }
            }
    }
}


//Instead of storing values to flip, function returns a count of flipped values
//of the values found (row/col) that would be flipped if color is placed on that tile.
//Pre: player input of row, col and given color.
//Post: int counter is returned as the number of flipped disks
int Reversi::resultCount(int row, int col, char color){
    int counter = 0;
    int tempRow = 0;
    int tempCol = 0;
    for(int i = -1; i < 2; i++){//phase one, locator within one space region
        for(int j = -1; j < 2; j++){
            if(row+i < 0 || col+j < 0){
                continue;
            }
            if(board[row+i][col+j] != color && board[row+i][col+j] != ' '){
                tempRow = row;
                tempCol = col;
                while(board[tempRow+i][tempCol+j] != color && board[tempRow+i][tempCol+j] != ' '){//if tile location has possible match //search via current incriment
                    tempRow = tempRow+i;
                    tempCol = tempCol+j;
                    if((tempRow > 7 || tempCol > 7) || (tempRow < 0 || tempCol < 0)){//error handling (index)
                    break;
                    }else{
                    counter++;  //increment location found (tile flipped
                }
                }
                if(board[tempRow+i][tempCol+j] == color){//if tile search is conclusive (reached color)
                    return counter;//return counted values flipped
                }else{
                    counter = 0;//error handling (out of range)
                }
            }
        }
    }
    return counter;
}


//This function consists of a greedy algorithm, which sorts through the value returned from "resultMove"
//which indicates the most flipped tiles from a possible move. Returns index of row and col value where
//Pre: player input of row, col and given color. Flipped is given from initial function call.
//Post: Program outputs row and column that results in the most disks flips.
//returns cout text containing row and column index that corresponds to the best move (highest turnover)
//for the current turn.
void Reversi::bestMove(int& row, int& col, int& flipped, char color){
    int biggest = 0;
    for(int r = 0; r < 8; ++r){//sort through board array
        for(int c = 0; c < 8; ++c){
            if(board[r][c] == ' '){//if position in board is free
                flipped = resultCount(r, c, color);//find best move
            if(biggest < flipped){//if flipped (found in search) is bigger than "biggest"
                biggest = flipped;
                row = r;//row index
                col = c;//col index
            }else if(biggest == flipped){
                continue;//if same value is found, keep value of smaller row.
            }
        }
        }
    }
    //row, col index is outputted, along with biggest number.
    cout << "Your best move is: " << row << ", " << col << " and will result in a +" << biggest << " score differential." << endl;
}

//Standard print board function. Prints out contents of board array when called. Board must be initialized.
//Pre: board must be intialized (reset, or constructor).
//Post: board is outputted with formatting and numbered rows/cols.
//prints out structured board with dimentions and space orientation.
void Reversi::printBoard (){
     cout << endl;
     cout << "    0   1   2   3   4   5   6   7 " << endl;
     for(int row = 0; row < 8; row++){
        cout << "-----------------------------------";
        cout << endl;
        cout << row << " | ";
        for(int col = 0; col < 8; col++){
            cout << board[row][col] << " | ";
        }
         cout << endl;
     }
    cout << "-----------------------------------" << endl << endl;
}


//Overloaded printBoard funcion. Takes in vector of pairs from displayMove function call, which supplies index values of possible moves.
//Pre: index vector must be passed in and intialized with values
//Post: board is printed with indexed "x" spots in correct location.
//prints out board with added "x"s to board. The "x"s are removed (returned to normal) from position after initial board is displayed.
void Reversi::printBoard(vector<pair<int, int>> index){//overloaded printBoard funcion. Takes
     vector<pair<int, int>>::iterator it;
     for(it = index.begin(); it != index.end(); it++){//iterate through indexes
           board[it->first][it->second] = {'x'};//add to board to print
     }
    //standard print board (with new values added)
    cout << endl;
    cout << "    0   1   2   3   4   5   6   7 " << endl;
     for(int row = 0; row < 8; row++){
        cout << "-----------------------------------";
        cout << endl;
        cout << row << " | ";
        for(int col = 0; col < 8; col++){
            cout << board[row][col] << " | ";
        }
         cout << endl;
    }
    for(it = index.begin(); it != index.end(); it++){//values are removed from board after being displayed
           board[it->first][it->second] = {' '};
       }
    cout << "-----------------------------------" << endl << endl;
}

//Resets board
//Pre: board must exist and be initialized.
//Post: board is reset to standard starting form.
void Reversi::resetBoard ( ){
    for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){
            board[row][col] = ' ';
        }
    }
    board[3][3] = {'B'};
    board[3][4] = {'W'};
    board[4][4] = {'B'};
    board[4][3] = {'W'};
}


//Auxillary function checks if there is a winner
//board is checked for winner every move.
//checks win cases
//Pre: board must contain winning indicator (no possible new places to go)
//Post: boolean is returned indicating winner status, returns true if win conditions are satisfied, false otherwise.
bool Reversi::checkWin(char p1, char p2){//rename temp?
    auto p1Points = count(p1);//point counters
    auto p2Points = count(p2);
    auto p1index = getIndex(p1);//possible move counters
    auto p2index = getIndex(p2);
    if(p1index.size() == 0 && p2index.size() == 0){
        if(p1Points > p2Points){
            cout << "Congradulations! Player 1 has won the game! (" << p1Points << "-" << p2Points << ")" << endl;
            return true;
        }else if(p1Points < p2Points){
            cout << "Congradulations! Player 2 has won the game! (" << p1Points << "-" << p2Points << ")" << endl;
            return true;
        }else if(p1Points == p2Points){
            cout << "Draw!" << "(" << p1Points << "-" << p2Points << ")" << endl;
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

//Function sorts through board array and locates opponent disks that satisfiy possible
//move locations for player 1. If position is free and valid, function indexes disk location
//and calls displayBoard with vector of indexes as parameter.
//Pre: board must be populated with values to flag in order to locate possible moves.
//Post: board is reprinted with printBoard being overriden with a vector of pairs parameter.
void Reversi::displayMove(char color){
    pair<int, int> tempIndex; //row/col index
    vector<pair<int, int>>Index;
    for(int row = 0; row < 8; row++){//sort through array
        for(int col = 0; col < 8; col++){
            if(board[row][col] == ' ' && resultCount(row, col, color) != 0){
                tempIndex.first = row;
                tempIndex.second = col;
                Index.push_back(tempIndex);//Index location
            }
        }
    }
    printBoard(Index);//calls printBoard, sends disk locations in vector.
}

//Auxillary function, provides index for set disk as well as dispaly moves for valid openings
//Pre: board must be populated with meaningful (valid) values to index
//Post: returns vector of indexes to be used for other function needs.
vector<pair<int,int>> Reversi::getIndex(char color){
pair<int, int> tempIndex; //row/col index
vector<pair<int,int>>Index;
for(int row = 0; row < 8; row++){//sort through array
    for(int col = 0; col < 8; col++){
        if(board[row][col] == ' ' && resultCount(row, col, color) != 0){
            tempIndex.first = row;
            tempIndex.second = col;
            Index.push_back(tempIndex);//Index location
       }
    }
}
    return Index;
}
//Function sends in indexed values to printBoard and displays to user possible
//(valid) locations to place disk.
