#include <iostream>
using namespace std;

class Patient {
public:
    string name;
    string id;

    Patient(string n, string i) : name (n), id (i) {}

    virtual void displayTreatment () = 0;

    virtual void calculateCost (float amount) = 0;

};

class InPatient : public Patient{
    public:

    InPatient (string n, string i) : Patient (n, i) {}

    void displayTreatment () {
	cout <<  "InPatient-----\n";
        cout << "Patient ID: " << id << "\nPatient Name: " << name << endl;
        cout << "Ongoing InPatient Treatment..." << endl;
    }

    void calculateCost (float amount) {
	cout <<  "Calculating Cost for InPatient-----\n";
        cout << "Total Cost InPatient: " << amount << "$\n";
    }

};

class OutPatient: public Patient{
    public:
    OutPatient(string n, string i) : Patient (n, i) {}

    void displayTreatment () {
	cout <<  "OutPatient-----\n";
        cout << "Patient ID: " << id << "\nPatient Name: " << name << endl;
        cout << "Ongoing OutPatient Treatment..." << endl;
    }

    void calculateCost (float amount) {
	cout <<  "Calculating Cost for OutPatient-----\n";
        cout << "Total Cost OutPatient: " << amount << "$\n";
    }

};

int main () {
    InPatient ip1("ABC", "01");
    OutPatient op1("XYZ", "02");

    ip1.displayTreatment ();
    ip1.calculateCost (1000.50);

    op1.displayTreatment ();
    op1.calculateCost (2000.50);

    return 0;
}
