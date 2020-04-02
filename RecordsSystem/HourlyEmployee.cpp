#include <iostream>
#include "HourlyEmployee.h"
#include <iostream>
#include <string>
#include "Employee.h"
#include <sstream>
#include <cstdlib>
#include "Exception.cpp"
using namespace std;

HourlyEmployee::HourlyEmployee(){}//default constructor

//Description: setter for hourly rate field. Checks if input is valid.
//Pre: Object of 'HourlyEmployee' must exist, rate must be assigned.
//Post: sets hourly pay rate.
void HourlyEmployee::setHourRate(double& rate){
    if(rate <= 100 && rate >=15){
        hourlyPay_ = rate;
    }else{
        InputException e(rate, "Hourly Rate", "Must be within 15 to 100 hour range.");
        throw(e);
    }
}
//Description: setter for hours worked.
//Pre: Object of 'HourlyEmployee' must exist, hours must be assigned.
//Post: sets number of hours worked.
void HourlyEmployee::setHoursWorked(double hours){
    if(hours > 40)
        numHoursWorked_ = 40;
    else
        numHoursWorked_ = hours;
    
}
//Description: setter for 'amount earned'.
//Pre: Object of 'HourlyEmployee' must exist, 'earned' must be calculated.
//Post: amount earned is set to calculated number.
void HourlyEmployee::setAmountEarned(double earned){//perform input verifications
    amountEarned_ = earned;
}
//Description: getter for hourly pay.
//Pre: Object of 'HourlyEmployee' must exist, hourly pay must be assigned.
//Post: returns double of hourly pay rate.
double HourlyEmployee::getHourlyPay(){
    return hourlyPay_;
}
//Description: getter for hours worked.
//Pre: Object of 'HourlyEmployee' must exist, hours worked must be assigned.
//Post: returns double of hours worked.
double HourlyEmployee::getHoursWorked(){
    return numHoursWorked_;
}
//Description: getter for amount earned.
//Pre: Object of 'HourlyEmployee' must exist. Amount earned must be assigned.
//Post: returns double of amount earned.
double HourlyEmployee::getAmountEarned(){
    return amountEarned_;
}
