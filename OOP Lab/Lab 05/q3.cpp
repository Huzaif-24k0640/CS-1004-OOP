#include <iostream>
using namespace std;

class Employee {
public:
    string name;
    string designation;

    Employee(string name, string designation) {
        this->name = name;
        this->designation = designation;
    }
};

class Project {
public:
    string title;
    string deadline;
    Employee* employees[10];
    int employeeCount;

    Project(string title, string deadline) {
        this->title = title;
        this->deadline = deadline;
        employeeCount = 0;
    }

    void addEmployee(Employee* emp) {
        if (employeeCount < 10) {
            employees[employeeCount++] = emp;
        } else {
            cout << "Cannot add more employees to the project." << endl;
        }
    }

    void displayDetails() {
        cout << "Project: " << title << "\nDeadline: " << deadline << "\nEmployees Assigned:" << endl;
        for (int i = 0; i < employeeCount; i++) {
            cout << "- " << employees[i]->name << " (" << employees[i]->designation << ")" << endl;
        }
    }
};

int main() {
    Employee e1("Huzaif", "Developer");
    Employee e2("Hardeep", "Designer");
    Employee e3("Kazim", "Manager");

    Project p1("Project 1", "2025-03-01");
    Project p2("Project 2", "2025-06-15");

    p1.addEmployee(&e1);
    p1.addEmployee(&e2);
    p2.addEmployee(&e2);
    p2.addEmployee(&e3);

    cout << "\nProject Details:\n";
    p1.displayDetails();
    cout << "\n";
    p2.displayDetails();
    
    return 0;
}
