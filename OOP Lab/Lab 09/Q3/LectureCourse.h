#pragma once

#include "Course.h"
#include <iostream>
using namespace std;

class LectureCourse: public Course {
	public:
		LectureCourse (string cc, int c);

		void calculateGrade (int m);
		void displayInfo ();
};
