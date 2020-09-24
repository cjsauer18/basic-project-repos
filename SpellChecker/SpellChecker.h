#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "QuadraticProbing.h"
using namespace std;

class SpellChecker{
    
    struct Word{//for word formatting sake
        string word;
        int lineNumber;
        Word(string w, int lineNum){
            word = w;
            lineNumber = lineNum;
        }
    };
private:
    HashTable<string> dictionary;
    ifstream input;
    ofstream output;
    vector<pair<Word, vector<string>>>incorrectWords;

public:
    SpellChecker();
    vector<string> spellCheck(string word);//permutate strings
    void readFile(string inputFilename);//will call spellcheck
    void writeCerr();
    void writeCorrections();
    void fillHashTable(int numWords, string dictionaryFilename);
    friend ostream& operator<<(ostream&out, Word&w){//friendly word formatter
        out << w.word << "(" << w.lineNumber << ")";
        return out;
    }
};
