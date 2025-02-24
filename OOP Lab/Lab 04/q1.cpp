#include <iostream>

using namespace std;

class Car {
private:
    string brand;
    string model;
    double rentalPrice;
    bool isAvailable;

public:
    Car() {
        brand = "Unknown";
        model = "Generic";
        rentalPrice = 0.0;
        isAvailable = true;
    }

    void updateDetails(string newBrand, string newModel, double newPrice) {
        brand = newBrand;
        model = newModel;
        rentalPrice = newPrice;
        cout << "Car details updated successfully.\n";
    }

    bool checkAvailability() const {
        return isAvailable;
    }

    void rentCar() {
        if (isAvailable) {
            isAvailable = false;
            cout << "Car rented successfully!\n";
        } else {
            cout << "Sorry, the car is already rented.\n";
        }
    }

    void displayDetails() const {
        cout << "Brand: " << brand << "\nModel: " << model
             << "\nRental Price: $" << rentalPrice 
             << "\nAvailable: " << (isAvailable ? "Yes" : "No") << "\n";
    }
};

int main() {
    Car myCar;
    myCar.displayDetails();

    myCar.updateDetails("Toyota", "Corolla", 50.0);
    myCar.displayDetails();

    myCar.rentCar();
    myCar.displayDetails();

    myCar.rentCar();

    return 0;
}
