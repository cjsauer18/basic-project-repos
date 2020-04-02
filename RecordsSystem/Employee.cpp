#include <iostream>
#include <string>
#include "Employee.h"
#include <sstream>
#include <cstdlib>
#include "Exception.cpp"
using namespace std;

Employee::Employee(){}//default constructor
//Description: First name setter
//Pre: Employee object must exist, 'first' must be assigned.
//Post: first name is set
void Employee::setFirstName(string first){
    firstName_ = first;
}
//Description: last name setter
//Pre: Employee object must exist, 'last' must be assigned.
//Post: last name is set
void Employee::setLastName(string last){
    lastName_ = last;
}
//Description: social security setter
//Pre: Employee object must exist, 'ssn' must be assigned
//Post: social security number is stored in legal formatting
void Employee::setSSN(string& ssn){
    if(ssn.length() == 9){//basic checking
        stringstream iss;
        iss << "XXX-XX-" << ssn.substr(5);//correct legal storing
        socialSec_ = iss.str();
    }else{
        InputException e(ssn, "Social Security", "'XXX-XX-XXXX'");//throw exception if input is invalid
        throw(e);
    }
}
//Description: Employee number setter
//Pre: Employee object must exist, 'num' must be assigned
//Post: Employee number is stored, edited in correct format.
void Employee::setEmployeeNumber(string& num){
    if(num.length() == 4 && isalpha(num[3])){//basic checking
        //L is num[3];
        if('A' <= num[3] && num[3] <= 'M'){//if letter(L) is in range
            stringstream temp;
            temp << num.substr(0,3) << "-" << num.substr(3);
            employeeNumber_ = temp.str();
        }else{
            InputException e(num, "Employee Number", "A is (uppercase) and from A-M: '###A'");//throw exception is input is invalid
            throw(e);
        }
    }else{
        InputException e(num, "Employee Number", "A is (uppercase) and from A-M: '###A'");
        throw(e);
    }
}
//Description: Tax rate setter
//Pre: Employee object must exist, 'rate' must be assigned.
//Post: Tax rate is converted to code (1 to 3).
void Employee::setTaxRate(int& rate){
    if(rate == 25){
        taxRate_ = 1;
    }else if(rate == 20){
        taxRate_ = 2;
    }else if(rate == 15){
        taxRate_ = 3;
    }else{
         rate = 0;//keeping rate type safe
         InputException e(rate, "Tax Rate", "Format for tax code rate mut be either '25', '20', or '15' (%)");//exception thrown if input is invalid
         throw(e);
    }
}
//Description: name getter for class Employee
//Pre: Employee object must exist, first and last name variables must be set.
//Post: returns first and last name formatted together.
string Employee::getName(){
    stringstream name;
    name << firstName_ << " " << lastName_;
    return name.str();
}
//Description: Social security getter
//Pre: Employee object must exist, ssn must be set.
//Post: socialSec_ is returned in legal format.
string Employee::getSocialSec(){
    return socialSec_;
}
//Description: Tax rate getter.
//Pre: Employee object must exist, Tax must be set.
//Post: returns double of rate percentage.
double Employee::getTax(){
    if(taxRate_ == 1){
        return 0.25;
    }else if (taxRate_ == 2){
        return 0.20;
    }else if (taxRate_ == 3){
        return 0.15;
    }else{
        cout <<"error" << endl;
        return NULL;
    }
}
//Description: Employee number getter.
//Pre: Employee object must exist, employee number must be set.
//Post: returns formatted employee number.
string Employee::getEmployeeNumber(){
    return employeeNumber_;
}
//Description: Utility function, helps makeNoise output 'random' strings from list of given strings.
//Pre: Employee object must exist, makeNoise must be called.
//Post: Mixes order of three strings by inconsistent reassigning. (mixing).
void Employee::randomize(string& one, string two, string three){
    srand(time(NULL));
    int num = rand() % 3;//random num out of 10
    if(num == 1){
        one = two;
    }
    else if(num == 2){
        one = three;
    }else{
        return;
    }
}
//Description: method outputs a string when prompted.
//Pre: Employee object must exist, printEmployeeRecord must be called.
//Post: Outputs a string to console.
void Employee::makeNoise(){
    string one = "I believe you have my stapler.";
    string two = "Excuse me, but I think you have my stapler.";
    string three = "I could set the building on fire.";
    randomize(one, two, three);
    cout << one << endl;
    
}
//Description: abstract function instantiations.
//Pre: Employee object must exist.
//Post: Subclass implementation
void Employee::calculatePay(){}
void Employee::printEmployeeRecord(){}


