#include <iostream>
#include <exception>
#include <string>
#include <sstream>
using namespace std;

//Exeception class
//Instantiated with the description, location and variable that is invalid.

class InputException : public exception{
public:
    //error descriptive attributes
    string where_;
    string* input_ = nullptr;
    int* inputNum_ = nullptr;
    double* inputDouble_ = nullptr;
    string format_;
    InputException(string& input, string where, string format){//for string errors
        input_ = &input;
        where_ = where;
        format_ = format;
    }
    InputException(int& input, string where, string format){//for integer errors
        inputNum_ = &input;
        where_ = where;
        format_ = format;
        }
    InputException(double& input, string where, string format){//for double errors
        inputDouble_ = &input;
        where_ = where;
        format_ = format;
    }
    const string what () {//exception description
        stringstream temp;
        temp << "Error in input of " << where_ << '\n' << "Proper format: " << format_;
        auto temp2 = temp.str();
        return temp2;
    }
};
