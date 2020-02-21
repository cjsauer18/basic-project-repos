#include "Reversi.h"
#include <iostream>
#include <string>
using namespace std;


void Rules(){//rules
    cout << "Movement rules for Othello: "<< endl;
    cout << "A player must place their disk such that: " << endl;
    cout << "1) The disk placed creates a straight line (horizontally, vertically, or diagonally) between the newly placed disk and another of the player's disks" << endl;
    cout << "2) There must be one or more of the opponent's disks between the current player's disks." << endl;
}


//swap function, takes player 1 and player 2 and switches their order for gameLoop.
//pre: player variables must be supplied to be flipped
void Swap(char& p1, string& p1S, char& p2, string& p2S){//string identifiers for display heading
    string tempS; char temp;
    tempS = p1S;
    p1S = p2S;
    p2S = tempS;
    temp = p1;
    p1 = p2;
    p2 = temp;
}
//post: changes player for turn
int main() {
    int col = 0; int row;
    string p1S = "Player 1: Black";//player identifer
    string p2S = "Player 2: White";//player identifer
    int flipped;
    char p1 = 'b'; char p2 = 'w';
    
    cout << "=-------------------------------=" << endl;
    cout << "             OTHELLO" << endl;
    cout << "=-------------------------------=" << endl;
    cout << endl << endl << endl;
    cout << "Player with the most spaces wins!" << endl;
    
    Reversi myGame;//intialize game
    myGame.printBoard();//intial standard print
    cout << endl;
    char play = 'y';
    //game loop
    while(play == 'y'){//play condition
        cout << p1S <<  endl;//player heading
        int selection;//separate sections into black and white alternating
        bool valid = false;//row/col entry indicator
        cout << "Menu:\n1) Place a disk \n2) See movement rules \n3) Display possible moves \n4) Display best move" << endl;
        cout << "Selection: ";
        cin >> selection;//menu choice
        if(selection == 1){
            while(valid == false){
                cout << "State the row (0-7) and col (0-7) of the square where you want to place a disk: ";
                 cin >> row >> col;//player input
                try{
                    myGame.setDisk(row, col, p1);//if valid, set
                    valid = true;//is valid
                }catch (exception){//error (non valid entry thrown from "setDisk" method.
                    cout << "disk space invalid, try again!" << endl;
                }
            }
            myGame.resultOfMove(row, col, p1);//result of disk being placed
            myGame.printBoard();//display new board
            Swap(p1, p1S, p2, p2S);//swap players, turn is over.
        }
        else if(selection == 2){
            Rules();//show rules
            continue;
        }
        else if(selection == 3){
            myGame.displayMove(p1);//display possible moves to player
            continue;
        }
        else if(selection == 4){
            myGame.bestMove(row, col, flipped, p1);//display best possible move location to player

            continue;
        }
        else{
            cout << "Invalid Entry, try again" << endl;//wrong select int is inputted.
        }
       

        if(myGame.checkWin(p1, p2) == true){//if game is won
            cout << "Play again? (y/n): ";
            do{
            char selection;
            cin >> selection;
            if(selection == 'y'){
                myGame.resetBoard();//reset board
                break;//start again
            }
            else if(selection == 'n'){
                play = 'n';//break while loop
                break;//end program
            }else{
                cout << "Error, Play again? (y/n): ";//reprompt
            }
            }while(selection != 'y' && selection != 'n');
        }
      
    }
}



