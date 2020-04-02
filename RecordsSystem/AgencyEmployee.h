#pragma once
#include "Employee.h"
#include "HourlyEmployee.h"
using namespace std;


class AgencyEmployee: public HourlyEmployee{
private:
    string companyName_;
public:
    AgencyEmployee();
    void setCompanyName(string name);
    string getCompanyName();
    void makeNoise();
    void calculatePay();
    void printEmployeeRecord();
};

