#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX = 100; // maximum stack size

struct Box {
    int id;
    string item;
    float weight;
    string destination;
};

class Stack {
private:
    Box arr[MAX];
    int top;
public:
    Stack() { top = -1; }

    bool isEmpty() { return top == -1; }
    bool isFull() { return top == MAX - 1; }

    void push(Box b) {
        if (isFull()) {
            cout << "Stack is full. Cannot add more boxes.\n";
            return;
        }
        arr[++top] = b;
        cout << "Box added to stack!\n";
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack is empty. No boxes to dispatch.\n";
            return;
        }
        Box b = arr[top--];
        cout << "Top box dispatched:\n";
        cout << "ID: " << b.id << ", Item: " << b.item
            << ", Destination: " << b.destination << "\n";
    }

    void display() {
        if (isEmpty()) {
            cout << "Stack is empty.\n";
            return;
        }
        cout << "STACKED BOXES (Top to Bottom)\n";
        for (int i = top; i >= 0; i--) {
            cout << arr[i].id << " | " << arr[i].item << " | "
                << arr[i].weight << "kg | " << arr[i].destination << "\n";
        }
    }

    void summary() {
        if (isEmpty()) {
            cout << "No boxes in stack.\n";
            return;
        }
        float totalWeight = 0;
        for (int i = 0; i <= top; i++) totalWeight += arr[i].weight;

        cout << "INVENTORY SUMMARY\n";
        cout << "Total Boxes in Stack: " << top + 1 << "\n";
        cout << "Total Weight: " << totalWeight << " kg\n";
        cout << "Top Box: ID " << arr[top].id << " - " << arr[top].item << "\n";
    }

    void saveToFile() {
        ofstream fout("inventory.txt");
        for (int i = top; i >= 0; i--) {
            fout << arr[i].id << "," << arr[i].item << ","
                << arr[i].weight << "," << arr[i].destination << "\n";
        }
        fout.close();
        cout << "Inventory saved to inventory.txt. Have a productive day!\n";
    }
};

int ware() {
    Stack s;
    int choice;
    cout << "Welcome to Warehouse Inventory Stack Tracker\n";
    do {
        cout << "\n1. Add Box to Stack\n2. View Current Stack\n3. Remove Top Box (Dispatch)\n";
        cout << "4. View Inventory Summary\n5. Exit\nChoice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            Box b;
            cout << "Enter Box ID: "; cin >> b.id; cin.ignore();
            cout << "Enter Item Name: "; getline(cin, b.item);
            cout << "Enter Weight (kg): "; cin >> b.weight; cin.ignore();
            cout << "Enter Destination: "; getline(cin, b.destination);
            s.push(b);
        }
        else if (choice == 2) {
            s.display();
        }
        else if (choice == 3) {
            s.pop();
        }
        else if (choice == 4) {
            s.summary();
        }
        else if (choice == 5) {
            s.saveToFile();
        }
    } while (choice != 5);
    return 0;
}