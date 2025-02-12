/*
* Name: Huzaif Ali
* Class: BCS-2C
* Question: 10
*/

/*
* Write a program to manage a 3D array using dynamic memory allocation. The program should: 
* 1. Allow the user to input the dimensions of the 3D array. 
* 2. Dynamically allocate memory for the array. 
* 3. Populate the array with user input. 
* 4. Display the array and deallocate memory.  
*/

#include <iostream>
using namespace std;

int main() {
    int x, y, z;

    // 1. Dimensions
    cout << "Enter the dimensions for the 3D array (x, y, z): ";
    cin >> x >> y >> z;

    // 2. Allocation for 3D
    int*** arr = new int**[x];
    for (int i = 0; i < x; ++i) {
        arr[i] = new int*[y];
        for (int j = 0; j < y; ++j) {
            arr[i][j] = new int[z];
        }
    }

    // 3. Inputs
    cout << "Enter elements for the 3D array:\n";
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                cout << "Enter element for [" << i << "][" << j << "][" << k << "]: ";
                cin >> arr[i][j][k];
            }
        }
    }

    // 4. Display
    cout << "\nDisplaying the 3D array:\n";
    for (int i = 0; i < x; ++i) {
        cout << "Layer " << i + 1 << ":\n";
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                cout << arr[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // 5. Deallocation of 3D
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            delete[] arr[i][j];
        }
        delete[] arr[i];
    }
    delete[] arr;

    return 0;
}
