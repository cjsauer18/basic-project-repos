#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <numeric>
#include <map>
#include <cmath>
using std::cin; using std::cout; using std::vector; using std::string;
using std::ostream; using std::endl; using std::map; using std::istringstream;
using map_type = map<string, long>;

//This project consists of several algorithms that provide statistical analysis of
//word sets of which are extracted by documents. A function opens a document, and parses
//the words, and their respective frequency inside the document to a map. Other functions
//use the maps created from data within the files to calculate Jaccard Similiarity, Cosine Similarity,
//and Norm factor.

//Utility function cleans words, checks if alphabetical. Converts to lowercase, returns new string.
string clean_word(const string s){
    string new_string;
  for(auto ch: s){
      if(isalpha(ch)){
            ch = tolower(ch);
            new_string += ch;
        }
    }
    return new_string;
}
//This function opens filename passed by parameter, and parses the words and counts their frequency.
//The map passed by reference adds the word as a key and value as the amount of times the word appears in the document.
void process_words(map_type& m1, string s)
{
    string filename;
    filename = s + ".txt";
    std::ifstream input;
    string line, word, new_string;
    input.open(filename);
    if(input.is_open()){
    
        while(getline(input, line)){//takes lines in file(loops over each line) Doesnt terminate until last \n (newline character)
            istringstream iss(line);
            while(iss >> word){//parses words from line
                //because our data are a bunch of sentences, the structure doesnt involve comma separated data. we can parse without using delimiters, etc. getline with(x,x, delimiter) does this.
                new_string = clean_word(word);
                m1[new_string] += 1;//assigns each string a value (starts at 1) and increments existing occurance of word each time
                //the same word is parsed. Key values will not be duplicated
            }
        }
    }
}

//Utility, prints map to ostream
ostream& print_map(ostream& out, const map_type& m){
    for(auto itr: m){
        out << "<" << itr.first << ", " << itr.second << ">" << endl;
    }
    return out;
}
//This function uses the jaccard similarity equation, and takes in two maps.
//The function extracts the integer values from each map to separate vectors
//and iterates through them, finding equivalency, to then use in jaccard equation.
double jaccard_similarity(map_type&m1, map_type&m2){
    int A, B;
    double AandB = 0; //common in both
    vector<string> first;
    vector<string> second;
    for (auto pair: m1){
        first.push_back(pair.first);//int in map 1
    }
    for (auto pair: m2){
        second.push_back(pair.first);//int in map 2
    }
    A = static_cast<int>(first.size());//number of words in m1
    B = static_cast<int>(second.size());//number of words in m2
    for(auto x: first){
        for(auto i: second){
            if(x==i){
                AandB += 1;//equivalence similarity found
            }
        }
    }
    double J = (AandB)/(A+B-AandB);//jaccard similarity
    return J;
}
//This function calculates the norm factor of a map passed in by parameter.
//Takes integers from map and takes the square root of the word frequency (ints) squared.
double calc_norm_factor(map_type&m1){
    vector<double> first;
    for (auto pair: m1){
        first.push_back(pair.second);//push back frequency of words
    }
    for (auto& x: first){
        x = x*x;//square each value
    }
    int sum = std::accumulate(first.begin(), first.end(),0);
    double NF = sqrt(sum);//divide by sum
    return NF;//returns norm factor
}
//This function finds the sumation of a vector passed by reference. Divides by squareroot of the sum.
void vector_sum(vector<double>& v){
    int sum = std::accumulate(v.begin(), v.end(),0);
    double NF = sqrt(sum);
    for(auto& x: v){//for each value in vector
        x = x/NF;//vector val is divided by square root
    }
}
//This function finds the cosine similarity using the similarity formula. Two maps are passed in by reference
//Longs are taken into vectors and then looped through to find similarity.
double cosine_similarity_tf(map_type&m1, map_type&m2){
    double AB = 0;
    vector<double> first;
    vector<double> second;
        for (auto pair: m1){
            first.push_back(pair.second);//long from first vector
        }
        for (auto pair: m2){
            second.push_back(pair.second);//long from second vector
    }
    vector_sum(first);
    vector_sum(second);
    for(auto x: first){
        double y;
        y = second[x];//instead of double loop
        cout << AB << " + " << x << "*" << y << endl;//dispaying purposes (displaying arithmetic)
        cout << endl;//display purposes
        AB = AB + (x*y);//cosine similarity
    }
    return AB;
}
int main() {
    cout << std::boolalpha << endl;
    map<string, long> m1; map<string, long>m2;
    
    //open document containing test words
    process_words(m2, "words_2");//document that will populate map 2
    process_words(m1, "words");//document that will populate map 1
    //print out map of words and occurences from file.
    
    cout << "Map 1: "<< endl;
    print_map(cout, m1);//print map 1 to console
    cout << endl << "---------------------------" << endl << endl;
    cout << "Map 2: "<< endl;
    print_map(cout, m2);//print map 2 to console
    
    cout << endl << "---------------------------" << endl << "Cosine similiarity arithmetic:" << endl;
    auto cosine_sim = cosine_similarity_tf(m1, m2);//cosine similarity
    auto jaccard_sim = jaccard_similarity(m1, m2);//jaccard similarity
    
    cout << endl << endl;
    
    //print to console
    cout << "Cosine Similarity: " << cosine_sim << endl;
    cout << "Jaccard Similarity: " << jaccard_sim << endl << endl;
}

