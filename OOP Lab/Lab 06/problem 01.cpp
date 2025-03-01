#include <iostream>
using namespace std;

class Employee {
public:
    string name;
    float salary;
    
    Employee (string n, float s): name(n), salary(s){}

    void employeeDetails () {
        cout << "\nEmployee Name: " << name << "\nSalary: $" << salary << endl;
    } 

};

class Manager: public Employee {
public:
    float bonus;
    
    Manager (string n, float s, float b): Employee (n, s), bonus(b) {}
    
    void managerDetails () {
        employeeDetails();
        cout << "Bonus: $" << bonus << endl;
	cout << "Total Income: $" << salary + bonus << endl;
    }   

};

int main() {
    Manager m1 ("Syed_Huzaif", 10000.0, 1000.0);
  
    m1.managerDetails();
  
    return 0;
}
