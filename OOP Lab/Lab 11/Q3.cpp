#include <iostream>
#include <exception>

using namespace std;

class InvalidTemperatureException : public exception {
};

template <typename T>
T convertToFahrenheit(T celsius) {
    if (celsius < static_cast<T>(-273.15)) {
        throw InvalidTemperatureException();
    }
    return celsius * static_cast<T>(9.0 / 5.0) + static_cast<T>(32);
}

int main() {
    try {
        cout << "Attempting to convert -300C..." << endl;
        double result = convertToFahrenheit(-300.0);
        cout << "Fahrenheit: " << result << endl;
    }
    catch (const InvalidTemperatureException& e) {
        cout << "Caught InvalidTemperatureException" << endl;
        cout << "what(): " << e.what() << endl;
    }

    return 0;
}
