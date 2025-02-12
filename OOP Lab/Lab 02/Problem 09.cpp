/*
* Name: Huzaif Ali
* Class: BCS-2C
* Question: 09
*/

/*
* Create a program to manage a dynamic array of pointers to integers. The program should: 
* 1. Allow the user to input the size of the array. 
* 2. Dynamically allocate memory for the array and its elements. 
* 3. Populate the array with user input. 
* 4. Display the array and deallocate memory. 
* 5. Display the total value of the inventory (sum of quantity price).
* 6. Deallocate memory after use. 
*/

#include <iostream>
using namespace std;

struct InventoryItem {
    int quantity;
    float price;
};

int main() {
    int size;

    // 1. Size
    cout << "Enter the number of inventory items: ";
    cin >> size;

    // 2. Allocation
    InventoryItem** inventory = new InventoryItem*[size];

    cout << "Enter details for " << size << " inventory items (quantity and price):\n";
    for (int i = 0; i < size; i++) {
        inventory[i] = new InventoryItem;
        cout << "Item " << i + 1 << " - Quantity: ";
        cin >> inventory[i]->quantity;
        cout << "Item " << i + 1 << " - Price: ";
        cin >> inventory[i]->price;
    }

    // 4. Display items
    float totalValue = 0;
    cout << "\nInventory Items:\n";
    for (int i = 0; i < size; ++i) {
        float itemValue = inventory[i]->quantity * inventory[i]->price;
        cout << "Item " << i + 1 << " - Quantity: " << inventory[i]->quantity << ", Price: " << inventory[i]->price << ", Total: " << itemValue << endl;
        totalValue += itemValue;
    }

    // 5. Display total value
    cout << "\nTotal value of the inventory: " << totalValue << endl;

    // 6. Deallocation
    for (int i = 0; i < size; ++i) {
        delete inventory[i];
    }
    delete[] inventory;

    return 0;
}
