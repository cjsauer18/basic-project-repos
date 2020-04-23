#pragma once
#include "Card.h"



class Queue{
    struct Node{
        Card card;
        Node* next;
    };
private:
    Node* top = nullptr;
    Node* rear = nullptr;
    int size;
    int capacity = 52;
public:
    Queue();
    int getSize();
    bool isEmpty();
    Card front();
    bool isFull();
    void enqueue(Card card);
    Card dequeue();
    void makeEmpty();
    friend ostream& operator<<(ostream&, Queue&);
};

