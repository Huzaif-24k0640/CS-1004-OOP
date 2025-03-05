#include <iostream>
using namespace std;

class Account {
public:
    int accountNumber;
    float balance;
    
    Account (int a, int b): accountNumber (a), balance (b) {} 
    
    void displayDetailsAccount () {
        cout << "Account number: " << accountNumber << "\nBalance: " << "$" << balance << endl;
    }
    
};

class SavingsAccount: public Account {
public:
    float interestRate;
    
    SavingsAccount (int a, float b, float i): Account (a, b), interestRate (i) {}
    
    void displayDetailsSavingsAccount () {
        cout << "\nSavings account details" << endl;
        displayDetailsAccount ();
        cout << "Interest rate: " << interestRate << "%" << endl;
    }
};

class CheckingAccount: public Account {
 public:
    float overdraftLimit;
    
    CheckingAccount (int a, float b, float ol): Account (a, b), overdraftLimit (ol) {}
    
    void displayDetailsCheckingAccount () {
        cout << "\nChecking account details" << endl;
        displayDetailsAccount ();
        cout << "Overdraft limit: " << overdraftLimit << endl;
    }
    
};

int main () {
    SavingsAccount sa1 (100, 500.00, 7.5);
    sa1.displayDetailsSavingsAccount ();
    
    CheckingAccount ca1 (101, 1000.00, 1.25);
    ca1.displayDetailsCheckingAccount ();

    return 0;
}
