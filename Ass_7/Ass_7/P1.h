#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// Struct to represent an order
struct Order {
    string id;       // Order ID
    string name;     // Customer name
    string item;     // Menu item
    int quantity;    // Quantity ordered
    float price;     // Price per item
    string status;   // "Pending" or "Served"
};

// Load orders from file into vector
void loadOrders(vector<Order>& orders) {
    ifstream inFile("orders.txt");
    if (inFile.is_open()) {
        while (inFile >> ws && !inFile.eof()) {
            Order o;
            getline(inFile, o.id, ',');
            getline(inFile, o.name, ',');
            getline(inFile, o.item, ',');
            inFile >> o.quantity;
            inFile.ignore(); // skip comma
            inFile >> o.price;
            inFile.ignore(); // skip comma
            float total;
            inFile >> total; // total not stored, recalculated later
            inFile.ignore(); // skip comma
            getline(inFile, o.status);
            orders.push_back(o);
        }
        inFile.close();
    }
}

// Save orders to file
void saveOrders(const vector<Order>& orders) {
    ofstream outFile("orders.txt");
    for (auto& o : orders) {
        float total = o.quantity * o.price;
        outFile << o.id << "," << o.name << "," << o.item << ","
            << o.quantity << "," << fixed << setprecision(2) << o.price << ","
            << total << "," << o.status << endl;
    }
    outFile.close();
}

// Place new order
void placeOrder(vector<Order>& orders) {
    Order o;
    cout << "Enter Order ID: ";
    cin >> o.id;
    cout << "Enter customer name: ";
    cin >> ws;
    getline(cin, o.name);
    cout << "Enter menu item: ";
    getline(cin, o.item);
    cout << "Enter quantity: ";
    cin >> o.quantity;
    cout << "Enter price per item: ";
    cin >> o.price;
    o.status = "Pending"; // default status
    orders.push_back(o);
    cout << "Order added!\n";
}

// Display all orders
void displayOrders(const vector<Order>& orders) {
    cout << "\nCURRENT ORDERS\n";
    cout << left << setw(6) << "ID"
        << setw(12) << "Name"
        << setw(12) << "Item"
        << setw(6) << "Qty"
        << setw(8) << "Price"
        << setw(8) << "Total"
        << setw(10) << "Status" << endl;

    for (auto& o : orders) {
        float total = o.quantity * o.price;
        cout << left << setw(6) << o.id
            << setw(12) << o.name
            << setw(12) << o.item
            << setw(6) << o.quantity
            << setw(8) << fixed << setprecision(2) << o.price
            << setw(8) << total
            << setw(10) << o.status << endl;
    }
}

// Mark order as served
void markServed(vector<Order>& orders) {
    string id;
    cout << "Enter Order ID to mark as served: ";
    cin >> id;
    bool found = false;
    for (auto& o : orders) {
        if (o.id == id && o.status == "Pending") {
            o.status = "Served";
            cout << "Order " << id << " marked as Served.\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "Order not found or already served!\n";
}

// Sales summary
void salesSummary(const vector<Order>& orders) {
    int served = 0, pending = 0;
    double totalSales = 0;
    for (auto& o : orders) {
        if (o.status == "Served") {
            served++;
            totalSales += o.quantity * o.price;
        }
        else {
            pending++;
        }
    }
    cout << "\nSALES SUMMARY\n";
    cout << "Total Orders: " << orders.size() << endl;
    cout << "Served: " << served << endl;
    cout << "Pending: " << pending << endl;
    cout << "Total Sales: $" << fixed << setprecision(2) << totalSales << endl;
}

int p1() {
    vector<Order> orders;
    loadOrders(orders);
    int choice;

    cout << "****** Welcome to Restaurant Order Manager ******\n";

    do {
        cout << "\n1. Place New Order\n2. Display All Orders\n3. Mark Order as Served\n4. View Sales Summary\n5. Exit\n> ";
        cin >> choice;

        switch (choice) {
        case 1: placeOrder(orders); break;
        case 2: displayOrders(orders); break;
        case 3: markServed(orders); break;
        case 4: salesSummary(orders); break;
        case 5: saveOrders(orders);
            cout << "Orders saved to orders.txt. Have a great day!\n";
            break;
        default: cout << "Invalid option. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}