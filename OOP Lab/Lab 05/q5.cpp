#include <iostream>
using namespace std;

class Doctor {
private:
    string name;
    string specialization;
    int experience;
public:
    Doctor(string n, string spec, int exp) : name(n), specialization(spec), experience(exp) {}

    void displayDetails() {
        cout << "Doctor Name: " << name << ", Specialization: " << specialization
             << ", Experience: " << experience << " years\n";
    }
};

class Hospital {
private:
    string name;
    Doctor* doctors[10];
    int doctorCount;
public:
    Hospital(string n) : name(n), doctorCount(0) {}

    void addDoctor(Doctor* doc) {
        if (doctorCount < 10) {
            doctors[doctorCount++] = doc;
            cout << "Doctor added to " << name << endl;
        } else {
            cout << "Hospital is full!\n";
        }
    }

    void displayDetails() {
        cout << "Hospital Name: " << name << "\nDoctors Working Here:\n";
        if (doctorCount == 0) {
            cout << "No doctors assigned yet.\n";
        } else {
            for (int i = 0; i < doctorCount; i++) {
                doctors[i]->displayDetails();
            }
        }
    }
};

int main() {

    Doctor d1("Huzaif", "Cardiology", 10);
    Doctor d2("Hardeep", "Neurology", 7);
    Doctor d3("Kazim", "Orthopedics", 5);

    Hospital h("Karachi Hospital");

    h.addDoctor(&d1);
    h.addDoctor(&d2);

    h.displayDetails();

    h.addDoctor(&d3);
    h.displayDetails();

    return 0;
}
