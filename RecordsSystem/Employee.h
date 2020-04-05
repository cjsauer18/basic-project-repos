#pragma once
#include <string>
using namespace std;


class Employee{
private:
    string lastName_;
    string firstName_;
    string socialSec_;
    string employeeNumber_;
    double taxRate_;
public:
    Employee();
    void setFirstName(string first);
    void setLastName(string second);
    void setSSN(string& ssn);//references allow for referencing in exception handling
    void setEmployeeNumber(string& num);
    void setTaxRate(int& rate);
    string getName();
    string getSocialSec();
    double getTax();
    string getEmployeeNumber();
    virtual void makeNoise();
    virtual void calculatePay() = 0;
    virtual void printEmployeeRecord() = 0;
    void randomize(string& one, string& two, string& three);//helper
};

