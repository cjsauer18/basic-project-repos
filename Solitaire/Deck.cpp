#include "Deck.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>

using namespace std;


//Desc: Constructor fills the deck with a complete set of cards
//Pre: N/A
//Post: Returns full deck of cards
Deck::Deck(){
    srand(time_t(NULL));
    for(int suite = 0; suite != 4; ++suite){//suite corresponding number
        for(int i = 1; i < 14; ++i){//card value
            if(suite == 0){
                deck.enqueue(Card(i, 'H'));
            }else if(suite == 1){
                deck.enqueue(Card(i, 'D'));
            }else if(suite == 2){
                deck.enqueue(Card(i, 'C'));

            }else if(suite == 3){
        
                deck.enqueue(Card(i, 'S'));
            }
        }
    }
}
//Desc: Checks capacity status
//Pre: Requires deck queue to be initialized
//Post: returns boolean of status
bool Deck::isFull(){
    if (deck.isFull()){
        return true;
    }else{
        return false;
    }
}
//Desc: Checks capacity status
//Pre: Requires deck queue to be initialized
//Post: returns boolean of status
bool Deck::isEmpty(){
    if(deck.isEmpty())
        return true;
    else
        return false;
}
//Desc: Getter method that dequeues and returns a card from the deck
//Pre: Requires deck to be populated
//Post: Returns card from queue
Card Deck::getCard(){
    try{
        return deck.dequeue();
    }catch(const char* msg){
        cout << msg << endl;
        return NULL;
    }
}
//Desc: Setter method that enqueues card to deck
//Pre: Deck must be initialized, cannot be full.
//Post: Enqueues card to deck
void Deck::insertCard(Card card){//method is only viable outside the constructor intialization
    if(!deck.isFull()){
        deck.enqueue(card);
    }else{
        cout << "Deck is full, cannot add to pile" << endl;
    }
}
//Desc: getter, returns size of queue
//Pre: Deck must be initialized
//Post: returns size
int Deck::getDeckSize(){
    return deck.getSize();
}
//Desc: utility method clears deck of contents
//Pre: deck (should) be initialized
//Post: returns empty queue
void Deck::clearDeck(){
    deck.makeEmpty();
    cout << "Deck cleared!" << endl;
}
//Desc: Initialzer method that fills deck with full set of cards
//Pre: Requires deck to be empty
//Post: Returns full deck of cards
void Deck::initializeDeck(){
    for(int suite = 0; suite != 4; ++suite){//suite corresponding number
        for(int i = 1; i < 14; ++i){//card value
            if(suite == 0){
                deck.enqueue(Card(i, 'H'));
            }else if(suite == 1){
                deck.enqueue(Card(i, 'D'));
            }else if(suite == 2){
                deck.enqueue(Card(i, 'C'));
            }else if(suite == 3){
                deck.enqueue(Card(i, 'S'));
            }
        }
    }
}
//Desc: Method prints contents of deck to console
//Pre: Deck should not be empty
//Post: Outputs deck contents to console
void Deck::printDeck(){
    cout << deck << endl;//calls overrided stack ostream operator 
}
//Desc: Inserton sorting algorithm that sorts cards in increasing order.
//Pre: Deck should not be empty.
//Post: Returns sorted deck of increasing value
void Deck::sortIncreasing(){
    vector<Card>cardVector = this->cardVector();
    int j=1; Card tempIndex;
    for(int i = 1; i < cardVector.size(); ++i){
        j=i;
        while(j>0 && cardVector[j-1] > cardVector[j]){//insertion sort
            tempIndex = cardVector[j];
            cardVector[j] = cardVector[j-1];//swap
            cardVector[j-1] = tempIndex;
            j--;
        }
    }
    for(int i = 0; i < cardVector.size(); ++i){
        deck.enqueue(cardVector[i]);
    }
}
//Desc: method returns first card in queue
//Pre: Deck must not be empty
//Post: Returns first card.
Card Deck::front(){
    return deck.front();
}
//Desc: Inserton sorting algorithm that sorts cards in decreasing order.
//Pre: Deck should not be empty.
//Post: Returns sorted deck of deceasing value
void Deck::sortDecreasing(){
    vector<Card>cardVector = this->cardVector();
    int j = 1; Card tempIndex;
    for(int i = 1; i < cardVector.size(); ++i){
        j=i;
        while(j > 0 && cardVector[j-1] < cardVector[j]){//insertion sort
            tempIndex = cardVector[j];
            cardVector[j] = cardVector[j-1];//swap
            cardVector[j-1] = tempIndex;
            j--;
        }
    }
     for(int i = 0; i < cardVector.size(); ++i){
           deck.enqueue(cardVector[i]);
    }
}

//Desc: Shuffles deck of cards
//Pre: Requires deck to be populated
//Post: Returns deck with randomized card positions
void Deck::Shuffle(){//find sort function
    vector<Card>cardVector = this->cardVector();
    srand(time_t(NULL));//seed randomize
    Card temp;
    for(int i = 0; i < cardVector.size(); ++i){
        temp = cardVector[i];
        int tempIndex = rand()%cardVector.size()-1;
        cardVector[i] = cardVector[tempIndex];//swap with random index
        cardVector[tempIndex] = temp;//reassign random index.
    }
    for(int i = 0; i < cardVector.size(); ++i){
           deck.enqueue(cardVector[i]);
       }
}
//Desc: Auxiliary method that converts queue to vector container for insertion sort
//Pre: Deck should be populated with cards
//Post: Returns vector of cards dequeued from deck queue
vector<Card>Deck::cardVector(){//sorting utility function
    vector<Card>temp;
    int size = deck.getSize();
    for(int i = 0; i < size; ++i){
        temp.push_back(deck.dequeue());//empties list while at it
    }
    return temp;
}
