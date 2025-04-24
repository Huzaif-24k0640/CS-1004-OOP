#pragma once

#include <iostream>
using namespace std;

class Course {
	public:
		string courseCode;
		int credits;
		Course (string cc, int c) : courseCode (cc), credits (c) {}

		virtual void calculateGrade (int m) = 0;
		virtual void displayInfo () = 0;
};
