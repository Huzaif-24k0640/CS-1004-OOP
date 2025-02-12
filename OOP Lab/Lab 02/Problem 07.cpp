/*
* Name: Huzaif Ali
* Class: BCS-2C
* Question: 07
*/

/*
* Write a program to perform matrix multiplication using pointers. The program should: 
* 1. Allow the user to input the dimensions of two matrices. 
* 2. Dynamically allocate memory for the matrices. 
* 3. Perform matrix multiplication. 
* 4. Display the result and deallocate memory. 
*/

#include <iostream>
using namespace std;

int** allocateMatrix(int rows, int cols) {
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }
    return matrix;
}

void inputMatrix(int** matrix, int rows, int cols, const string& name) {
    cout << "Enter elements of " << name << " matrix (" << rows << "x" << cols << "):\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> matrix[i][j];
        }
    }
}

int** multiplyMatrices(int** mat1, int r1, int c1, int** mat2, int r2, int c2) {

    int** result = allocateMatrix(r1, c2);

    for (int i = 0; i < r1; ++i) {
        for (int j = 0; j < c2; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < c1; ++k) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return result;
}

// Function to display a matrix
void displayMatrix(int** matrix, int rows, int cols) {
    cout << "Resultant Matrix (" << rows << "x" << cols << "):\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to deallocate memory of a matrix
void deallocateMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    int r1, c1, r2, c2;

    // 1. Dimensions
    cout << "Enter rows and columns of first matrix: ";
    cin >> r1 >> c1;
    cout << "Enter rows and columns of second matrix: ";
    cin >> r2 >> c2;

    if (c1 != r2) {
        cout << "Matrix multiplication not possible (columns of first must equal rows of second).\n";
        return 1;
    }

    // 2. Allocation
    int** mat1 = allocateMatrix(r1, c1);
    int** mat2 = allocateMatrix(r2, c2);

    // 3. Input
    inputMatrix(mat1, r1, c1, "first");
    inputMatrix(mat2, r2, c2, "second");

    // 4. Multiplication
    int** result = multiplyMatrices(mat1, r1, c1, mat2, r2, c2);

    // 5. Display
    displayMatrix(result, r1, c2);

    // 6. Deallocation
    deallocateMatrix(mat1, r1);
    deallocateMatrix(mat2, r2);
    deallocateMatrix(result, r1);

    return 0;
}
