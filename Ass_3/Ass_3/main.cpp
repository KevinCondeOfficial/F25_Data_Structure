/*
* Conde, Kevin
* Bank Management system; Assignment 3
* 10/25/25
*/

#include <iostream>
#include <string>
#include <cstdlib>   // for rand(), srand()
#include <ctime>     // for time()
using namespace std;

// Base class: BankAccount
class BankAccount {
protected:
    string accountHolderName; // name of the account holder
    int accountNumber;        // unique account number
    double balance;           // current balance

public:
    // Constructor
    BankAccount(string name, int number, double initialBalance)
    {
        accountHolderName = name;
        accountNumber = number;
        balance = initialBalance;
    }

    // Virtual function to deposit money
    virtual void deposit(double amount) {
        balance += amount;
        cout << "Congratulations " << accountHolderName
            << "! You have successfully deposited $" << amount
            << " in your account #" << accountNumber
            << ". Your current balance is $" << balance << endl;
    }

    // Virtual function to withdraw money
    virtual void withdraw(double amount) 
    {
        if (amount <= balance) {
            balance -= amount;
            cout << "Congratulations " << accountHolderName
                << "! You have successfully withdrawn $" << amount
                << " from your account #" << accountNumber
                << ". Your current balance is $" << balance << endl;
        }
        else {
            cout << "Error: Insufficient funds!" << endl;
        }
    }

    // Virtual function to display balance
    virtual void displayBalance() {
        cout << "Your current balance is $" << balance << endl;
    }

    // Getter for account number
    int getAccountNumber() {
        return accountNumber;
    }

    // Getter for name
    string getName() {
        return accountHolderName;
    }
};

// Derived class (example of polymorphism, could extend features later)
class SavingsAccount : public BankAccount {
public:
    SavingsAccount(string name, int number, double initialBalance)
        : BankAccount(name, number, initialBalance) {
    }

    // Could override deposit/withdraw with interest rules, etc.
};

// Utility function to generate random account number
int generateAccountNumber() {
    return rand() % 90000 + 10000; // random 5-digit number
}

int main() {
    srand(time(0)); // seed random number generator

    const int MAX_ACCOUNTS = 100;
    BankAccount* accounts[MAX_ACCOUNTS]; // array of pointers to accounts
    int accountCount = 0;

    int choice;
    do {
        cout << "\n*************** Welcome to Chase ***************\n";
        cout << "Please choose one of the following operations:\n";
        cout << "1 - Create a new bank account with an initial balance\n";
        cout << "2 - Deposit Money to an Account\n";
        cout << "3 - Withdraw Money from an Account\n";
        cout << "4 - Display Current Balance of an Account\n";
        cout << "5 - Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            double initialBalance;
            cout << "Enter your name: ";
            cin >> name;
            cout << "Enter your initial balance: ";
            cin >> initialBalance;

            int accNum = generateAccountNumber();
            accounts[accountCount++] = new SavingsAccount(name, accNum, initialBalance);

            cout << "Congratulations " << name
                << "! You have successfully opened your new bank account "
                << "with an initial balance of $" << initialBalance
                << ". Your account number is " << accNum << endl;

        }
        else if (choice == 2) {
            int accNum;
            cout << "Enter the account number: ";
            cin >> accNum;

            bool found = false;
            for (int i = 0; i < accountCount; i++) {
                if (accounts[i]->getAccountNumber() == accNum) {
                    double depositAmount;
                    cout << "Enter the amount that you would like to deposit: ";
                    cin >> depositAmount;
                    accounts[i]->deposit(depositAmount);
                    found = true;
                    break;
                }
            }
            if (!found) cout << "No account number exists!" << endl;

        }
        else if (choice == 3) {
            int accNum;
            cout << "Enter the account number: ";
            cin >> accNum;

            bool found = false;
            for (int i = 0; i < accountCount; i++) {
                if (accounts[i]->getAccountNumber() == accNum) {
                    double withdrawAmount;
                    cout << "Enter the amount that you would like to withdraw: ";
                    cin >> withdrawAmount;
                    accounts[i]->withdraw(withdrawAmount);
                    found = true;
                    break;
                }
            }
            if (!found) cout << "No account number exists!" << endl;

        }
        else if (choice == 4) {
            int accNum;
            cout << "Enter the account number: ";
            cin >> accNum;

            bool found = false;
            for (int i = 0; i < accountCount; i++) {
                if (accounts[i]->getAccountNumber() == accNum) {
                    accounts[i]->displayBalance();
                    found = true;
                    break;
                }
            }
            if (!found) cout << "No account number exists!" << endl;
        }

    } while (choice != 5);

    cout << "Thank you for using Chase Bank System!" << endl;

    return 0;
}