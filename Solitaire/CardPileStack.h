#pragma once
#include "Card.h"



class CardPileStack{
    struct Node{
        Card card;
        Node* next;
    };
private:
    Node* top = nullptr;
    int size;
    int capacity = 52;
    int overTurned;
public:
    int getOverturned();
    CardPileStack();
    int getSize();
    bool isEmpty();
    bool isFull();
    void insert(Card card);
    Card pop();
    void makeEmpty();
    Card peek();
    friend ostream& operator<<(ostream&, CardPileStack&);
    void setOverturned(int num);
    vector<Card>observe();
    void testPrint();
    bool isSameColor(Card c, int reach);
    bool isSameSuite(Card c, int reach);
    bool isSameSuite(Card c);
};
