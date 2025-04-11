#include <iostream>
using namespace std;

class Account; 
class Manager;

class Account {
private:
    int accountNumber;
    double balance;

public:
    Account(int accNo, double bal) : accountNumber(accNo), balance(bal) {}

    friend class Manager;
    friend void transferFunds(Account& from, Account& to, double amount);
};

class Manager {
public:
    void displayAccount(const Account& acc) const {
        cout << "Account Number: " << acc.accountNumber 
             << ", Balance: $" << acc.balance << endl;
    }

    void deposit(Account& acc, double amount) const {
        if (amount > 0) {
            acc.balance += amount;
            cout << "Deposited $" << amount << " to account " 
                 << acc.accountNumber << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    void withdraw(Account& acc, double amount) const {
        if (amount > 0 && amount <= acc.balance) {
            acc.balance -= amount;
            cout << "Withdrew $" << amount << " from account " 
                 << acc.accountNumber << endl;
        } else {
            cout << "Invalid withdrawal attempt." << endl;
        }
    }
};

void transferFunds(Account& from, Account& to, double amount) {
    if (amount > 0 && from.balance >= amount) {
        from.balance -= amount;
        to.balance += amount;
        cout << "Transferred $" << amount << " from account " 
             << from.accountNumber << " to account " << to.accountNumber << endl;
    } else {
        cout << "Transfer failed: insufficient funds or invalid amount." << endl;
    }
}

int main() {
    Account acc1(1001, 500.0);
    Account acc2(1002, 300.0);
    Manager mgr;

    cout << "Initial Account Status:" << endl;
    mgr.displayAccount(acc1);
    mgr.displayAccount(acc2);

    cout << "\nDepositing $200 to Account 1:" << endl;
    mgr.deposit(acc1, 200.0);

    cout << "\nWithdrawing $100 from Account 2:" << endl;
    mgr.withdraw(acc2, 100.0);

    cout << "\nTransferring $250 from Account 1 to Account 2:" << endl;
    transferFunds(acc1, acc2, 250.0);

    cout << "\nFinal Account Status:" << endl;
    mgr.displayAccount(acc1);
    mgr.displayAccount(acc2);

    return 0;
}
