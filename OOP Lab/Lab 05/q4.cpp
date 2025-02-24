#include <iostream>
using namespace std;

class AlarmSystem {
private:
    string securityLevel;
public:
    AlarmSystem(string level) : securityLevel(level) {
        cout << "AlarmSystem created with security level: " << securityLevel << endl;
    }

    ~AlarmSystem() {
        cout << "AlarmSystem destroyed.\n";
    }

    void displayDetails() {
        cout << "Alarm Security Level: " << securityLevel << endl;
    }
};

class SmartHome {
private:
    AlarmSystem alarm; AlarmSystem
public:
    SmartHome(string level) : alarm(level) {
        cout << "SmartHome created with an AlarmSystem.\n";
    }

    ~SmartHome() {
        cout << "SmartHome destroyed.\n";
    }

    void displayDetails() {
        cout << "Smart Home Details:\n";
        alarm.displayDetails();
    }
};

int main() {
    SmartHome home("High");
    home.displayDetails();
    
    return 0;
}
