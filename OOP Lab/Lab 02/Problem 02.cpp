/*
* Name: Huzaif Ali
* Class: BCS-2C
* Question: 02
 */

/*
* Write a program to perform matrix operations (addition and subtraction) using pointer-to-pointer (double pointer) for dynamic memory allocation. The program 
* should: 
* 1. Allow the user to input the dimensions of two matrices. 
* 2. Dynamically allocate memory for the matrices. 
* 3. Perform addition and subtraction. 
* 4. Display the results and deallocate memory. 
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

void deallocateMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void inputMatrix(int** matrix, int rows, int cols, const string& name) {
    cout << "Enter elements for " << name << " (" << rows << "x" << cols << "):\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << "Element [" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
    }
}

void displayMatrix(int** matrix, int rows, int cols, const string& name) {
    cout << "\n" << name << ":\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int** addMatrices(int** A, int** B, int rows, int cols) {
    int** result = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

int** subtractMatrices(int** A, int** B, int rows, int cols) {
    int** result = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

int main() {
    int rows, cols;

    // 1. Dimensions
    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> cols;

    // 2. Allocation
    int** matrixA = allocateMatrix(rows, cols);
    int** matrixB = allocateMatrix(rows, cols);

    // 3. Inputs
    inputMatrix(matrixA, rows, cols, "Matrix A");
    inputMatrix(matrixB, rows, cols, "Matrix B");

    // 4. Operations
    int** sumMatrix = addMatrices(matrixA, matrixB, rows, cols);
    int** diffMatrix = subtractMatrices(matrixA, matrixB, rows, cols);

    // 5. Display
    displayMatrix(matrixA, rows, cols, "Matrix A");
    displayMatrix(matrixB, rows, cols, "Matrix B");
    displayMatrix(sumMatrix, rows, cols, "Sum (A + B)");
    displayMatrix(diffMatrix, rows, cols, "Difference (A - B)");

    // 6. Deallocation
    deallocateMatrix(matrixA, rows);
    deallocateMatrix(matrixB, rows);
    deallocateMatrix(sumMatrix, rows);
    deallocateMatrix(diffMatrix, rows);

    return 0;
}
