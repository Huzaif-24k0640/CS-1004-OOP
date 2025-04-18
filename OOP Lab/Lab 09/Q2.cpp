#include <iostream>
using namespace std;

class MenuItem {
public:
    string dishName;
    double price;

    MenuItem(string d, double p) : dishName (d), price (p) {}

    virtual void showDetails () = 0;

    virtual void prepare () = 0;

};

class Appetizer : public MenuItem{
    public:

    Appetizer (string n, double p) : MenuItem (n, p) {}

    void showDetails () {
	cout <<  "Appetizer-----\n";
        cout << "Dish Name " << dishName << "\nCost " << price << endl;
    }

    void prepare () {
	cout <<  "Preparing Appetizer-----\n";
    }

};

class MainCourse: public MenuItem{
    public:
    MainCourse(string n, double p) : MenuItem (n, p) {}

    void showDetails () {
	cout <<  "MainCourse-----\n";
        cout << "Dish Name " << dishName << "\nCost " << price << endl;
    }

    void prepare () {
	cout <<  "Preparing Main COurse-----\n";
  
    }

};

int main () {
    Appetizer a1("ABC", 500);
    MainCourse m1("XYZ", 100);

    a1.showDetails ();
    a1.prepare ();

    m1.showDetails ();
    m1.prepare ();

    return 0;
}
