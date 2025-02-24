#include <iostream>
using namespace std;

class Car {
private:
    string brand;
    string model;
    double fuelCapacity;  
    double currentFuel;

public:
    Car(string carBrand, string carModel, double capacity) 
        : brand(carBrand), model(carModel), fuelCapacity(capacity), currentFuel(capacity) {
        cout << "Car " << brand << " " << model << " initialized with full tank: " << currentFuel << "L\n";
    }

    void drive(double distance) {
        double fuelNeeded = distance / 12.0;

        if (fuelNeeded > currentFuel) {
            cout << "Not enough fuel! You can drive only " << currentFuel * 12 << " km.\n";
        } else {
            currentFuel -= fuelNeeded;
            cout << "Drove " << distance << " km. Fuel used: " << fuelNeeded << "L. Remaining fuel: " << currentFuel << "L\n";
        }
        checkFuelStatus();
    }

    void refuel(double amount) {
        if (amount <= 0) {
            cout << "Invalid refuel amount!\n";
            return;
        }
        if (currentFuel + amount > fuelCapacity) {
            cout << "Tank overflow!.\n";
            currentFuel = fuelCapacity;
        } else {
            currentFuel += amount;
            cout << "Added " << amount << "L. Current fuel: " << currentFuel << "L\n";
        }
    }

    void checkFuelStatus() {
        cout << "Fuel Level: " << currentFuel << "/" << fuelCapacity << "L\n";
        if (currentFuel < 5) {
            cout << "Low fuel! Please refuel soon!\n";
        }
    }
};

int main() {

    Car zoyaCar("Toyota", "Corolla", 50);

    zoyaCar.drive(100);
    zoyaCar.drive(300);
    zoyaCar.refuel(20); 
    zoyaCar.drive(450);  
    zoyaCar.refuel(30); 
    zoyaCar.drive(600); 

    return 0;
}
