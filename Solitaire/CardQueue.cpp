#include "CardQueue.h"
#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

//Desc: intializes queue to size of 0
Queue::Queue(){
    size = 0;
}
//Desc: checks capacity status
//Pre: queue must be initialized
//Post: returns boolean of status
bool Queue::isEmpty(){
    if(size == 0){
        return true;
    }else{
        return false;
    }
}
//Desc: checks capacity status
//Pre: queue must be initalized
//Post: returns boolean of status
bool Queue::isFull(){
    if(size==capacity){
        return true;
    }else{
        return false;
    }
}
//Desc: Returns first element of queue
//Pre: queue must be initalized and popualted
//Post: returns first element
Card Queue::front(){
    if(!isEmpty()){
        return top->card;
    }else{
        return NULL;
    }
}
//Desc: Enqueue method that adds card element supplied by parameter
//Pre: requires queue to not be full and initialized
//Post: Adds element to queue
void Queue::enqueue(Card card){
    if(isEmpty()){
        Node* temp = new Node;
        temp->card = card;
        top = rear = temp;
        size++;
        return;
    }if(!isFull()){
        Node* temp = new Node;
        temp->card = card;
        rear->next = temp;
        rear = temp;
        size++;
    }else{
        cout << "Stack is full" << endl;
    }
}
//Desc: Dequeue method that returns card element from queue, removes form queue.
//Pre: Requires queue to be initialied and not empty.
//Post: returns card from queue
Card Queue::dequeue(){
    Card newCard;
    if(!isEmpty()){
        Node* temp = top;
        newCard = top->card;
        top = top->next;
        size--;
        if(size == 0){
            top = rear = nullptr;
        }

        delete temp;
        return newCard;
    }else{
        throw("stack is empty, cannot pop");
    }

    return newCard;
}
//Desc: Getter, returns capcaity
//Pre: Queue must be iniitlaized
//Post: Returns size
int Queue::getSize(){
    return size;
}
//Desc: utility method, clears queue
//Pre: queue should be initialized and filled prior to call
//Post: clears queue of elements, size set to 0.
void Queue::makeEmpty(){
    size = 0;
    Node* current = top;
    while(top != nullptr){
        current = top;
        top = top->next;
        delete current;
    }
}
//Desc: Utility ostream operator, formats elements in queue to output to ostream.
//Pre: Queue must be called in the ostream.
//Post: Returns formatted output of elements in queue
ostream& operator <<(ostream& out, Queue& queue){
    out << "Current Deck: " << endl;
    Queue::Node* current = queue.top;
    int count = 1;
    while(current != queue.rear->next){//is rear equivalent to nullptr but its next pointer is alsp nullptr?
        if(count == 13){//formatter
            out << current->card << " ";
            out << endl;
            count = 1;
        }else{
            out << current->card << " ";
            count++;
        }
        current = current->next;
    }
   
    return out;
}
