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

    Car(string newBrand, string newModel, double newPrice, bool availability) {
        brand = newBrand;
        model = newModel;
        rentalPrice = newPrice;
        isAvailable = availability;
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

    void applyDiscount(int rentalDays) {
        double finalPrice = rentalPrice;
        if (rentalDays > 10) {
            finalPrice *= 0.90;
        } else if (rentalDays > 5) {
            finalPrice *= 0.95;
        }
        cout << "Total price for " << rentalDays << " days: $" << finalPrice * rentalDays << "\n";
    }

    void rentCar(int rentalDays) {
        if (!isAvailable) {
            cout << "Sorry, the car is already rented.\n";
            return;
        }
        isAvailable = false;
        cout << "Car rented successfully!\n";
        applyDiscount(rentalDays);
    }

    void displayDetails() const {
        cout << "Brand: " << brand << "\nModel: " << model
             << "\nRental Price: $" << rentalPrice 
             << "\nAvailable: " << (isAvailable ? "Yes" : "No") << "\n";
    }
};

int main() {
    Car car1("Toyota", "Corolla", 50.0, true);
    Car car2("Honda", "Civic", 60.0, true);

    car1.displayDetails();
    car1.rentCar(7);
    car1.displayDetails();

    car1.rentCar(3);

    car2.displayDetails();
    car2.rentCar(12);

    return 0;
}
