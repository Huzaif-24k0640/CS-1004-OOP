#include "Course.h"
#include "LectureCourse.h"
#include "LabCourse.h"
#include <iostream>
using namespace std;

int main () {
	LectureCourse lec ("CS1004", 3);
	lec.displayInfo ();
	lec.calculateGrade (72);

	LabCourse lab ("CL1004", 1);
	lab.displayInfo ();
	lab.calculateGrade (86);

	return 0;
}
