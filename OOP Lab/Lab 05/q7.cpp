#include <iostream>
using namespace std;

class Product {
public:
    int id;
    string name;
    int quantity;

    Product(int i, string n, int q) : id(i), name(n), quantity(q) {}

    void displayDetails() {
        cout << "Product ID: " << id << ", Name: " << name 
             << ", Quantity: " << quantity << endl;
    }
};

class Warehouse {
private:
    Product* inventory[50];
    int productCount;
public:
    Warehouse() : productCount(0) {}

    ~Warehouse() {
        for (int i = 0; i < productCount; i++) {
            delete inventory[i];
        }
        cout << "Warehouse inventory cleared.\n";
    }

    void addProduct(int id, string name, int quantity) {
        if (productCount < 50) {
            inventory[productCount++] = new Product(id, name, quantity);
            cout << "Product '" << name << "' added.\n";
        } else {
            cout << "Inventory full! Cannot add more products.\n";
        }
    }

    void sortProductsByName() {

        for (int i = 0; i < productCount - 1; i++) {
            for (int j = 0; j < productCount - i - 1; j++) {
                if (inventory[j]->name > inventory[j + 1]->name) {
                    swap(inventory[j], inventory[j + 1]);
                }
            }
        }
        cout << "Products sorted alphabetically by name.\n";
    }

    void searchProductByID(int id) {
        for (int i = 0; i < productCount; i++) {
            if (inventory[i]->id == id) {
                cout << "Product found:\n";
                inventory[i]->displayDetails();
                return;
            }
        }
        cout << "Product with ID " << id << " not found.\n";
    }

    void displayInventory() {
        if (productCount == 0) {
            cout << "Inventory is empty.\n";
        } else {
            cout << "\nWarehouse Inventory:\n";
            for (int i = 0; i < productCount; i++) {
                inventory[i]->displayDetails();
            }
        }
    }
};

int main() {
    Warehouse warehouse;

    warehouse.addProduct(101, "Computer", 20);
    warehouse.addProduct(103, "Mobile", 5);
    warehouse.addProduct(102, "Mouse", 50);
    warehouse.addProduct(104, "Table", 10);

    warehouse.displayInventory();

    warehouse.sortProductsByName();
    warehouse.displayInventory();

    warehouse.searchProductByID(103);
    warehouse.searchProductByID(999);

    return 0;
}
