#include <iostream>
#include <string>
#include "Employee.h"
#include <sstream>
#include <cstdlib>
#include "Exception.cpp"
#include "RegularEmployee.h"
using namespace std;


RegularEmployee::RegularEmployee(){}//default constructor

//Description: setter for overtime hours. Checks if current hoursWorked field is in correct range.
//Pre: Object of 'RegularEmployee' must exist. 'hours' must be assigned.
//Post: Sets overtime hours to hours.
void RegularEmployee::setOvertimeHours(double hours){//MAYBE: perform input verification (overtime hour threshhold)
    if(getHoursWorked() == 40){
        if((overtimeHours_ + hours) > 20 || hours > 20){
            overtimeHours_ = 20;
            cout << "Employee has worked maximum overtime limit" << endl;
        }else{
            overtimeHours_ = hours;
        }
    }else{
        overtimeHours_ = 0;
        cout << "Employee's current hours worked does not merit overtime pay" << endl;
    }
}
//Description: getter for overtime hours.
//Pre: Object of 'RegularEmployee' must exist, overtimeHours_ must be assigned.
//Post: Returns double of overtime hours.
double RegularEmployee::getOvertimeHours(){
    return overtimeHours_;
}
//Description: Implementation of abstract calculatePay. Calculates the hourly rate, with overtime hours included.
//Pre: Object of 'RegularEmployee' must exist, overtimeHours, hourlyPay and hoursWorked must be assigned.
//Post: sets amount earned to calculated rate.
void RegularEmployee::calculatePay(){
    auto hoursWorked = getHoursWorked();
    auto hourlyRate = getHourlyPay();
    auto overTimeHours = getOvertimeHours();
    auto earned = hourlyRate * hoursWorked + ((hourlyRate * 1.5) * overTimeHours);//hourly pay + hourly overtime pay
    setAmountEarned(earned); //sets amount earned
}
//Description: Implementation of abstract printEmployeeRecords. Prints out employee data to console.
//Pre: Object of 'RegularEmployee' must exist, all fields must be assigned.
//Post: Outputs employee attributes to console.
void RegularEmployee::printEmployeeRecord(){
    calculatePay();
    cout << "Employee: " << getName() << endl;
    cout << "SSN: " << getSocialSec() << endl;
    cout << "Employee Number: " << getEmployeeNumber() << endl;
    cout << "Tax rate: " << getTax() << endl;
    cout << "Hourly Rate: " << getHourlyPay() << endl;
    cout << "Hours worked: " << getHoursWorked() << endl;
    cout << "Overtime: " << getOvertimeHours() << endl;
    cout << "Gross amount earned: " << getAmountEarned() << endl;
    cout << "Net income: "<< getAmountEarned() + (getAmountEarned() * getTax()) << endl;//i think this is right
    cout << "Intercom: ";
    makeNoise();
}
