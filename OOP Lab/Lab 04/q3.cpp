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

    Car(const Car &other) {
        brand = other.brand;
        model = other.model;
        rentalPrice = other.rentalPrice;
        isAvailable = other.isAvailable;
        cout << "Copy Constructor: A copy of " << brand << " " << model << " has been created.\n";
    }

    ~Car() {
        cout << "Destructor: Car " << brand << " " << model << " is being removed from memory.\n";
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
    cout << "\nOriginal Car Details:\n";
    car1.displayDetails();

    Car car2 = car1; // Copy Constructor is called
    cout << "\nCopied Car Details:\n";
    car2.displayDetails();

    car1.updateDetails("Honda", "Civic", 60.0);
    cout << "\nAfter modifying the original car:\n";
    car1.displayDetails();
    
    cout << "\nCopied Car should remain unchanged:\n";
    car2.displayDetails();

    return 0;
}
