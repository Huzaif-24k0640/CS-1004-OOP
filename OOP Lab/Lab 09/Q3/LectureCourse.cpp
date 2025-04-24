#include "LectureCourse.h"
#include <iostream>
using namespace std;

LectureCourse::LectureCourse (string cc, int c): Course(cc, c) {}

void LectureCourse::calculateGrade (int m) {
	cout << "Grade: " << m * credits << endl;
}

void LectureCourse::displayInfo () {
	cout << "Lecture Course Info: \nCourse Code: " << courseCode << "\nTotal Credits: " << credits << endl;
}
