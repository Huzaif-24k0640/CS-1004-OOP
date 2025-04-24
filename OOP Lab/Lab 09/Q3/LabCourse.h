#pragma once

#include "Course.h"
#include <iostream>
using namespace std;

class LabCourse: public Course {
	public:
		LabCourse (string cc, int c);

		void calculateGrade (int m);
		void displayInfo ();
};
