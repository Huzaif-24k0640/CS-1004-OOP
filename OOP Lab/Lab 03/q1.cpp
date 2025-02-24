#include <iostream>
using namespace std;

class Wallet {
private:
    string ownerName;
    int totalBalance;
    string transactionHistory[50];
    int transactionCount;

public:
    Wallet(string name, int balance = 0) : ownerName(name), totalBalance(balance), transactionCount(0) {
        cout << "Wallet created for " << ownerName << " with initial balance: Rs. " << totalBalance << endl;
    }

    void addMoney(int amount) {
        if (amount <= 0) {
            cout << "Invalid amount! Cannot add Rs. " << amount << endl;
            return;
        }
        totalBalance += amount;
        transactionHistory[transactionCount++] = "Added Rs. " + to_string(amount);
        cout << "Rs. " << amount << " added to wallet. Current balance: Rs. " << totalBalance << endl;
    }

    void spendMoney(int amount, string reason) {
        if (amount <= 0) {
            cout << "Invalid amount! Cannot spend Rs. " << amount << endl;
            return;
        }
        if (amount > totalBalance) {
            cout << "Insufficient balance! Cannot spend Rs. " << amount << endl;
            return;
        }
        totalBalance -= amount;
        transactionHistory[transactionCount++] = "Spent Rs. " + to_string(amount) + " on " + reason;
        cout << "Rs. " << amount << " spent on " << reason << ". Current balance: Rs. " << totalBalance << endl;

        // Low balance warning
        if (totalBalance < 500) {
            cout << "Low balance! Current balance is Rs. " << totalBalance << endl;
        }
    }

    void displayTransactionHistory() {
        cout << "\nTransaction History for " << ownerName << ":\n";
        if (transactionCount == 0) {
            cout << "No transactions recorded yet.\n";
        } else {
            for (int i = 0; i < transactionCount; i++) {
                cout << i + 1 << ". " << transactionHistory[i] << endl;
            }
        }
        cout << "Current Balance: Rs. " << totalBalance << endl;
    }
};

int main() {
    Wallet saadWallet("Saad", 2000);

    saadWallet.addMoney(1000);
    saadWallet.spendMoney(1200, "Dinner");
    saadWallet.spendMoney(500, "Groceries");
    saadWallet.spendMoney(2000, "New Phone");
    saadWallet.addMoney(300);
    saadWallet.spendMoney(600, "Fuel");

    saadWallet.displayTransactionHistory();

    return 0;
}

