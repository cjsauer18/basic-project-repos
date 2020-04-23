#include "CardPileStack.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
//Desc: sets initial values of pile stack
CardPileStack::CardPileStack(){
    overTurned = 1;
    size = 0;
}
//Desc: Checks capaity status
//Pre: Stack should be initialzied
//Post: Returns boolean value of status
bool CardPileStack::isEmpty(){
    if(size == 0){
        return true;
    }else{
        return false;
    }
}
//Desc: Checks capacity status
//Pre: Stack should be initialized
//Post: Returns boolean value of status
bool CardPileStack::isFull(){
    if(size==capacity){
        return true;
    }else{
        return false;
    }
}
//Desc: Method inserts card into stack
//Pre: Stack should be initialzed
//Post: Adds card element to stack
void CardPileStack::insert(Card card){
    if(isEmpty()){
        Node* temp = new Node;
        temp->card = card;
        temp->next = nullptr;
        top = temp;
        size++;
          
        return;
    }if(!isFull()){
        Node* temp = new Node;
        temp->card = card;
        temp->next = top;
        top = temp;
        size++;
        
    }else{
        cout << "Stack is full" << endl;
    }
}
//Desc: Stack pop method that returns and removes element from stack.
//Pre: Requires stack to be initlaized and not empty
//Post: Returns and removes card element from stack.
Card CardPileStack::pop(){
    Card newCard;
    if(!isEmpty()){
        Node* temp = top;
        newCard = top->card;
        top = top->next;
        size--;
        delete temp;
        return newCard;
    }else{
        throw("stack is empty, cannot pop");
    }
    return newCard;
}
//Desc: Peek method returns card from stack, does not remove.
//Pre: Requires stack to be initlaized and not empty.
//Post: Returns and removes card element from stack.
Card CardPileStack::peek(){
    if(!isEmpty()){
        return top->card;
    }else{
         return Card(0);//none value
    }

}
//Desc: Methed returns capacity
//Pre: Stack must be initialized
//Post: returns capacity count
int CardPileStack::getSize(){
    return size;
}
//Desc: Method makes card stack empty
//Pre: stack should be filled and initialzed
//Post: sets size to 0, clears content of stack.
void CardPileStack::makeEmpty(){
    size = 0;
    Node* current = top;
    while(top != nullptr){
        current = top;
        top = top->next;
        delete current;
    }
}
//Desc: Setter method sets overturned value of stack.
//Pre: Requires overturned value to be supplied by method that alters stack contents
//Post: Adjusts overturned status of pile stack.
void CardPileStack::setOverturned(int num){
    if(num == 0){
        overTurned = 1;
    }else if(num < 0){
        overTurned = 1;
    }
    else{
     overTurned = num;
    }
}
//Desc: Auxiliary method converts stack to vector container.
//Pre: Requires stack to be populated.
//Post: Returns vector of overturned elements in stack.
vector<Card>CardPileStack::observe(){
    vector<Card>peek;
    Node* current = top;
    int count = overTurned;
    while(count != 0){
        peek.push_back(current->card);
        current=current->next;
        count--;
    }
    return peek;
}

void CardPileStack::testPrint(){
    Node* current = top;
    while(current != nullptr){
        cout << current->card << endl;
        current = current->next;
    }
}
//Desc: Method compares card element passed in to element in stack at certain index.
//Pre: Stack must be initialzed, card must be passed in, reach (index) must be supplied
//Post: Returns boolean value of card comparison.
bool CardPileStack::isSameColor(Card c, int reach){
    Node* current = top;
    while(reach > 1){
        current = current->next;
        reach--;
    }
    return current->card.isSameColor(c);
     
}
int CardPileStack::getOverturned(){
    return overTurned;
}
