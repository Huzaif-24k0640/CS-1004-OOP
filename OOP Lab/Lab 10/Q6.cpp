#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct InventoryItem {
    	int itemID;
    	char itemName[20];
};

int main() {

    	InventoryItem itemOut;
    	itemOut.itemID = 101;
    	strncpy(itemOut.itemName, "Screwdriver", sizeof(itemOut.itemName));
    	itemOut.itemName[sizeof(itemOut.itemName) - 1] = '\0';

    	ofstream outFile("inventory.dat", ios::binary);
    	if (!outFile) {
        	cerr << "Could not open file for writing." << endl;
        	return 1;
    	}
    	outFile.write(reinterpret_cast<char*>(&itemOut), sizeof(InventoryItem));
    	outFile.close();

    	InventoryItem itemIn;
    	ifstream inFile("inventory.dat", ios::binary);
    	if (!inFile) {
        	cerr << "Could not open file for reading." << endl;
        	return 1;
    	}
    	inFile.read(reinterpret_cast<char*>(&itemIn), sizeof(InventoryItem));
    	inFile.close();

    	cout << "Item ID: " << itemIn.itemID << endl;
    	cout << "Item Name: " << itemIn.itemName << endl;

    	return 0;
}
