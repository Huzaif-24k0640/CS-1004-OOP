#include "LabCourse.h"
#include <iostream>
using namespace std;

LabCourse::LabCourse (string cc, int c): Course(cc, c) {}

void LabCourse::calculateGrade (int m) {
	cout << "Grade: " << m * credits << endl;
}

void LabCourse::displayInfo () {
	cout << "Lab Course Info: \nCourse Code: " << courseCode << "\nTotal Credits: " << credits << endl;
}
