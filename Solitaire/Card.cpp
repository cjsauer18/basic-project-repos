#include "Card.h"
#include <iostream>



using namespace std;

//may need suite comparator

Card::Card(){}
//Desc: Constructor that sets card value and suite
//Pre: N/A
//Post: Creates card, assigning facecard identifier if number > 10
Card::Card(int num, char suite){
    this->number = num;
    this->suite = suite;
    if(this->suite == 'D' || this->suite == 'H'){
        color = 1;
    }else{
        color = 0;
    }
    if(number == 1){
        identifier = 'A';
    }else if(number == 11){
        identifier = 'J';
    }else if(number == 12){
        identifier = 'Q';
    }else if(number == 13){
        identifier = 'K';
    }
}
//Desc: Secondary constructor for null card. Placeholder card.
//Post: sets value to 0 (null card)
Card::Card(int num){
    this->number = 0;
    this->identifier = '0';
    this->suite = NULL;
}
//Desc: boolean equality operator
//Pre: cards must be compared
//Post: returns boolean status of card compared to another card
bool Card::operator==(Card c){//still having number values offsets need for char comparator
    if(this->number == c.number){
        return true;
    }else{
        return false;
    }
}
//Desc: Boolean equality operator
//Pre: Card must be compared to an integer
//Post: Returns boolean status of card compared an integer
bool Card::operator==(int num){//still having number values offsets need for char comparator
    if(this->number == num){
        return true;
    }else{
        return false;
    }
}
//Desc: Boolean greater than operator
//Pre: Card must be compared to another
//Post: Returns boolean status after comparing card values
bool Card::operator>(Card c){
    if(this->number > c.number){
        return true;
    }else{
        return false;
    }
}
//Desc: Boolean less than operator
//Pre: Card must be compared to another
//Post: Returns boolean status after comparing card values
bool Card::operator<(Card c){
    if(this->number < c.number){
        return true;
    }else{
        return false;
    }
}
//Desc: Method checks if the card suite is the same as another card
//Pre: Requires card to be supplied
//Post: Returns boolean status of card suite comparison.
bool Card::isSameSuite(Card c){
    if(this->suite == c.suite){
        return true;
    }else{
        return false;
    }
}
//Desc: Checks if card is the same suite to a given character.
//Pre: Requires card to be compared to a character value.
//Post: Returns boolean status of card suite comparison.
bool Card::checkSameSuite(char suite){
    if(this->suite == suite){
        return true;
    }else{
        return false;
    }
}
//Desc: Ostream operator formats output of card to console.
//Pre: Object of type card must be called in the ostream.
//Post: Returns formatted output of Card object.
ostream& operator<<(ostream&out, Card& c){
    if(c.number > 10 || c.number == 1 || c.number == 0){//if a jack or above
        out << "|" << c.identifier << c.suite << "|";
    }else{
        out << "|" << c.number << c.suite << "|";
    }
    return out;
}
//Desc: Card subtraction operator
//Pre: Requires card to be subtracted by an integer type
//Post: Returns card of value subtracted by integer
Card Card::operator-(int num){
    if(number != 1){
        number = number - num;
    }else{
        cout << "Error, Ace cannot be decremented" << endl;
    }
    return *this;
}
//Desc: Card addition operator
//Pre: Requires card to be added by an integer type
//Post: Returns card value added by integer.
Card Card::operator+(int num){
    if(number != 13){
        number = number + num;
    }else{
        cout << "Error, King cannot be incremented." << endl;
    }
    return *this;
}
//Desc: Checks if the color of the card is the same as another
//Pre: Requires comparison card to be supplied
//Post: Returns boolean status of card having the same suite color.
bool Card::isSameColor(Card c){
    if(this->color != c.color){
        return false;
    }else{
        return true;
    }
}
