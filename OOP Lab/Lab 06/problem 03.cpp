#include <iostream>
using namespace std;

class Person {
public:
    string name;
    int age;
    
    Person (string n, int a): name (n), age (a) {} 
    
    void displayDetailsPerson () {
        cout << "Name: " << name << "\nAge: " << age << " years" << endl;
    }
    
};

class Teacher: public Person {
public:
    string subject;
    
    Teacher (string n, int a, string s): Person (n, a), subject (s) {}
    
    void displayDetailsTeacher () {
        displayDetailsPerson ();
        cout << "Subject: " << subject << endl;
    }
};

class Researcher {
 public:
    string researchArea;
    
    Researcher (string ra): researchArea (ra) {}
    
    void displayDetailsResearcher () {
        cout << "Research Area: " << researchArea << endl;
    }
    
};

class Professor: public Teacher, public Researcher {
public:
    int publications;
    
   Professor (string n, int a, string s, string ra, int p): Teacher (n, a, s), Researcher (ra), publications (p) {}
    
    void displayDetailsProfessor () {
        cout << "\nProfessor Details:" << endl;
        displayDetailsTeacher ();
        displayDetailsResearcher ();
        cout << "Publications: " << publications << endl;
    }
    
};
int main () {
    Professor p1 ("ABC", 40, "Science", "Biology", 2020);
    p1.displayDetailsProfessor ();

    return 0;
}
