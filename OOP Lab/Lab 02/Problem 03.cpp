/*
* Name: Huzaif Ali
* Class: BCS-2C
* Question: 03
 */

/*
* Develop a program to calculate the total salary of employees using structures. Each employee has a name, hoursWorked, and hourly Rate. The program should: 
* 1. Allow the user to input details for multiple employees. 
* 2. Dynamically allocate memory for the employees. 
* 3. Calculate the total salary for each employee (hoursWorked hourly Rate). 
* 4. Display the results and deallocate memory. 
*/

#include <iostream>
#include <string>
using namespace std;

struct Employee {
    string name;
    int hoursWorked;
    double hourlyRate;
};


void inputEmployees(Employee* employees, int numEmployees) {
    for (int i = 0; i < numEmployees; i++) {
        cout << "Enter details for Employee " << i + 1 << ":\n";
        cout << "Name(without space): ";
        cin >> employees[i].name;
        cout << "Hours Worked: ";
        cin >> employees[i].hoursWorked;
        cout << "Hourly Rate: ";
        cin >> employees[i].hourlyRate;
    }
}


void displaySalaries(Employee* employees, int numEmployees) {
    cout << "\nEmployee Salary Details:\n";
    for (int i = 0; i < numEmployees; i++) {
        double totalSalary = employees[i].hoursWorked * employees[i].hourlyRate;
        cout << "Name: " << employees[i].name << ", Hours Worked: " << employees[i].hoursWorked << ", Hourly Rate: $" << employees[i].hourlyRate << ", Total Salary: $" << totalSalary << "\n";
    }
}

int main() {
    int numEmployees;

    // 1. Number of Employees
    cout << "Enter the number of employees: ";
    cin >> numEmployees;

    // 2. Allocation
    Employee* employees = new Employee[numEmployees];

    // 3. Input
    inputEmployees(employees, numEmployees);

    // 4 Display
    displaySalaries(employees, numEmployees);

    // 5. Deallocation
    delete[] employees;

    return 0;
}
