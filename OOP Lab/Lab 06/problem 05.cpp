#include <iostream>
using namespace std;

class Device {
public:
    int deviceID;
    bool status;
    
    Device (int id, bool s): deviceID (id), status (s) {}
    
    void displayDetailsDevice () {
        cout << "Device ID: " << deviceID << endl;
        cout << "Status: ";
        if (status == true) {
            cout << "Working!" << endl;
        } else {
            cout << "Not working!" << endl;
        }
    }
    
};

class SmartPhone: public Device {
public:
    float screenSize;
    
    SmartPhone (int id, bool s, float ss): Device (id, s), screenSize (ss) {}
    
    void displayDetailsSmartPhone () {
        displayDetailsDevice ();
        cout << "Screen size: " << screenSize << endl;
    }
};

class SmartWatch: public SmartPhone {
public:
    bool heartRateMonitor;
    
    SmartWatch (int id, bool s, float ss, bool hrm): SmartPhone (id, s, ss), heartRateMonitor (hrm) {}
    
    void displayDetailsSmartWatch () {
        displayDetailsSmartPhone ();
        cout << "Heart rate monitor: ";
        if (heartRateMonitor == false) {
            cout << "Heart rate is Normal!" << endl;
        } else {
            cout << "Heart rate Abnormal!" << endl;
        }
    }
    
};

class SmartWearable: public SmartWatch {
public:
    int stepCounter;
    
    SmartWearable (int id, bool s, float ss, float hrm, int sc): SmartWatch (id, s, ss, hrm), stepCounter (sc) {}
    
    void displayDetailsSmartWearable () {
        cout << "Smart wearable details: " << endl;
        displayDetailsSmartWatch();
        cout << "Total steps taken: " << stepCounter;
    }
};

int main () {
    SmartWearable sw1 (100, true, 5.5, false, 5000);
    sw1.displayDetailsSmartWearable ();
    
    return 0;
}
