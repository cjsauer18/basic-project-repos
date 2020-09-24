#include <iostream>
#include <stdio.h>
#include "SpellChecker.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
//default constructor
SpellChecker::SpellChecker(){}

//Desc: This method accesses the incorrectWords collection and places them in a file.
//Pre: Requires readFile to be called previously to find words and correct any that are flagged as misspelled
//Post: Reports a formatted output of misspelled words and possible corrections to a file.
void SpellChecker::writeCorrections(){
    for(int i = 0; i < incorrectWords.size(); ++i){
        cout << incorrectWords[i].first << ": ";//
        if(incorrectWords[i].second.size() > 0){
            for(int j = 0; j < incorrectWords[i].second.size(); ++j){
                cout << incorrectWords[i].second[j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}
//Desc: This method takes in a filename and parses the words in the file. Strips lines in the document of any punctuation. Then each word is processed and checked if it is present in the hashtable. If not, the word is permutated in a separate function call and passed to a incorrect word collection.
//Pre: Requires filename to be inputted. Hashtable should be filled with elements to compare words to.
//Post: Fills incorrectWords collection with possible corrections (if any) of a misspelled word.
void SpellChecker::readFile(string inputFilename){
    int count = 0;
    string line;
    input.open(inputFilename);
    stringstream buffer;
    string tempWord;
    while(getline(input,line)){
        for(int i=0; i <line.length(); i++)//basic punctuation clean
        {
            if (!isalpha(line[i]))
                line[i] = ' ';
        }
        count++;
        stringstream buffer(line);
        while(buffer >> tempWord){
            if(!dictionary.contains(tempWord)){//check if present
                string tempWordLowerCase = tempWord;
                for(int i = 0; i < tempWord.length(); ++i){//convert to lowercase
                    tempWordLowerCase[i] = tolower(tempWordLowerCase[i]);
                }
                if(!dictionary.contains(tempWordLowerCase)){//check if present again
                    incorrectWords.push_back(make_pair(Word(tempWord,count), spellCheck(tempWord)));
                }
            }
        }
    }
    input.close();
}

//Desc: Auxiliary function that permutates the word in each of the four styles for standardized spell checking.
//Pre: Readfile must be called, and a word must be supplied.
//Post: returns a vector of strings of possible permutations (corrected guesses) that may be the right spelling.
vector<string> SpellChecker::spellCheck(string word){
    vector<string> permutations;
    //erase letter from each position
    for(int i = 0; i < word.length(); ++i){
        string temp = word.substr(0, i) + word.substr(i+1);
        if(dictionary.contains(temp)){
            permutations.push_back(temp);
        }
    }
    //swap adjacent letters
    for(int i = 1; i < word.length(); ++i){
        string temp = word;
        swap(temp[i-1], temp[i]);
        if(dictionary.contains(temp)){
            permutations.push_back(temp);
        }
    }
    //insert random letter in each position
    for(int i = 0; i < word.length()+1; ++i){
        for(char j = 'a'; j != 'z'; ++j){
            string temp = word;
            temp = word.substr(0, i) + j + word.substr(i);
            if(dictionary.contains(temp)){
                permutations.push_back(temp);
            }
        }
    }
    //replace random letter in each position
    for(int i = 0; i < word.length(); ++i){
        for(char j = 'a'; j != 'z'; ++j){
            string temp = word;
            temp[i] = j;
            if(dictionary.contains(temp)){
                permutations.push_back(temp);
            }
        }
    }
    return permutations;
}

//Desc: This method takes in a word count and a dictionary filename and inserts each word into the hash table.
//Pre: Word count and dictionary filename must be supplied on the command line
//Post: Hash table is filled with elements
void SpellChecker::fillHashTable(int numWords, string dictionaryFilename){
    dictionary = HashTable<string>(numWords * 2);
    string line;
    input.open(dictionaryFilename);
    while(input >> line){
        dictionary.insert(line);
    }
    input.close();
}
//Desc: Print method calls statistic methods from the Hash table class and formats them to an output file.
//Pre: Requires hash table to be filled with elements for a report.
//Post: Outputs statistical analysis to a file.
void SpellChecker::writeCerr(){
    cerr << "Number of words: " << dictionary.getNumberOfObjectsInTable() << ", Table Size: " << dictionary.getArraySize() << ", Load Factor: " << setprecision(6) << dictionary.getLoadFactor() << endl;
    cerr << "Collisions: " << dictionary.getTotalCollisions() << ", Average Chain Length: " << setprecision(6) << dictionary.getCollisionLengthAverage() << ", Longest Chain Length: " << dictionary.getLongestCollision() << endl;
}
