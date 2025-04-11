#include <iostream>
#include <string>
using namespace std;

class Car;

class InventoryManager;

class Car {
private:
    string model;
    double price;

public:
    Car(string m, double p) : model(m), price(p) {}

    friend class InventoryManager;
    friend void comparePrice(const Car& car1, const Car& car2);
};

class InventoryManager {
public:
    void updatePrice(Car& car, double newPrice) const {
        if (newPrice >= 0) {
            car.price = newPrice;
            cout << "Updated price of " << car.model << " to $" << newPrice << endl;
        } else {
            cout << "Invalid price. Price must be non-negative." << endl;
        }
    }

    void displayCar(const Car& car) const {
        cout << "Model: " << car.model << ", Price: $" << car.price << endl;
    }
};

void comparePrice(const Car& car1, const Car& car2) {
    cout << "Comparing prices of " << car1.model << " and " << car2.model << ":" << endl;
    if (car1.price > car2.price) {
        cout << car1.model << " is more expensive." << endl;
    } else if (car2.price > car1.price) {
        cout << car2.model << " is more expensive." << endl;
    } else {
        cout << "Both cars are priced equally." << endl;
    }
}

int main() {
    Car car1("Suzuki Alto", 20000.0);
    Car car2("Mercedes Benz", 22000.0);

    InventoryManager manager;

    cout << "Initial Car Details:" << endl;
    manager.displayCar(car1);
    manager.displayCar(car2);

    cout << "\nUpdating Prices:" << endl;
    manager.updatePrice(car1, 21000.0);
    manager.updatePrice(car2, 21000.0);

    cout << "\nUpdated Car Details:" << endl;
    manager.displayCar(car1);
    manager.displayCar(car2);

    cout << "\nPrice Comparison:" << endl;
    comparePrice(car1, car2);

    return 0;
}
