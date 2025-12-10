#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Circular singly linked list node for a traffic light
struct TrafficLight {
    int id;              // road ID
    string roadName;     // road name
    string color;        // current color (Green/Yellow/Red)
    TrafficLight* next;  // next light in the circle
};

TrafficLight* lead = nullptr;    // start of the circle
TrafficLight* current1 = nullptr; // "active" light pointer

// Insert a new light at the end (maintaining circularity)
void addLight() {
    TrafficLight* t = new TrafficLight();

    cout << "Enter Road ID: ";
    cin >> t->id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Road Name: ";
    getline(cin, t->roadName);

    cout << "Enter Initial Light Color (Green/Yellow/Red): ";
    getline(cin, t->color);

    if (!lead) {
        // First node points to itself
        lead = t;
        t->next = lead;
        current1 = lead;
    }
    else {
        // Find tail (node whose next is head)
        TrafficLight* tail = lead;
        while (tail->next != lead) tail = tail->next;
        tail->next = t;
        t->next = lead;
    }
    cout << "Traffic light added for " << t->roadName << ".\n";
}

// Display the sequence once around the circle from head
void displaySequence() {
    if (!lead) { cout << "No lights in system.\n"; return; }

    cout << "\nTRAFFIC LIGHT SEQUENCE\n";
    cout << left << "ID  Road Name           Color\n";

    TrafficLight* temp = lead;
    do {
        cout << temp->id << "   " << temp->roadName << "   " << temp->color << endl;
        temp = temp->next;
    } while (temp != lead);
}

// Advance the system: current -> Red, next -> Green, all others -> Yellow
void advanceLight() {
    if (!current) { cout << "No lights in system.\n"; return; }

    // First, set all lights to Yellow
    TrafficLight* temp = lead;
    if (temp) {
        do {
            temp->color = "Yellow";
            temp = temp->next;
        } while (temp != lead);
    }

    // Set current to Red
    current1->color = "Red";
    // Set next to Green and shift current pointer forward
    current1 = current1->next;
    current1->color = "Green";

    // Print snapshot
    cout << current1->roadName << " > Green\n";

    // Show others explicitly (optional, but matches sample behavior)
    TrafficLight* t = lead;
    do {
        if (t != current1) {
            if (t->color == "Red") cout << t->roadName << " > Red\n";
            else cout << t->roadName << " > Yellow\n";
        }
        t = t->next;
    } while (t != lead);
}

// Delete all nodes and reset pointers
void resetSystem() {
    if (!head) { cout << "System reset. All traffic lights cleared.\n"; return; }

    // Break circular reference to simplify deletion
    TrafficLight* tail = lead;
    while (tail->next != lead) tail = tail->next;
    tail->next = nullptr;

    // Delete linear chain
    TrafficLight* temp = lead;
    while (temp) {
        TrafficLight* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }

    head = nullptr;
    current = nullptr;
    cout << "System reset. All traffic lights cleared.\n";
}

int p3() {
    int choice;
    cout << "****** Welcome to Smart Traffic Light Controller ******\n";
    do {
        cout << "\n1. Add Road and Light\n2. Display Light Sequence\n3. Advance to Next Light\n4. Reset System\n5. Exit\n> ";
        cin >> choice;

        switch (choice) {
        case 1: addLight(); break;
        case 2: displaySequence(); break;
        case 3: advanceLight(); break;
        case 4: resetSystem(); break;
        case 5: cout << "Traffic system saved. Goodbye and drive safe!\n"; break;
        default: cout << "Invalid option. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}