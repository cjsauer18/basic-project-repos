#pragma once
#include "Employee.h"
using namespace std;

class HourlyEmployee: public Employee{
private:
    double hourlyPay_;
    double numHoursWorked_;
    double amountEarned_;
public:
    HourlyEmployee();
    void setHourRate(double& rate);
    void setHoursWorked(double hours);
    void setAmountEarned(double amount);
    double getHourlyPay();
    double getHoursWorked();
    double getAmountEarned();
    
};
