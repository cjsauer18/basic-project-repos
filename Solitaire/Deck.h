#pragma once
#include <iostream>
#include "CardQueue.h"
#include "Card.h"
#include <vector>
using namespace std;

class Deck{
private:
    int size;
    Queue deck;
public:
    Deck();
    bool isFull();
    bool isEmpty();
    int getDeckSize();
    Card front();
    Card getCard();
    void insertCard(Card card);
    void Shuffle();
    void clearDeck();
    void initializeDeck();//subsitutde to constructor
    void printDeck();
    void sortIncreasing();
    void sortDecreasing();
    vector<Card>cardVector();
};
