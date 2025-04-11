#include <iostream>
#include <cmath>

using namespace std;

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(const Complex& other) const {
        double newReal = real * other.real - imag * other.imag;
        double newImag = real * other.imag + imag * other.real;
        return Complex(newReal, newImag);
    }

    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        double newReal = (real * other.real + imag * other.imag) / denominator;
        double newImag = (imag * other.real - real * other.imag) / denominator;
        return Complex(newReal, newImag);
    }

    friend ostream& operator<<(ostream& out, const Complex& c) {
        out << "(" << c.real << " " << (c.imag >= 0 ? "+ " : "- ") 
            << abs(c.imag) << "i)";
        return out;
    }

    friend double magnitude(const Complex& c);
};

double magnitude(const Complex& c) {
    return sqrt(c.real * c.real + c.imag * c.imag);
}

int main() {
    Complex c1(3, 4);
    Complex c2(1, -2);

    cout << "c1 = " << c1 << endl;
    cout << "c2 = " << c2 << endl;

    Complex sum = c1 + c2;
    cout << "c1 + c2 = " << sum << endl;

    Complex diff = c1 - c2;
    cout << "c1 - c2 = " << diff << endl;

    Complex prod = c1 * c2;
    cout << "c1 * c2 = " << prod << endl;

    Complex quot = c1 / c2;
    cout << "c1 / c2 = " << quot << endl;

    cout << "Magnitude of c1 = " << magnitude(c1) << endl;
    cout << "Magnitude of c2 = " << magnitude(c2) << endl;

    return 0;
}
