#include <iostream>
#include "Solitaire.h"
#include "Deck.h"
#include "Card.h"
#include <vector>
#include <time.h>
#include <stdlib.h>
using namespace std;

//Menu display
void menu(){
    cout << "Options" << endl;
    cout << "(1) Move card to sort pile" << endl;
    cout << "(2) Move card(s) between piles" << endl;
    cout << "(3) Deal from discard pile" << endl;
    cout << "'exit' to quit" << endl;
    cout << "Selection: ";
}

int main() {

     Deck gameDeck;
  //  sorting algorithms
    gameDeck.sortIncreasing();
    gameDeck.printDeck();
    gameDeck.sortDecreasing();
    gameDeck.printDeck();
    gameDeck.Shuffle();
    gameDeck.printDeck();
    gameDeck.Shuffle();
    gameDeck.Shuffle();
    Solitaire Game;
    Game.initializeGame(gameDeck);//initialize piles
    bool run = true;
    while(run == true){
        cout << "Deck size: " << gameDeck.getDeckSize() << endl;
        Game.printDisplay();
        menu();
        string selection;
        cin >> selection;
        transform(selection.begin(), selection.end(), selection.begin(), ::tolower);
        if(selection == "exit"){
            cout << "Are you sure you want to exit? (y/n)" << endl;
            while(true){
                string selection;
                cin >> selection;
                if(selection == "y"){
                    cout << "Game lost. Score: " << Game.getScore();
                    run = false;
                    break;
                }else if(selection == "n"){
                    break;
                }else{
                    cin.clear();
                    cin.ignore();
                    cout << "(y/n)? " << endl;
                }
            }
        }
        if(selection == "1"){
            int pile;
            char newPile;
            cout << "Enter pile number of card to move, and character of sorted pile (Pile #, Sorted Pile)." << endl;
            cin >> pile >> newPile;
            try{
                Game.moveToPile(pile, newPile);
            }catch(const char* msg){
                cout << msg << endl;
                cin.clear();
                cin.ignore();
            }
        }else if(selection == "2"){
            int pile;
            int newPile;
            cout << "Enter pile number of card(s) to move, and pile number of new pile (#, #)" << endl;
            cin >> pile >> newPile;
            try{
                Game.moveToPile(pile, newPile);
            }catch(const char* msg){
                cout << msg << endl;
                cin.clear();
                cin.ignore();
            }
        }else if(selection == "3"){
            Game.moveFromDiscard();
        }else{
            cin.clear();
            cin.ignore();
        }
        if(Game.didWin()){
            cout << "You won! Score: " << Game.getScore() << endl;
            cout << "Play again? ";
            string selection;
            while(true){
                cin >> selection;
                if(selection == "y"){
                    gameDeck.clearDeck();
                    gameDeck.initializeDeck();
                    gameDeck.Shuffle();
                    Game.initializeGame(gameDeck);
                    break;
                }else if(selection == "n"){
                    cout << "Bye" << endl;
                    run = false;
                    break;
                }else{
                    cin.clear();
                    cin.ignore();
                    cout << "(y,n)? ";
                }
            }
        }
    }
}


