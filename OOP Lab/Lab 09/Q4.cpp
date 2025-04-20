#include <iostream>
using namespace std;

class WeatherSensor {
public:
    virtual void readData () = 0;
    virtual void displayReport () = 0;
};

class Thermometer : public WeatherSensor {
public:
    void readData () { cout << "Please wait, sensors are readind Data...\n\n"; }
    void displayReport () { cout << "--- Thermometer Report ---\nFetching Data from sensors." << endl; }
};

class Barometer : public WeatherSensor {
public:
    void readData () { cout << "Please wait, sensors are readind Data...\n\n"; }
    void displayReport () { cout << "--- Barometer Report ---\nFetching Data from sensors." << endl; }
};

int main() {
    Thermometer t;
    Barometer b;
    
    t.displayReport ();
    t.readData ();
    
    b.displayReport ();
    b.readData ();
    
    return 0;
}
