#include <iostream>
#include <exception>
#include <sstream>

using namespace std;

class DimensionMismatchException : public exception {
private:
    string message;
public:
    DimensionMismatchException(int r1, int c1, int r2, int c2) {
        stringstream ss;
        ss << "DimensionMismatchException (" << r1 << "x" << c1 << " != " << r2 << "x" << c2 << ")!";
        message = ss.str();
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

template <typename T, int ROWS, int COLS>
class Matrix {
private:
    T data[ROWS][COLS];
public:
    Matrix() {
        for (int i = 0; i < ROWS; ++i)
            for (int j = 0; j < COLS; ++j)
                data[i][j] = 0;
    }

    void set(int r, int c, T value) {
        data[r][c] = value;
    }

    T get(int r, int c) const {
        return data[r][c];
    }

    void print() const {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    template<int R2, int C2>
    Matrix<T, ROWS, COLS> add(const Matrix<T, R2, C2>& other) const {
        if (ROWS != R2 || COLS != C2) {
            throw DimensionMismatchException(ROWS, COLS, R2, C2);
        }

        Matrix<T, ROWS, COLS> result;
        for (int i = 0; i < ROWS; ++i)
            for (int j = 0; j < COLS; ++j)
                result.set(i, j, data[i][j] + other.get(i, j));
        return result;
    }
};

int main() {
    try {
        Matrix<int, 2, 2> A;
        Matrix<int, 3, 3> B;

        A.set(0, 0, 1); A.set(0, 1, 2);
        A.set(1, 0, 3); A.set(1, 1, 4);

        B.set(0, 0, 5); B.set(0, 1, 6); B.set(0, 2, 7);
        B.set(1, 0, 8); B.set(1, 1, 9); B.set(1, 2, 10);
        B.set(2, 0, 11); B.set(2, 1, 12); B.set(2, 2, 13);

        cout << "Matrix A:\n"; A.print();
        cout << "Matrix B:\n"; B.print();

        auto C = A.add(B);
        cout << "Matrix C (A + B):\n"; C.print();
    }
    catch (const DimensionMismatchException& e) {
        cout << e.what() << endl;
    }

    return 0;
}
