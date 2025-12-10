/*
* Conde, Kevin
* Assignment 6: Delivery tracker
* 11/11/25
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// Template struct for Package
// T1 = ID type (string or int)
// T2 = Fee type (float or double)
template <typename T1, typename T2>
struct Package {
    T1 id;              // package ID
    string name;        // recipient name
    string type;        // delivery type (Standard/Express/Fragile)
    int etaHours;       // estimated delivery time in hours
    T2 fee;             // delivery fee
    string status;      // "Pending" or "Delivered"
};

// Load packages from file into array
template <typename T1, typename T2>
int loadPackages(Package<T1, T2> packages[]) {
    ifstream inFile("packages.txt");
    int count = 0;
    if (inFile.is_open()) {
        while (inFile >> ws && !inFile.eof()) {
            inFile >> packages[count].id;
            inFile.ignore(); // skip comma
            getline(inFile, packages[count].name, ',');
            getline(inFile, packages[count].type, ',');
            inFile >> packages[count].etaHours;
            inFile.ignore(); // skip comma
            inFile >> packages[count].fee;
            inFile.ignore(); // skip comma
            getline(inFile, packages[count].status);
            count++;
        }
        inFile.close();
    }
    return count;
}

// Save packages back to file
template <typename T1, typename T2>
void savePackages(Package<T1, T2> packages[], int count) {
    ofstream outFile("packages.txt");
    for (int i = 0; i < count; i++) {
        outFile << packages[i].id << ","
            << packages[i].name << ","
            << packages[i].type << ","
            << packages[i].etaHours << ","
            << fixed << setprecision(2) << packages[i].fee << ","
            << packages[i].status << endl;
    }
    outFile.close();
}

// Add new package
template <typename T1, typename T2>
void addPackage(Package<T1, T2> packages[], int& count) {
    cout << "Enter package ID: ";
    cin >> packages[count].id;
    cout << "Enter recipient name: ";
    cin >> ws;
    getline(cin, packages[count].name);
    cout << "Enter delivery type (Standard/Express/Fragile): ";
    getline(cin, packages[count].type);
    cout << "Enter delivery ETA (in hours): ";
    cin >> packages[count].etaHours;
    cout << "Enter delivery fee: ";
    cin >> packages[count].fee;
    packages[count].status = "Pending"; // default status
    count++;
    cout << "Package added!\n";
}

// Display all packages
template <typename T1, typename T2>
void displayPackages(Package<T1, T2> packages[], int count) {
    cout << "\nPACKAGES\n";
    cout << left << setw(10) << "ID"
        << setw(15) << "Name"
        << setw(12) << "Type"
        << setw(8) << "ETA"
        << setw(10) << "Fee"
        << setw(12) << "Status" << endl;

    for (int i = 0; i < count; i++) {
        cout << left << setw(10) << packages[i].id
            << setw(15) << packages[i].name
            << setw(12) << packages[i].type
            << setw(8) << packages[i].etaHours
            << "$" << setw(9) << fixed << setprecision(2) << packages[i].fee
            << setw(12) << packages[i].status << endl;
    }
}

// Mark package as delivered
template <typename T1, typename T2>
void markDelivered(Package<T1, T2> packages[], int count) {
    T1 id;
    cout << "Enter package ID to mark as delivered: ";
    cin >> id;

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (packages[i].id == id) {
            packages[i].status = "Delivered";
            cout << "Package " << id << " marked as Delivered.\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "Package not found!\n";
}

// Delivery report
template <typename T1, typename T2>
void deliveryReport(Package<T1, T2> packages[], int count) {
    int delivered = 0, pending = 0;
    double revenue = 0;

    for (int i = 0; i < count; i++) {
        if (packages[i].status == "Delivered") {
            delivered++;
            revenue += packages[i].fee;
        }
        else {
            pending++;
        }
    }

    cout << "\nDELIVERY REPORT\n";
    cout << "Total Packages: " << count << endl;
    cout << "Delivered: " << delivered << endl;
    cout << "Pending: " << pending << endl;
    cout << "Total Revenue: $" << fixed << setprecision(2) << revenue << endl;
}

int main() {
    Package<int, double> packages[100]; // using int for ID, double for fee
    int count = loadPackages(packages); // load existing packages from file
    int choice;

    cout << "******** Welcome to Package Delivery Tracker ********\n";

    do {
        cout << "\nPlease choose one of the following operations:\n";
        cout << "1 - Add New Package\n";
        cout << "2 - Display All Packages\n";
        cout << "3 - Mark Package as Delivered\n";
        cout << "4 - View Delivery Report\n";
        cout << "5 - Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addPackage(packages, count); break;
        case 2: displayPackages(packages, count); break;
        case 3: markDelivered(packages, count); break;
        case 4: deliveryReport(packages, count); break;
        case 5:
            savePackages(packages, count);
            cout << "Data saved to packages.txt. Goodbye!\n";
            break;
        default: cout << "Invalid option. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}