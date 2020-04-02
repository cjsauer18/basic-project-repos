#include <iostream>
#include <vector>
#include "Employee.h"
#include <sstream>
#include <string>
#include <cstdlib>
#include <exception>
#include "Exception.cpp"
#include "AgencyEmployee.h"
#include "SalaryEmployee.h"
#include "RegularEmployee.h"

using namespace std;
//Description: Template retry class gets called when an exception is caught. Function is given
//a pointer to the variable that user will reinput along with a description of where it occured.
//Pre: An error must be detected in user input format
//Post: User input will be re entered
template <class T> void retry(T* input, string where){
    while(!cin.fail()){//checks if T matches cin input
        T temp;
        cout << endl;
        cout << "Re-Enter value for " << where << ": ";
        cin >> temp;
        cin.clear();
        cin.ignore();
        *input = temp;
        break;
    }
}
//Description: Input fields for standard employee attributes
//Pre: an instance of Employee must exist.
//Post: Name, ssn, eNumber and tax rate are assigned values
void standard(string& first, string& last, string& ssn, string& num, int& taxRate){
    while(true){
        cout << "Set first name: ";
        cin >> first; cout << endl;
        cout << "Set last name: ";
        cin >> last; cout << endl;
        cout << "Enter SSN: ";
        cin >> ssn; cout << endl;
        cout << "Employee Number: ";
        cin >> num; cout << endl;
        cout << "Tax rate: ";
        cin >> taxRate; cout << endl;
        if(cin.fail()){//general fail case scenario. Reprompt.
            cin.clear();
            cin.ignore();
            cout << "Error, record couldn't store value, try again." << endl;
        }else{
            break;
        }
    }
}
//Description: Input field for salary employee
//Pre: An instance of object 'salary employee' must exist.
//Post: pay is assigned
void salary(double& pay){
    cout << "Set annual pay: ";
    cin >> pay; cout << endl;
}
//Description: Input fields for regular employee attributes
//Pre: Instance of object 'regular employee' must exist.
//Post: Hours, rate and overtime hours are assigned.
void reg(int& hours, double& rate, int& overHours){
    while(true){
        cout << "Hourly Rate: ";
        cin >> rate; cout << endl;
        cout << "Hours Worked: ";
        cin >> hours; cout << endl;
        cout << "Overtime: ";
        cin >> overHours; cout << endl;
        if(cin.fail()){//general fail case scenario. Reprompted after later exception is caught.
            cin.clear();
            cin.ignore();
            cout << "Error, retry" << endl;
        }else{
            break;
        }
    }
}
//Description: Input fields for agency employee.
//Pre: Instance of object 'agency employee' must exist.
//Post: Hours, rate and company name are assigned.
void agency(int& hours, double& rate, string& companyName){
    while(true){
        cout << "Hourly Rate: ";
        cin >> rate; cout << endl;
        cout << "Hours Worked: ";
        cin >> hours; cout << endl;
        cout << "Company Name: ";
        cin >> companyName; cout << endl;
        if(cin.fail()){//general fail case scenario. Reprompted after later exception is caught.
            cin.clear();
            cin.ignore();
            cout << "Error, retry" << endl;
        }else{
            break;
        }
    }
}
int main(){
    vector<Employee*>Employees;//holds employee objects
    while(true){//main loop
        string selection;
        //main menu
        cout << "---------------------------------------------" << endl;
        cout << "To create employee template: " << endl;
        cout << "(1) Salary" << endl << "(2) Regular" << endl << "(3) Agency" << endl;
        cout << "To print employee records: " << endl;
        cout << "(4) Print Records" << endl;
        cout << "(5) Exit" << endl;
        cout << "Choice: ";
        cin >> selection;
        cout << "---------------------------------------------" << endl;
        cout << selection << endl;
         string first; string last; string ssn; string num; int taxRate; double pay;  int hours; double rate; int overHours;  string companyName;
        if(selection == "1"){//make new salary employee
            SalaryEmployee* sEmployee = new SalaryEmployee();
           // string first; string last; string ssn; string num; int taxRate; double pay;
            standard(first, last, ssn, num, taxRate);
            salary(pay);
                while(true){//runs until all are entered
                    try{
                        sEmployee->setFirstName(first);
                        sEmployee->setLastName(last);
                        sEmployee->setSSN(ssn);
                        sEmployee->setEmployeeNumber(num);
                        sEmployee->setTaxRate(taxRate);
                        sEmployee->setAnnualPay(pay);
                        Employees.push_back(sEmployee);//push to employee list
                        break;//input is valid
                    }catch(InputException &e){//exception object returns what failed and what to re-enter.
                        cout << e.what() << endl;
                        if(e.input_){
                            retry(e.input_, e.where_);
                        }if(e.inputNum_){
                            retry(e.inputNum_, e.where_);
                        }if(e.inputDouble_){
                            retry(e.inputDouble_, e.where_);
                        }
                    }
            }
        }
        else if(selection == "2"){//make new regular employee
         //   string first; string last; string ssn; string num; int taxRate; int hours; double rate; int overHours;
            standard(first, last, ssn, num, taxRate);//standard employee fields
            reg(hours, rate, overHours); //regular employee fields
            RegularEmployee* rEmployee = new RegularEmployee();
                while(true){//runs until all are entered
                    try{
                        rEmployee->setFirstName(first);
                        rEmployee->setLastName(last);
                        rEmployee->setSSN(ssn);
                        rEmployee->setEmployeeNumber(num);
                        rEmployee->setTaxRate(taxRate);
                        rEmployee->setHourRate(rate);
                        rEmployee->setHoursWorked(hours);
                        rEmployee->setOvertimeHours(overHours);
                        Employees.push_back(rEmployee);//pust to employee list
                        break;//every input is valid
                    }catch(InputException &e){//exception object returns what failed and what to re-enter.
                        cout << e.what() << endl;
                        if(e.input_){
                            retry(e.input_, e.where_);
                        }if(e.inputNum_){
                            retry(e.inputNum_, e.where_);
                        }if(e.inputDouble_){
                            retry(e.inputDouble_, e.where_);
                        }
                    }
            }
        }
        else if(selection == "3"){//make new agency emplyee
         //   string first; string last; string ssn; string num; string companyName; int taxRate; int hours; double rate;
            standard(first, last, ssn, num, taxRate);//standard employee fields
            agency(hours, rate, companyName);//agency employee fields
            AgencyEmployee* aEmployee = new AgencyEmployee();
            while(true){
                try{
                    aEmployee->setFirstName(first);
                    aEmployee->setLastName(last);
                    aEmployee->setSSN(ssn);
                    aEmployee->setEmployeeNumber(num);
                    aEmployee->setTaxRate(taxRate);
                    aEmployee->setHourRate(rate);
                    aEmployee->setHoursWorked(hours);
                    aEmployee->setCompanyName(companyName);
                    Employees.push_back(aEmployee);//push to employee list
                    break;//every input is valid
                }catch(InputException &e){//exception object returns what failed and what to re-enter.
                    cout << e.what() << endl;
                     if(e.input_){
                        retry(e.input_, e.where_);
                    }if(e.inputNum_){
                        retry(e.inputNum_, e.where_);
                    }if(e.inputDouble_){
                        retry(e.inputDouble_, e.where_);
                    }
                }
            }
        }
        else if (selection == "4"){//print records
            for(auto i = Employees.begin(); i != Employees.end(); ++i){//loop through employee pointers
                auto temp = &(**i);//dereference the 'Employee' pointer that points to the pointer of employee subclass.
                temp->printEmployeeRecord();//call print function
                cout << endl;//formatting
            }
        }
        else if(selection == "5"){//stop
            break;
        }else{
            cout << "invalid selection" << endl;
        }
    }
}
