#include "AgencyEmployee.h"
#include <iostream>
#include <string>
#include "Employee.h"
#include <sstream>
#include <cstdlib>
#include "Exception.cpp"
using namespace std;


AgencyEmployee::AgencyEmployee(){}//default constructor

//Description: setter for 'company name'.
//Pre: Object of 'AgencyEmplyee' must exist, 'name' must be assigned.
//Post: sets company name to parameter.
void AgencyEmployee::setCompanyName(string name){
    companyName_ = name;
}
//Description: getter for 'company name'.
//Pre: Object of 'agencyEmplyee' must exist, company name must be assigned.
//Post: returns string of name.
string AgencyEmployee::getCompanyName(){
    return companyName_;
}
//Description: override of makeNoise, outputs random string.
//Pre: Object of 'agencyEmplyee' must exist, printEmployeeRecords must be called.
//Post: outputs one of three strings.
void AgencyEmployee::makeNoise(){//implement randomizer fuction to select one at random
    string one = "Right, so there’s three more people we can easily lose.";
    string two = "So what would you say you do here?";
    string three = "We fixed the glitch.";
    randomize(one, two, three);
    cout << one << endl;
}
//Description: Implementation of abstract calculatePay. Calculates, and sets field of 'amount earned' from inputted variables.
//Pre: Object of 'agencyEmplyee' must exist, Hourly pay and rate must be assigned.
//Post: sets amount earned.
void AgencyEmployee::calculatePay(){//agency employees dont get overtime
    auto hoursWorked = getHoursWorked();
    auto hourlyRate = getHourlyPay();
    auto earned = hourlyRate * hoursWorked;
    setAmountEarned(earned); //sets amount earned
}
//Description: Implementation of abstract printEmployeeRecord. Formats display of output.
//Pre: Object of 'agencyEmplyee' must exist, all private fields must be assigned.
//Post: Displays employee attributes to console.
void AgencyEmployee::printEmployeeRecord(){
    calculatePay();//calcuate pay to set amount earned
    cout << "Employee: " << getName() << endl;
    cout << "SSN: " << getSocialSec() << endl;
    cout << "Employee Number: " << getEmployeeNumber() << endl;
    cout << "Tax rate: " << getTax() << endl;
    cout << "Hourly Rate: " << getHourlyPay() << endl;
    cout << "Hours worked: " << getHoursWorked() << endl;
    cout << "Gross amount earned: " << getAmountEarned() << endl;
    cout << "Net income: "<< getAmountEarned() + (getAmountEarned() * getTax()) << endl;//i
    cout << "Company Name: " << getCompanyName() << endl;
    cout << "intercom: ";
    makeNoise();
}
