#pragma once
#include "Employee.h"
#include "HourlyEmployee.h"
using namespace std;

class RegularEmployee: public HourlyEmployee{
private:
    double overtimeHours_;
public:
    RegularEmployee();
    void setOvertimeHours(double hours);
    double getOvertimeHours();
    void calculatePay();
    void printEmployeeRecord();
};
