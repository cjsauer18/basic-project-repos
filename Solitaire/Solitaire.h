#pragma once
#include <iostream>
#include "Deck.h"
#include "Card.h"
#include "CardPileStack.h"
#include <string>
#include <fstream>
class Solitaire{
private:
    string name;
    int score = 0;
    Deck* deck;
    ofstream output;
    CardPileStack firstStack;
    CardPileStack secondStack;
    CardPileStack thirdStack;
    CardPileStack fourthStack;
    CardPileStack fifthStack;
    CardPileStack sixthStack;
    CardPileStack seventhStack;
    CardPileStack diamonds;
    CardPileStack spades;
    CardPileStack hearts;
    CardPileStack clubs;
    CardPileStack discardPile;
public:
    Solitaire();
    void printDisplay();
    int getScore();
    void initializeGame(Deck&);
    void dealOutFromDeck();
    void moveFromDiscard();
    void insertBack(Card c, int);
    void insertBack(Card c, string);
    void moveToPile(int initialPile, int newPile);
    void moveToPile(int initialPile, char newPile);
    bool didWin();
    void formatStackOutput(string&, int, CardPileStack&);
    int findBiggest(CardPileStack s1, CardPileStack s2, CardPileStack s3, CardPileStack s4, CardPileStack s5, CardPileStack s6, CardPileStack s7);
    CardPileStack getCardStack(int number);
    CardPileStack getCardStack(char suite);
    void setCardPile(CardPileStack, int);
    void setCardPile(CardPileStack, char);
    vector<string>choices();
};
