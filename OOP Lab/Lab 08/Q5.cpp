#include <iostream>

using namespace std;

class Matrix2x2; // Forward declaration

class MatrixHelper;

class Matrix2x2 {
private:
    int a, b, c, d; // Matrix elements arranged as:
                    // [a  b]
                    // [c  d]

public:
    Matrix2x2(int a = 0, int b = 0, int c = 0, int d = 0)
        : a(a), b(b), c(c), d(d) {}

    Matrix2x2 operator+(const Matrix2x2& other) const {
        return Matrix2x2(a + other.a, b + other.b, c + other.c, d + other.d);
    }

    Matrix2x2 operator-(const Matrix2x2& other) const {
        return Matrix2x2(a - other.a, b - other.b, c - other.c, d - other.d);
    }

    Matrix2x2 operator*(const Matrix2x2& other) const {
        int m1 = a * other.a + b * other.c;
        int m2 = a * other.b + b * other.d;
        int m3 = c * other.a + d * other.c;
        int m4 = c * other.b + d * other.d;
        return Matrix2x2(m1, m2, m3, m4);
    }

    friend int determinant(const Matrix2x2& m);

    friend class MatrixHelper;

    friend ostream& operator<<(ostream& out, const Matrix2x2& m);
};

int determinant(const Matrix2x2& m) {
    return m.a * m.d - m.b * m.c;
}

class MatrixHelper {
public:
    void updateElement(Matrix2x2& m, int row, int col, int value) {
        if (row == 0 && col == 0) m.a = value;
        else if (row == 0 && col == 1) m.b = value;
        else if (row == 1 && col == 0) m.c = value;
        else if (row == 1 && col == 1) m.d = value;
        else cout << "Invalid row or column index." << endl;
    }
};

ostream& operator<<(ostream& out, const Matrix2x2& m) {
    out << "[" << m.a << " " << m.b << "]" << endl;
    out << "[" << m.c << " " << m.d << "]";
    return out;
}

int main() {
    Matrix2x2 mat1(1, 2, 3, 4);
    Matrix2x2 mat2(5, 6, 7, 8);

    cout << "Matrix 1:" << endl << mat1 << endl;
    cout << "Matrix 2:" << endl << mat2 << endl;

    Matrix2x2 sum = mat1 + mat2;
    cout << "\nMatrix 1 + Matrix 2:" << endl << sum << endl;

    Matrix2x2 diff = mat1 - mat2;
    cout << "\nMatrix 1 - Matrix 2:" << endl << diff << endl;

    Matrix2x2 prod = mat1 * mat2;
    cout << "\nMatrix 1 * Matrix 2:" << endl << prod << endl;

    cout << "\nDeterminant of Matrix 1: " << determinant(mat1) << endl;
    cout << "Determinant of Matrix 2: " << determinant(mat2) << endl;

    MatrixHelper helper;
    cout << "\nUpdating element (0,1) of Matrix 1 to 9:" << endl;
    helper.updateElement(mat1, 0, 1, 9);
    cout << "Updated Matrix 1:" << endl << mat1 << endl;

    return 0;
}
