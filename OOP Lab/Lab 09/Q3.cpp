#include <iostream>
using namespace std;

class Course {
public:
    string CourseCode;
    int CreditHour;

    Course(string cc, int ch) : CourseCode (cc), CreditHour (ch) {}

    virtual void calculateGrade () = 0;

    virtual void DisplayInfo () = 0;
};

class LectureCourse : public Course{
    public:

    LectureCourse (string cc, intcp) : Course (cc, ch) {}

    void calculateGrade () {
	cout <<  "LectureCourse-----\n";
        cout << "Dish Name " << CourseCode << "\nCost " << CreditHour << endl;
    }

    void DisplayInfo () {
	cout <<  "Preparing LectureCourse-----\n";
    }

};

class MainCourse: public Course{
    public:
    MainCourse(string n, int p) : Course (n, p) {}

    void calculateGrade () {
	cout <<  "MainCourse-----\n";
        cout << "Dish Name " << CourseCode << "\nCost " << CreditHour << endl;
    }

    void DisplayInfo () {
	cout <<  "Preparing Main COurse-----\n";
  
    }

};

int main () {
    LectureCourse a1("ABC", 500);
    MainCourse m1("XYZ", 100);

    a1.calculateGrade ();
    a1.DisplayInfo ();

    m1.calculateGrade ();
    m1.DisplayInfo ();

    return 0;
}
