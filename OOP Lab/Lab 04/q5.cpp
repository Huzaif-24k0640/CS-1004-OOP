#include <iostream>

using namespace std;

class Car {
private:
    string brand;
    string model;
    double rentalPrice;
    bool isAvailable;
    double totalRevenue;
    int carID;

public:
    Car() : brand("Unknown"), model("Generic"), rentalPrice(0.0), isAvailable(true), totalRevenue(0.0), carID(0) {}

    Car(int id, string newBrand, string newModel, double newPrice, bool availability) 
        : carID(id), brand(newBrand), model(newModel), rentalPrice(newPrice), isAvailable(availability), totalRevenue(0.0) {}

    Car(const Car &other) 
        : carID(other.carID), brand(other.brand), model(other.model), rentalPrice(other.rentalPrice), 
          isAvailable(other.isAvailable), totalRevenue(other.totalRevenue) {
        cout << "Copy Constructor: A copy of Car ID " << carID << " (" << brand << " " << model << ") has been created.\n";
    }

    ~Car() {
        cout << "Destructor: Car ID " << carID << " (" << brand << " " << model << ") is being removed from memory.\n";
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

    void applyDiscount(int rentalDays, double &finalPrice) {
        if (rentalDays > 10) {
            finalPrice *= 0.90;
        } else if (rentalDays > 5) {
            finalPrice *= 0.95;
        }
    }

    void rentCar(int rentalDays) {
        if (!isAvailable) {
            cout << "Sorry, Car ID " << carID << " is already rented.\n";
            return;
        }

        double finalPrice = rentalPrice;
        applyDiscount(rentalDays, finalPrice);
        double rentalCost = finalPrice * rentalDays;

        this->totalRevenue += rentalCost;
        this->isAvailable = false;

        cout << "Car ID " << carID << " rented successfully for " << rentalDays << " days!\n";
        cout << "Total rental cost: $" << rentalCost << "\n";
    }

    void returnCar() {
        isAvailable = true;
        cout << "Car ID " << carID << " has been returned and is now available for rent.\n";
    }

    void displayDetails() const {
        cout << "Car ID: " << carID
             << "\nBrand: " << brand 
             << "\nModel: " << model
             << "\nRental Price: $" << rentalPrice 
             << "\nAvailable: " << (isAvailable ? "Yes" : "No") 
             << "\nTotal Revenue: $" << totalRevenue << "\n";
    }
};

int main() {
    Car car1(101, "Toyota", "Corolla", 50.0, true);
    Car car2(102, "Honda", "Civic", 60.0, true);

    cout << "\n--- Car Fleet Details ---\n";
    car1.displayDetails();
    car2.displayDetails();

    cout << "\n--- Renting Car 101 for 7 Days ---\n";
    car1.rentCar(7);
    car1.displayDetails();

    cout << "\n--- Returning Car 101 ---\n";
    car1.returnCar();
    car1.displayDetails();

    cout << "\n--- Renting Car 102 for 12 Days ---\n";
    car2.rentCar(12);
    car2.displayDetails();

    cout << "\n--- Copying Car 102 ---\n";
    Car car3 = car2;
    car3.displayDetails();

    return 0;
}
