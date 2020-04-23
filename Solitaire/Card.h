#pragma once

#include <iostream>
#include <ostream>
using namespace std;


class Card{
private:
    int color;
       int number;
       char suite;
       string identifier;
public:
    Card();
    Card(int num); //dummy constructor
    Card(int num, char suite);
    bool operator==(Card c);
    bool operator==(int);
    bool operator>(Card c);
    bool operator<(Card c);
    Card operator-(int);
    Card operator+(int);
    bool isSameColor(Card c);
    bool isSameSuite(Card c);
    bool checkSameSuite(char);
    friend ostream& operator<< (ostream&, Card&);
};
