#include <iostream>
#include "Solitaire.h"
#include <vector>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <sstream>

using namespace std;

Solitaire::Solitaire(){}//deal starting hand
//Desc: Function intializes the solitare game by dealing out cards from the deck to each pile.
//Pre: Requires deck address
//Post: Fills card pile stacks with cards
void Solitaire::initializeGame(Deck& newDeck){
    cout << "Enter player name" << endl;
    cin >> name;
    deck = &newDeck;
    CardPileStack* tempSeventh = new CardPileStack;
    CardPileStack* tempSixth = new CardPileStack;
    CardPileStack* tempFifth = new CardPileStack;
    CardPileStack* tempFourth = new CardPileStack;
    CardPileStack* tempThird = new CardPileStack;
    CardPileStack* tempSecond = new CardPileStack;
    CardPileStack* tempFirst = new CardPileStack;
    vector<CardPileStack*>temp;//load in opposite order
    temp.push_back(tempFirst);
    temp.push_back(tempSecond);
    temp.push_back(tempThird);
    temp.push_back(tempFourth);
    temp.push_back(tempFifth);
    temp.push_back(tempSixth);
    temp.push_back(tempSeventh);
    for(int i = 0; i < temp.size(); ++i){
        for(int j = i; j < temp.size(); ++j){
            temp[j]->insert(deck->getCard());
        }
    }
    firstStack = *tempFirst;
    delete tempFirst;
    secondStack = *tempSecond;
    delete tempSecond;
    thirdStack = *tempThird;
    delete tempThird;
    fourthStack = *tempFourth;
    delete tempFourth;
    fifthStack = *tempFifth;
    delete tempFifth;
    sixthStack = *tempSixth;
    delete tempSixth;
    seventhStack = *tempSeventh;
}
//Desc: Method prints out the game board, as well as outputs an image of the board to a separate file.
//Pre: Requires game to be initialized
//Post: Output file is appended, output console display is updated with next move.
void Solitaire::printDisplay(){
    output.open("cis200solitaire.txt", 'w');
    cout << endl << endl;
    auto heartsTop = hearts.peek();
    auto clubsTop = clubs.peek();
    auto spadesTop = spades.peek();
    auto diamondsTop = diamonds.peek();
    auto discardTop = discardPile.peek();
    cout << setw(35) << " " << name << "'s Game" << endl;
    cout << setw(33) << " " << "Player Score: " << score << endl;
    output << setw(35) << " " << name << "'s Game" << endl << "Player Score " << score << endl;
    string firstOutput; string secondOutput; string thirdOutput; string fourthOutput; string fifthOutput; string sixthOutput; string seventhOutput;
    int biggest = findBiggest(firstStack, secondStack, thirdStack, fourthStack, fifthStack, sixthStack, seventhStack);
    for(int i = 0; i < biggest; ++i){
        formatStackOutput(firstOutput, i, firstStack);
        formatStackOutput(secondOutput, i, secondStack);
        formatStackOutput(thirdOutput, i, thirdStack);
        formatStackOutput(fourthOutput, i, fourthStack);
        formatStackOutput(fifthOutput, i, fifthStack);
        formatStackOutput(sixthOutput, i, sixthStack);
        formatStackOutput(seventhOutput, i, seventhStack);
        if(i == 0){
            cout << setw(10);
            cout << left << "Heart Pile: "  << heartsTop << setw(5) <<" " << "Diamond Pile: " << diamondsTop << setw(5) <<" "
            << "Spade Pile: " << spadesTop << setw(5) <<" "<< "Club Pile: "<< clubsTop << endl;
            cout  << "Pile 1: " << setw(5) << firstOutput << "Pile 2: " << setw(5) << secondOutput << "Pile 3: " << setw(5)<< thirdOutput<<
            "Pile 4: " << setw(5) << fourthOutput<< "Pile 5: " << setw(5)<< fifthOutput << "Pile 6: " <<setw(5)<< sixthOutput << "Pile 7: " << setw(5)<< seventhOutput << endl;
            output << setw(10) << left << "Heart Pile: "  << heartsTop << setw(5) <<" " << "Diamond Pile: " << diamondsTop << setw(5) <<" "
                       << "Spade Pile: " << spadesTop << setw(5) <<" "<< "Club Pile: "<< clubsTop << endl;
            output << "Pile 1: " << setw(5) << firstOutput << "Pile 2: " << setw(5) << secondOutput << "Pile 3: " << setw(5)<< thirdOutput<<
                       "Pile 4: " << setw(5) << fourthOutput<< "Pile 5: " << setw(5)<< fifthOutput << "Pile 6: " <<setw(5)<< sixthOutput << "Pile 7: " << setw(5)<< seventhOutput << endl;
        }else{
            cout << right << setw(9) << firstOutput << setw(13)  << secondOutput << setw(13)<< thirdOutput << setw(13) << fourthOutput << setw(13) << fifthOutput << setw(13) <<  sixthOutput << setw(13) << seventhOutput << endl;
            output << right << setw(9) << firstOutput << setw(13)  << secondOutput << setw(13)<< thirdOutput << setw(13) << fourthOutput << setw(13) << fifthOutput << setw(13) <<  sixthOutput << setw(13) << seventhOutput << endl;
        }
    }
    cout  << "Deck []" << setw(10) << " " << "Discard: " << discardTop << endl;
    output << "Deck []" << setw(10) << " " << "Discard: " << discardTop << endl;
    output.close();
}
//Desc: One of two direct insertion functions that inserts a card to a pile after checking validity
//Pre: Requires pile number and card to be inserted.
//Post: If placement is valid, card is added to stack, stack is updated.
void Solitaire::insertBack(Card c, int Pile){//primarily used for dealing out from the deck
    CardPileStack temp;
    temp = getCardStack(Pile);
    if(temp.peek()-1 == c && (!temp.isSameColor(c, 1))){//inserting at top, reach is just one, unlike moving a pile
        temp.insert(c);
        temp.setOverturned(temp.getOverturned()+1);
        setCardPile(temp, Pile);
    }
}

//Desc: Second direct insertion primarily called from discard pile. Handles both instances of suite pile and
//standard piles
//Pre: Requires discard pile to be called from user with assosiated methods.
//Post: Checks and sets card in user defined pile location.
void Solitaire::insertBack(Card c, string Pile){
    stringstream buffer(Pile);
    if(isalpha(Pile[0])){
        char newPile;
        buffer >> newPile;
        toupper(newPile);
        CardPileStack temp;
        temp = getCardStack(newPile);
        if(temp.getSize() == 0 && c == 1){
            temp.insert(c);
            temp.setOverturned(1);
            setCardPile(temp, newPile);
            score += 10;
        }
        else if(temp.peek()+1 == c && (temp.peek().isSameSuite(c))){//inserting at top, reach is just one, unlike moving a pile
            temp.insert(c);
            temp.setOverturned(temp.getOverturned()+1);
            setCardPile(temp, newPile);
            score += 10;
        }else{
            cout << "Cannot add card to foundation pile " << Pile;
        }
       
    }else if(isdigit(Pile[0])){
        int newPile;
        buffer >> newPile;
        CardPileStack temp;
        temp = getCardStack(newPile);
        if(c == 13 && temp.getSize() == 0){
            temp.insert(c);
            temp.setOverturned(1);
            setCardPile(temp, newPile);
        }else if(temp.peek()-1 == c && (!temp.isSameColor(c, 1))){//inserting at top, reach is just one, unlike moving a pile
            temp.insert(c);
            temp.setOverturned(temp.getOverturned()+1);
            setCardPile(temp, newPile);
        }else{
            cout << "Cannot add card to pile " << Pile;
        }
    }
}
//Desc: Method handles card moves from inbetween piles.
//Pre: Requires user input of file location and new pile location
//Post: Checks serveral condition cases then sets card(s) from initial pile to new pile. Formats columns to new display.
void Solitaire::moveToPile(int initialPile, int newPile){
    vector<Card>tempTransfer;
    CardPileStack nextPile = getCardStack(newPile);
    CardPileStack previousPile = getCardStack(initialPile);
    Card peekPrevious = previousPile.peek();
    if(nextPile.getSize() == 0){
        for(int i = 0; i < previousPile.getOverturned(); ++i){
            peekPrevious = peekPrevious + 1;
        }
        if(peekPrevious == 13){
            for(int j = 0; j < previousPile.getOverturned(); ++j){
                tempTransfer.push_back(previousPile.pop());//transfer to temp container
            }
            for(auto k = tempTransfer.size()-1; k != -1; --k){//insert to pile stack
                nextPile.insert(tempTransfer[k]);
            }
            nextPile.setOverturned(previousPile.getOverturned());
            previousPile.setOverturned(1);//not done here
            setCardPile(previousPile, initialPile);
            setCardPile(nextPile, newPile);
            return;
        }else{
            cout << "Only a King can be placed on an empty pile." << endl;
        }
    }
    int count = 0;
    for(int i = 1; i < previousPile.getOverturned()+1; ++i){
        peekPrevious = peekPrevious+1;//grabs index
        if(peekPrevious == nextPile.peek()){
            count = i;
        }
    }
    if(!previousPile.isSameColor(nextPile.peek(), count)){//if first overturned card in previous stack is 1 (of value) more, and is a different suite.
        for(int i = 0; i < count; ++i){
            tempTransfer.push_back(previousPile.pop());//transfer to temp container
            }
        for(auto i = tempTransfer.size()-1; i != -1; --i){//insert to pile stack
            nextPile.insert(tempTransfer[i]);
        }
        previousPile.setOverturned(previousPile.getOverturned() - count);//if zero, setOverturned will make 1.
        nextPile.setOverturned(nextPile.getOverturned() + count);
        setCardPile(previousPile, initialPile);
        setCardPile(nextPile, newPile);
    }else{
        cout << "Error, cannot move." << endl;
    }
}
//Desc: Method handles card movement to character pile. Deals with stack conditions following
//transfer of overturned cards.
//Pre: Requires intial pile number and new pile character to be supplied.
//Post: Checks and sets card placement in suite pile, formats initial column to new display.
void Solitaire::moveToPile(int initialPile, char newPile){
    if(getCardStack(newPile).getSize() < 13){
        CardPileStack nextPile = getCardStack(newPile);
        CardPileStack previousPile = getCardStack(initialPile);
        if(nextPile.getSize() == 0){
            if(previousPile.peek() == 1 && previousPile.peek().checkSameSuite(newPile)){//ace case
                nextPile.insert(previousPile.pop());
                score += 10;
                if(previousPile.getOverturned() > 1){
                    previousPile.setOverturned(previousPile.getOverturned() - 1);
                }else{
                      previousPile.setOverturned(1);
                }
            }
        }else{
            if(previousPile.peek().isSameSuite(nextPile.peek()) && (nextPile.peek()+1 == previousPile.peek())){
                nextPile.insert(previousPile.pop());
                score += 10;
                if(previousPile.getOverturned() > 1){
                    previousPile.setOverturned(previousPile.getOverturned() - 1);
                }else{
                    previousPile.setOverturned(1);
                }
            }
        }
        setCardPile(nextPile, newPile);
        setCardPile(previousPile, initialPile);
    }else{
        cout << "FULL PILE!" << endl;
    }
}
//Desc: Checks win status
//Pre: Game must be initialized
//Post: Returns true if all suite piles are filled, else returns false
bool Solitaire::didWin(){
    if(score == 520){
        return true;
    }else{
        return false;
    }
}
//Desc: Formats output identifier of each stack for console and file output.
//Pre: Requires pile, string identifier reference and count(iteration value) to be passed in
//Post: Sets a string identifier for each pile in iteration sequence for display
void Solitaire::formatStackOutput(string& s, int count, CardPileStack& pile){//figure out overturn procedure
    if(pile.getOverturned() > 1){
        if(pile.getSize() - pile.getOverturned() <= count && (!(count >= pile.getSize()))){
            stringstream temp;
            auto tempPile = pile.observe();
            temp << tempPile[pile.getSize()-count-1];
            s = temp.str();
        }else if(pile.getSize() - count > 1){
            s = "?";
        }else{
            s = "";
        }
    }else{
        if(pile.getSize() - count <= 0){
            s = "";//empty slot
        }
        else if(pile.getSize() - count == 1){//handles other case
            Card tempCard = pile.peek();
            stringstream temp;
            temp << tempCard;
            s = temp.str();//face up
        }else if(pile.getSize() - count > 1){
            s = "?";//face down
        }
    }
}
//Desc: Auxiliary method that calculates the largest stacks of the 7 piles.
//Pre: Requires all piles to be passed in.
//Post: Returns size of the largest pile
int Solitaire::findBiggest(CardPileStack s1, CardPileStack s2, CardPileStack s3, CardPileStack s4, CardPileStack s5, CardPileStack s6, CardPileStack s7){
    int biggest = 0;
    vector<int>sizeOfStacks = {s1.getSize(), s2.getSize(), s3.getSize(), s4.getSize(), s5.getSize(), s6.getSize(), s7.getSize()};
    for(int i = 0; i < sizeOfStacks.size(); ++i){
        if(sizeOfStacks[i] > biggest){
            biggest = sizeOfStacks[i];
        }
    }
    return biggest;
}
//Desc: Auxiliary method that fetches the card pile stack.
//Pre: Requires pile number
//Post: Returns corresponding stack
CardPileStack Solitaire::getCardStack(int number){//auxiliary
    if(number == 1){
        return firstStack;
    }else if(number == 2){
        return secondStack;
    }else if(number == 3){
        return thirdStack;
    }else if(number == 4){
        return fourthStack;
    }else if(number == 5){
        return fifthStack;
    }else if(number == 6){
        return sixthStack;
    }else if(number == 7){
        return seventhStack;
    }else{
        return firstStack;//temp idk what to do there
    }
}
//Desc: Auxiliary method that fetches suite pile
//Pre: Requires char input for suite stack
//Post: returns suite stack
CardPileStack Solitaire::getCardStack(char suite){//auxiliary
    if(suite == 'H'){
        return hearts; 
    }else if(suite == 'C'){
        return clubs;
    }else if(suite == 'D'){
        return diamonds;
    }else if(suite == 'S'){
        return spades;
    }else{
        return hearts;//idk what else to do 
    }
}
//Desc: Auxiliary method that sets card pile stack after it has been updated
//Pre: Requires changed pile and pile number to be set
//Post: Sets card pile stack with new content.
void Solitaire::setCardPile(CardPileStack pile, int number){
    if(number == 1){
        firstStack = pile;
    }else if(number == 2){
        secondStack = pile;
    }else if(number == 3){
        thirdStack = pile;
    }else if(number == 4){
        fourthStack = pile;
    }else if(number == 5){
        fifthStack = pile;
    }else if(number == 6){
        sixthStack = pile;
    }else if(number == 7){
        seventhStack = pile;
    }
}
//Desc: Auxiliary method sets suite pile with updated content.
//Pre: Requires card pile stack and suite identifier of pile
//Post: Sets suite pile with new content.
void Solitaire::setCardPile(CardPileStack pile, char suite){
    if(suite == 'H'){
        hearts = pile;
    }else if(suite == 'C'){
        clubs = pile;
    }else if(suite == 'D'){
        diamonds = pile;
    }else if(suite == 'S'){
        spades = pile;
    }
}
//Desc: Method fills discard pile with cards from the deck
//Pre: Requires deck to be filled with cards
//Post: Fills discard pile with cards from deck.
void Solitaire::dealOutFromDeck(){
    if(deck->getDeckSize() == 3 ){
        discardPile.insert(deck->getCard());
    }else if(deck->getDeckSize() == 2){
          discardPile.insert(deck->getCard());
    }else if(deck->getDeckSize() == 1){
           discardPile.insert(deck->getCard());
    }else{
        discardPile.insert(deck->getCard());//  discardPile.insert(deck->getCard());// discardPile.insert(deck->getCard());
    }//used one card discard for testing
}
//Desc: Method handles discard pile functionality. Prompts user for discard options (set at pile, discard)
//Pre: Requires discard pile to be filled
//Post: Performs pile updates with cards from discard pile if card placement is valid.
void Solitaire::moveFromDiscard(){
    if(discardPile.getSize() == 0){
        dealOutFromDeck();
    }
    auto card = discardPile.peek();
    string choice;
    cout << "Enter pile to move (enter 'discard' to discard, 'exit' to exit) " << card << endl;
    cin >> choice;
    try{
        if(choice == "discard"){
            int tempSize = discardPile.getSize();
            for(int i = 0; i < tempSize; ++i){
                deck->insertCard(discardPile.pop());
            }
            discardPile.makeEmpty();//in case
            dealOutFromDeck();
            moveFromDiscard();//have to start again in first doesnt work
        }else{
            for(int i = 0; i < choices().size(); ++i){
                if(choice == choices()[i]){
                    insertBack(discardPile.peek(), choice);
                    discardPile.pop();//only executed if insertBack doesnt throw anything
                }
            }
        }
    }catch(string msg){
        cout << msg << endl;
        cout << "try again. Options: (D,H,C,S), (1,2,3,4,5,6,7)" << endl;
    }
}

//Desc: Helper method, supplies option symbols in a vector container
//Pre: n/a
//Post: returns vector of symbols.
vector<string>Solitaire::choices(){
    return {"H","C","D","S","1","2","3","4","5","6","7"};
}
int Solitaire::getScore(){
    return score;
}
