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
    void displayReport () {
        cout << "--- Thermometer Report ---\nFetching Data from sensors." << endl; 
        readData ();
        }
};

class Barometer : public WeatherSensor {
public:
    void readData () { cout << "Please wait, sensors are readind Data...\n\n"; }
    void displayReport () {
        cout << "--- Barometer Report ---\nFetching Data from sensors." << endl; 
        readData ();
    }
};

int main() {
    Thermometer t;
    Barometer b;
    
    t.displayReport ();
    b.displayReport ();
    
    return 0;
}
