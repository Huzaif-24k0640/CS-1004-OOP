#include <iostream>
using namespace std;

class Person {
protected:
    string name;
    int age;
    string contactNumber;
    string address;

public:
    Person(string n, int a, string c, string addr) : name(n), age(a), contactNumber(c), address(addr) {}
    virtual void displayInfo() {
        cout << "Name: " << name << "\nAge: " << age << "\nContact: " << contactNumber << "\nAddress: " << address << endl;
    }
    void updateInfo(string newName, int newAge, string newContact, string newAddress) {
        name = newName;
        age = newAge;
        contactNumber = newContact;
        address = newAddress;
    }
};

class Patient : public Person {
private:
    int patientID;
    string medicalHistory;
    string doctorAssigned;

public:
    Patient(string n, int a, string c, string addr, int pID, string mHist, string doc) :
        Person(n, a, c, addr), patientID(pID), medicalHistory(mHist), doctorAssigned(doc) {}
    void displayInfo() override {
        Person::displayInfo();
        cout << "Patient ID: " << patientID << "\nMedical History: " << medicalHistory << "\nDoctor Assigned: " << doctorAssigned << endl;
    }
};

class Doctor : public Person {
private:
    string specialization;
    double consultationFee;
    string patientsList[10];
    int patientCount;

public:
    Doctor(string n, int a, string c, string addr, string spec, double fee) :
        Person(n, a, c, addr), specialization(spec), consultationFee(fee), patientCount(0) {}
    void addPatient(string patientName) {
        if (patientCount < 10) {
            patientsList[patientCount++] = patientName;
        }
    }
    void displayInfo() override {
        Person::displayInfo();
        cout << "Specialization: " << specialization << "\nConsultation Fee: " << consultationFee << "\nPatients List: ";
        for (int i = 0; i < patientCount; i++) cout << patientsList[i] << ", ";
        cout << endl;
    }
};

class Nurse : public Person {
private:
    string assignedWard;
    string shiftTimings;

public:
    Nurse(string n, int a, string c, string addr, string ward, string shift) :
        Person(n, a, c, addr), assignedWard(ward), shiftTimings(shift) {}
    void displayInfo() override {
        Person::displayInfo();
        cout << "Assigned Ward: " << assignedWard << "\nShift Timings: " << shiftTimings << endl;
    }
};

class Administrator : public Person {
private:
    string department;
    double salary;

public:
    Administrator(string n, int a, string c, string addr, string dept, double sal) :
        Person(n, a, c, addr), department(dept), salary(sal) {}
    void updateInfo(string newDept, double newSalary) {
        department = newDept;
        salary = newSalary;
    }
    void displayInfo() override {
        Person::displayInfo();
        cout << "Department: " << department << "\nSalary: " << salary << endl;
    }
};

int main() {
    Patient p1("ABC", 30, "1234567890", "123 Main St", 1, "Diabetes", "Ali");
    Doctor d1("Ali", 45, "0987654321", "456 Elm St", "Cardiology", 200.0);
    d1.addPatient("ABC");
    Nurse n1("XYZ", 35, "1112223333", "789 Oak St", "ICU", "Night Shift");
    Administrator a1("Hamza", 50, "4445556666", "101 Pine St", "Finance", 5000.0);
    
    cout << "\n--- Patient Info ---\n";
    p1.displayInfo();
    
    cout << "\n--- Doctor Info ---\n";
    d1.displayInfo();
    
    cout << "\n--- Nurse Info ---\n";
    n1.displayInfo();
    
    cout << "\n--- Administrator Info ---\n";
    a1.displayInfo();
    
    return 0;
}
