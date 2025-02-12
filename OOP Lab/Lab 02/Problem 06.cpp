/*
* Name: Huzaif Ali
* Class: BCS-2C
* Question: 06
*/

/*
* Develop a program to manage student records using dynamic memory allocation. Each student has a name, rollNumber, and marks in 3 subjects. The program should: 
* 1. Allow the user to input details for multiple students. 
* 2. Dynamically allocate memory for the students. 
* 3. Calculate the average marks for each student. 4. Display the results and deallocate memory. 
*/

#include <iostream>
using namespace std;

struct Student {
    char name[50];
    int rollNumber;
    float marks[3];
};

void inputStudents(Student* students, int numStudents) {
    for (int i = 0; i < numStudents; ++i) {
        cout << "Enter details for Student " << i + 1 << ":\n";
        cout << "Name(without space): ";
        cin >> students[i].name;
        cout << "Roll Number: ";
        cin >> students[i].rollNumber;
        cout << "Enter marks for 3 subjects: ";
        for (int j = 0; j < 3; ++j) {
            cin >> students[i].marks[j];
        }
    }
}

float calculateAverage(float marks[], int numSubjects) {
    float sum = 0;
    for (int i = 0; i < numSubjects; ++i) {
        sum += marks[i];
    }
    return sum / numSubjects;
}

void displayStudents(Student* students, int numStudents) {
    cout << "\nStudent Records:\n";
    for (int i = 0; i < numStudents; ++i) {
        float avgMarks = calculateAverage(students[i].marks, 3);
        cout << "Name: " << students[i].name
             << ", Roll Number: " << students[i].rollNumber
             << ", Average Marks: " << avgMarks << "\n";
    }
}

int main() {
    int numStudents;

    // 1. Number
    cout << "Enter the number of students: ";
    cin >> numStudents;

    // 2. Allocation
    Student* students = new Student[numStudents];

    // 3. Input
    inputStudents(students, numStudents);

    // 4. Display
    displayStudents(students, numStudents);

    // 5. Deallocation
    delete[] students;

    return 0;
}
