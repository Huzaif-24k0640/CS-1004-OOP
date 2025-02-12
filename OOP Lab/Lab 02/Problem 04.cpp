/*
* Name: Huzaif Ali
* Class: BCS-2C
* Question: 04
 */

/*
* Create a program to manage a dynamic array of strings. The program should: 
* 1. Allow the user to input the number of strings. 
* 2. Dynamically allocate memory for the strings. 
* 3. Populate the array with user input. 
* 4. Sort the strings alphabetically and display them. 
* 5. Deallocate memory after use. 
*/

#include <iostream>
using namespace std;

void inputStrings(char** arr, int numStrings) {
    for (int i = 0; i < numStrings; ++i) {
        cout << "Enter string " << i + 1 << ": ";
        cin >> arr[i];
    }
}

void swapStrings(char*& str1, char*& str2) {
    char* temp = str1;
    str1 = str2;
    str2 = temp;
}

void sortStrings(char** arr, int numStrings) {
    for (int i = 0; i < numStrings - 1; ++i) {
        for (int j = 0; j < numStrings - i - 1; ++j) {
            int k = 0;
            while (arr[j][k] != '\0' && arr[j + 1][k] != '\0' && arr[j][k] == arr[j + 1][k]) {
                k++;
            }
            if (arr[j][k] > arr[j + 1][k]) {
                swapStrings(arr[j], arr[j + 1]);
            }
        }
    }
}

void displayStrings(char** arr, int numStrings) {
    cout << "\nSorted Strings:\n";
    for (int i = 0; i < numStrings; ++i) {
        cout << arr[i] << endl;
    }
}

int main() {
    int numStrings, maxLength;

    // 1. Number of Strings
    cout << "Enter the number of strings: ";
    cin >> numStrings;

    // 2. Allocation
    char** strings = new char*[numStrings];
    for (int i = 0; i < numStrings; ++i) {
        strings[i] = new char[100];
    }

    // 3. Input
    inputStrings(strings, numStrings);

    // 4. Sort
    sortStrings(strings, numStrings);

    // 5. Display
    displayStrings(strings, numStrings);

    // 6. Deallocation
    for (int i = 0; i < numStrings; ++i) {
        delete[] strings[i];
    }
    delete[] strings;

    return 0;
}
