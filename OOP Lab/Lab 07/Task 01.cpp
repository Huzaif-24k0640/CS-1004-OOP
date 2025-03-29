#include <iostream>
#include <string>
using namespace std;

class Device {
protected:
    int deviceID;
    string deviceName;
    bool status;
    string location;

public:
    Device(int id, string name, string loc = "Unknown") : deviceID(id), deviceName(name), status(false), location(loc) {}
    
    virtual void turnOn() { status = true; }
    virtual void turnOff() { status = false; }
    virtual float getStatus() { return status; }
    virtual void displayInfo() {
        cout << "Device ID: " << deviceID << "\nName: " << deviceName << "\nStatus: " << getStatus() << "\nLocation: " << location << "\n";
    }
};

class Light : public Device {
private:
    int brightnessLevel;
    string colorMode;

public:
    Light(int id, string name, string loc, int brightness, string color)
        : Device(id, name, loc), brightnessLevel(brightness), colorMode(color) {}

    void displayInfo() {
        Device::displayInfo();
        cout << "Brightness Level: " << brightnessLevel << "\nColor Mode: " << colorMode << "\n";
    }
};

class Thermostat : public Device {
private:
    float temperature;
    string mode;
    float targetTemperature;

public:
    Thermostat(int id, string name, string loc, float temp, string m, float target)
        : Device(id, name, loc), temperature(temp), mode(m), targetTemperature(target) {}

    float getStatus() {
        return temperature;
    }
};

class SecurityCamera : public Device {
private:
    string resolution;
    bool recordingStatus;
    bool nightVisionEnabled;

public:
    SecurityCamera(int id, string name, string loc, string res, bool nightVision)
        : Device(id, name, loc), resolution(res), nightVisionEnabled(nightVision), recordingStatus(false) {}

    void turnOn() {
        status = true;
        recordingStatus = true;
        cout << "Security Camera is now recording." << endl;
    }
};

class SmartPlug : public Device {
private:
    double powerConsumption;
    int timerSetting;

public:
    SmartPlug(int id, string name, string loc, double power, int timer)
        : Device(id, name, loc), powerConsumption(power), timerSetting(timer) {}

    void turnOff() {
        status = false;
        cout << "Power consumption recorded: " << powerConsumption << "W" << endl;
    }
};

int main() {
    Light light1(1, "Living Room Light", "Living Room", 75, "Warm White");
    Thermostat thermostat1(2, "Hallway Thermostat", "Hallway", 22.5f, "Cooling", 24.0f);
    SecurityCamera camera1(3, "Front Door Camera", "Front Door", "1080p", true);
    SmartPlug plug1(4, "TV Plug", "Living Room", 50.5, 2);

    light1.turnOn();
    thermostat1.turnOn();
    camera1.turnOn();
    plug1.turnOff();

    cout << "\nDevice Info:\n";
    light1.displayInfo();
    thermostat1.displayInfo();
    
    cout << "Current Temp: " << thermostat1.getStatus() << "°C" << endl;

    camera1.displayInfo();
    plug1.displayInfo();

    return 0;
}
