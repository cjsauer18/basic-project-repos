#include <iostream>
#include <string>
#include "Employee.h"
#include <sstream>
#include <cstdlib>
#include "Exception.cpp"
using namespace std;

#include "SalaryEmployee.h"

SalaryEmployee::SalaryEmployee(){}//default constructor

//Description: setter for annual pay.
//Pre: Object of 'SalaryEmployee' must exist. 'pay' must be assigned.
//Post: annual pay is set.
void SalaryEmployee::setAnnualPay(double pay){
    annualPay_ = pay;
}
//Description: getter for annual pay
//Pre: Object of 'SalaryEmployee' must exist. annual pay must be assigned.
//Post: returns double of annual pay.
double SalaryEmployee::getAnnualPay(){
    return annualPay_;
}
//Description: getter for weekly pay.
//Pre: Object of 'SalaryEmployee' must exist. Weekly pay must be calculated.
//Post: returns double of weekly pay.
double SalaryEmployee::getWeeklyPay(){
    return weeklyPay_;
}
//Description: Override of makeNoise, outputs random string.
//Pre: Object of 'SalaryEmployee' must exist, printEmployeeRecords must be called.
//Post: returns one of three strings.
void SalaryEmployee::makeNoise(){
    string one = "Yeah, if you could remember to put the new cover page on the TPS reports that would be great.";
    string two = "Yeah...I’m gonna need you to come in on Saturday.";
    string three = "Oh, oh, and I almost forgot. Ahhh, I’m also gonna need you to go ahead and come in on Sunday, too.";
    randomize(one, two, three);
    cout << one << endl;
}
//Description: Implementation of abstract calculatePay, calculates weekly pay from annual pay field.
//Pre: Object of 'SalaryEmployee' must exist, annual pay must be set.
//Post: sets weeklyPay field from annual/52.
void SalaryEmployee::calculatePay(){
    weeklyPay_ = annualPay_/52;
}
//Description: Implementation of abstract printEmployeeRecord. Prints all field of employee info to console.
//Pre: Object of 'SalaryEmployee' must exist. All fields must be assigned.
//Post: Outputs employee attributes to console.
void SalaryEmployee::printEmployeeRecord(){
    calculatePay();
    cout << "Employee: " << getName() << endl;
    cout << "SSN: " << getSocialSec() << endl;
    cout << "Employee Number: " << getEmployeeNumber() << endl;
    cout << "Tax rate: " << getTax() << endl;
    cout << "Gross annual salary: " << annualPay_ << endl;
    cout << "Annual net salary: " << (annualPay_ - (getTax()*annualPay_)) << endl;
    cout << "weekly salary: " << getWeeklyPay() << endl;
    cout << "Intercom: ";
    makeNoise();
}
