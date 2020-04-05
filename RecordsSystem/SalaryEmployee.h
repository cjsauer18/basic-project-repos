#pragma once
#include "Employee.h"
using namespace std;

class SalaryEmployee: public Employee{
private:
    double annualPay_ = 0;
    double weeklyPay_;
public:
    SalaryEmployee();
    void setAnnualPay(double pay);
    double getAnnualPay();
    double getWeeklyPay();
    void makeNoise();
    void calculatePay();
    void printEmployeeRecord();
};
