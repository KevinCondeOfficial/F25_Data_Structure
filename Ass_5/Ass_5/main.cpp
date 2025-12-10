/*
* Conde, Kevin
* Assignment 5: Inventory System
* 11/10/25
*/

#include <iostream>
#include <fstream>   // for file I/O
#include <string>
#include <iomanip>   // for formatted output
using namespace std;

// Struct to represent an inventory item
struct Item {
    string name;
    string category;
    int quantity;
    double price;
};

// Struct to represent a transaction
struct Transaction {
    string type;      // "BUY" or "RETURN"
    string itemName;
    int quantity;
    double unitPrice;
};

// Function to load inventory from file into array
int loadInventory(Item items[]) {
    ifstream inFile("inventory.txt");
    int count = 0;
    if (inFile.is_open()) {
        while (inFile >> ws && !inFile.eof()) {
            getline(inFile, items[count].name, ',');
            getline(inFile, items[count].category, ',');
            inFile >> items[count].quantity;
            inFile.ignore(); // skip comma
            inFile >> items[count].price;
            inFile.ignore(); // skip newline
            count++;
        }
        inFile.close();
    }
    return count; // return number of items loaded
}

// Function to save inventory back to file
void saveInventory(Item items[], int count) {
    ofstream outFile("inventory.txt");
    for (int i = 0; i < count; i++) {
        outFile << items[i].name << ","
            << items[i].category << ","
            << items[i].quantity << ","
            << items[i].price << endl;
    }
    outFile.close();
}

// Function to record a transaction in transactions.txt
void saveTransaction(Transaction t) {
    ofstream outFile("transactions.txt", ios::app); // append mode
    outFile << t.type << ","
        << t.itemName << ","
        << t.quantity << ","
        << t.unitPrice << endl;
    outFile.close();
}

// Function to display inventory
void displayInventory(Item items[], int count) {
    cout << "\nINVENTORY\n";
    cout << left << setw(15) << "Item Name"
        << setw(15) << "Category"
        << setw(10) << "Qty"
        << setw(10) << "Price" << endl;
    for (int i = 0; i < count; i++) {
        cout << left << setw(15) << items[i].name
            << setw(15) << items[i].category
            << setw(10) << items[i].quantity
            << "$" << fixed << setprecision(2) << items[i].price << endl;
    }
}

// Function to add new item to inventory
void addItem(Item items[], int& count) {
    cout << "Enter item name: ";
    cin >> ws;
    getline(cin, items[count].name);
    cout << "Enter category: ";
    getline(cin, items[count].category);
    cout << "Enter quantity: ";
    cin >> items[count].quantity;
    cout << "Enter price: ";
    cin >> items[count].price;
    count++;
    cout << "Item added!\n";
}

// Function to buy an item
void buyItem(Item items[], int count) {
    string itemName;
    int qty;
    cout << "Enter item to buy: ";
    cin >> ws;
    getline(cin, itemName);
    cout << "Quantity: ";
    cin >> qty;

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (items[i].name == itemName) {
            found = true;
            if (qty <= items[i].quantity) {
                items[i].quantity -= qty;
                double total = qty * items[i].price;
                cout << "Successfully purchased " << qty << " x " << itemName
                    << " for $" << fixed << setprecision(2) << total << endl;

                // Record transaction
                Transaction t = { "BUY", itemName, qty, items[i].price };
                saveTransaction(t);
            }
            else {
                cout << "Not enough stock available!\n";
            }
            break;
        }
    }
    if (!found) cout << "Item not found!\n";
}

// Function to return an item
void returnItem(Item items[], int count) {
    string itemName;
    int qty;
    cout << "Enter item to return: ";
    cin >> ws;
    getline(cin, itemName);
    cout << "Quantity: ";
    cin >> qty;

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (items[i].name == itemName) {
            found = true;
            items[i].quantity += qty;
            cout << qty << " x " << itemName << " returned and added back to inventory.\n";

            // Record transaction
            Transaction t = { "RETURN", itemName, qty, items[i].price };
            saveTransaction(t);
            break;
        }
    }
    if (!found) cout << "Item not found!\n";
}

// Function to show profit report
void showProfitReport() {
    ifstream inFile("transactions.txt");
    double revenue = 0, refunds = 0;
    string type, itemName;
    int qty;
    double unitPrice;

    while (inFile >> ws && !inFile.eof()) {
        getline(inFile, type, ',');
        getline(inFile, itemName, ',');
        inFile >> qty;
        inFile.ignore(); // skip comma
        inFile >> unitPrice;
        inFile.ignore(); // skip newline

        if (type == "BUY") {
            revenue += qty * unitPrice;
        }
        else if (type == "RETURN") {
            refunds += qty * unitPrice;
        }
    }
    inFile.close();

    cout << "\nPROFIT REPORT\n";
    cout << "Total Revenue: $" << fixed << setprecision(2) << revenue << endl;
    cout << "Total Refunds: $" << fixed << setprecision(2) << refunds << endl;
    cout << "Net Profit: $" << fixed << setprecision(2) << (revenue - refunds) << endl;
}

int main() {
    Item items[100]; // inventory array
    int count = loadInventory(items); // load existing inventory from file
    int choice;

    cout << "******** Welcome to Store Inventory & Profit Tracker ********\n";

    do {
        cout << "\nPlease choose one of the following operations:\n";
        cout << "1 - Add New Item to Inventory\n";
        cout << "2 - Display Inventory\n";
        cout << "3 - Buy Item\n";
        cout << "4 - Return Item\n";
        cout << "5 - View Profit Report\n";
        cout << "6 - Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addItem(items, count); break;
        case 2: displayInventory(items, count); break;
        case 3: buyItem(items, count); break;
        case 4: returnItem(items, count); break;
        case 5: showProfitReport(); break;
        case 6:
            saveInventory(items, count);
            cout << "Inventory and transactions saved. Goodbye!\n";
            break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}