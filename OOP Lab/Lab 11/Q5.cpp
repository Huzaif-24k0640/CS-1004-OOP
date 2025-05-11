#include <iostream>
#include <exception>

using namespace std;

class NegativeStockException : public exception {
};

class OverCapacityException : public exception {
};

template <typename T>
class InventoryItem {
private:
    T stock;
    T maxStock;

public:
    InventoryItem(T maxLimit) : stock(0), maxStock(maxLimit) {}

    void setStock(T value) {
        if (value < 0) {
            throw NegativeStockException();
        }
        if (value > maxStock) {
            throw OverCapacityException();
        }
        stock = value;
    }

    T getStock() const {
        return stock;
    }
};

int main() {
    InventoryItem<int> item(100);

    try {
        cout << "Attempting to set stock to -5..." << endl;
        item.setStock(-5);
    }
    catch (const NegativeStockException& e) {
        cout << "Caught NegativeStockException" << endl;
        cout << "what(): " << e.what() << endl;
    }

    try {
        cout << "Attempting to set stock to 120 (max 100)..." << endl;
        item.setStock(120);
    }
    catch (const OverCapacityException& e) {
        cout << "Caught OverCapacityException" << endl;
        cout << "what(): " << e.what() << endl;
    }

    return 0;
}
