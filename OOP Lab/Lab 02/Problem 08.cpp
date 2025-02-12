/*
* Name: Huzaif Ali
* Class: BCS-2C
* Question: 08
*/

/*
* Create a program to manage a dynamic array of pointers to integers. The program should: 
* 1. Allow the user to input the size of the array. 
* 2. Dynamically allocate memory for the array and its elements. 
* 3. Populate the array with user input. 
* 4. Display the array and deallocate memory. 
*/

#include <iostream>
using namespace std;

int main() {
    int size;

    // 1. Size
    cout << "Enter the size of the array: ";
    cin >> size;

    // 2. Allocation
    int** arr = new int*[size];

    cout << "Enter " << size << " integers:\n";
    for (int i = 0; i < size; i++) {
        arr[i] = new int;
        cin >> *(arr[i]);
    }

    // 3. Display
    cout << "Array elements: ";
    for (int i = 0; i < size; i++) {
        cout << *(arr[i]) << " ";
    }
    cout << endl;

    // 4. Deallocation
    for (int i = 0; i < size; ++i) {
        delete arr[i];
    }
    delete[] arr;

    return 0;
}
