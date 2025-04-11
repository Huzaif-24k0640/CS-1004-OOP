#include <iostream>
using namespace std;

class Vector2D {
private:
    double x;
    double y;

public:
    Vector2D(double xVal = 0.0, double yVal = 0.0) : x(xVal), y(yVal) {}

    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    Vector2D operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    friend double dotProduct(const Vector2D& v1, const Vector2D& v2);

    friend ostream& operator<<(ostream& out, const Vector2D& v);
};

double dotProduct(const Vector2D& v1, const Vector2D& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

ostream& operator<<(ostream& out, const Vector2D& v) {
    out << "(" << v.x << ", " << v.y << ")";
    return out;
}

int main() {
    Vector2D v1(3.0, 4.0);
    Vector2D v2(1.0, 2.0);

    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;

    Vector2D sum = v1 + v2;
    cout << "v1 + v2 = " << sum << endl;

    Vector2D diff = v1 - v2;
    cout << "v1 - v2 = " << diff << endl;

    Vector2D scaled = v1 * 2.5;
    cout << "v1 * 2.5 = " << scaled << endl;

    double dot = dotProduct(v1, v2);
    cout << "Dot product of v1 and v2 = " << dot << endl;

    return 0;
}
