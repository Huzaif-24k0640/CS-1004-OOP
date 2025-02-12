/*
* Name: Huzaif Ali
* Class: BCS-2C
* Question: 05
*/

/*
* Write a program to demonstrate the relationship between pointers and arrays. The program should: 
* 1. Allow the user to input an array of integers. 
* 2. Use pointer arithmetic to traverse and display the array. 
* 3. Find the sum of the array elements using pointers. 
* 4. Display the results and deallocate memory. 
*/

#include <iostream>

using namespace std;

int main() {
    int size;

    // 1. Number
    cout << "Enter the number of elements: ";
    cin >> size;

    // 2. Allocation
    int* arr = new int[size];

    // 3. Input
    cout << "Enter " << size << " elements:\n";
    for (int i = 0; i < size; ++i) {
        cin >> *(arr + i);
    }

    // 4. Display Inputs
    cout << "Array elements: ";
    for (int i = 0; i < size; ++i) {
        cout << *(arr + i) << " ";
    }
    cout << endl;

    // 5. Sum
    int sum = 0;
    for (int* ptr = arr; ptr < arr + size; ++ptr) {
        sum += *ptr;
    }

    // 6. Display Sum
    cout << "Sum of array elements: " << sum << endl;

    // 7. Deallocation
    delete[] arr;

    return 0;
}
