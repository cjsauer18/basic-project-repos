#include <iostream>
#include <string>
#include "QuadraticProbing.h"
#include "SpellChecker.h"
#include <stdlib.h>
using namespace std;
/*
Chris Sauer
11 June, 2020
CIS 350 - Project 2
Given a hashtable class that uses Quadratic Probing to resolve collisions, design a spellchecking program that takes in a dictionary and a text file and checks if each word in the text file is spelled correctly by checking if the word is contained in the dictionary. The program also will try to find corrections to the word and display each inccorrect word with possible corrections in a separate file, along with a statistical report of the dictionary hash table behavior.
*/

//Desc: main takes 3 command line arguments and inserts them into sspellcheck functions.
//Pre: Requires properly formatted arguments in correct order.
//Post: Outputs a file of misspelled words with possible corrections, along with a statistical analysis of hash table behavior.
int main(int argc, char* argv[])
{
    SpellChecker spellcheck;
    spellcheck.fillHashTable(atoi(argv[1]), string(argv[2]));
    spellcheck.readFile(string(argv[3]));
    spellcheck.writeCorrections();
    spellcheck.writeCerr();
}
