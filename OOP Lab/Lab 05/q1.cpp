#include <iostream>
using namespace std;

class Apartment {
private:
    int id;
    string address;
    string* owner;

public:
    Apartment(int _id, string _address, string _owner) {
        id = _id;
        address = _address;
        owner = new string(_owner);
    }

    Apartment(const Apartment& other) {
        id = other.id;
        address = other.address;
        owner = new string(*other.owner); // Deep copy
    }

    void display() const {
        cout << "Apartment ID: " << id << endl;
        cout << "Address: " << address << endl;
        cout << "Owner: " << *owner << endl;
        cout << endl;
    }

    ~Apartment() {
        delete owner;
    }
};

int main() {
    Apartment apt1(101, "Gulshan E Johar", "Huzaif");
    cout << "Original Apartment:" << endl;
    apt1.display();

    Apartment apt2 = apt1;
    cout << "Copied Apartment:" << endl;
    apt2.display();
    
    return 0;
}
