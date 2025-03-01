#include <iostream>
using namespace std;

class Vehicle {
public:
    string brand;
    int speed;
    
    Vehicle (string b, int s): brand(b), speed(s){}
    void vehicleDetails () {
	cout << "\nCar Details: " << endl;
        cout << "Brand name: " << brand << "\nMaximum speed: " << speed << " km/h" << endl;
    }
    
};

class Car: public Vehicle {
public:
    int seats;
    
    Car (string b, int s, int st): Vehicle (b, s), seats(st) {}
    
    void carDetails () {
        vehicleDetails();
        cout << "Number of seats: " << seats << endl;
    }
    
};

class ElectricCar: public Car {
public:
    int batteryLife;
    
    ElectricCar (string b, int s, int st, int bl): Car (b, s, st), batteryLife(bl) {}
    
    void electricCarDetails () {
        carDetails();
        cout << "Battery life: " << batteryLife << " minutes" << endl;
    }
    
};

int main() {
    ElectricCar e1 ("Toyota", 260, 4, 300);

    e1.electricCarDetails();

    return 0;
}
