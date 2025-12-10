#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct Patient {
    string id;
    string name;
    string condition;
    int severity;
    Patient* next;
};

Patient* head = nullptr;   // start of the queue
int totalServed = 0;       // counter for served patients

// Load patients from file
void loadPatients() {
    ifstream inFile("patients.txt");
    if (inFile.is_open()) {
        while (inFile >> ws && !inFile.eof()) {
            Patient* p = new Patient;
            getline(inFile, p->id, ',');
            getline(inFile, p->name, ',');
            getline(inFile, p->condition, ',');
            inFile >> p->severity;
            inFile.ignore(); // skip newline
            p->next = nullptr;

            if (!head) head = p;
            else {
                Patient* temp = head;
                while (temp->next) temp = temp->next;
                temp->next = p;
            }
        }
        inFile.close();
    }
}

// Save patients to file
void savePatients() {
    ofstream outFile("patients.txt");
    Patient* temp = head;
    while (temp) {
        outFile << temp->id << "," << temp->name << ","
            << temp->condition << "," << temp->severity << endl;
        temp = temp->next;
    }
    outFile.close();
}

// Add new patient
void addPatient() {
    Patient* p = new Patient;
    cout << "Enter Patient ID: ";
    cin >> p->id;
    cin.ignore();
    cout << "Enter patient name: ";
    getline(cin, p->name);
    cout << "Enter condition: ";
    getline(cin, p->condition);
    cout << "Enter severity (1-5): ";
    cin >> p->severity;
    p->next = nullptr;

    if (!head) head = p;
    else {
        Patient* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = p;
    }
    cout << "Patient added to the queue.\n";
}

// Display queue
void displayQueue() {
    cout << "\nCURRENT QUEUE\n";
    Patient* temp = head;
    while (temp) {
        cout << temp->id << " " << temp->name << " "
            << temp->condition << " " << temp->severity << endl;
        temp = temp->next;
    }
}

// Serve next patient
void servePatient() {
    if (!head) {
        cout << "No patients in queue.\n";
        return;
    }
    Patient* temp = head;
    cout << "Serving Patient: " << temp->id << " - " << temp->name << endl;
    head = head->next;
    delete temp;
    totalServed++;
}

// Show summary
void showSummary() {
    int count = 0, severitySum = 0;
    Patient* temp = head;
    while (temp) {
        count++;
        severitySum += temp->severity;
        temp = temp->next;
    }
    double avgSeverity = (count > 0) ? (double)severitySum / count : 0;

    cout << "\nER SUMMARY\n";
    cout << "Total Patients Served: " << totalServed << endl;
    cout << "Patients in Queue: " << count << endl;
    cout << "Average Severity of Waiting Patients: " << fixed << setprecision(2) << avgSeverity << endl;
}

int p1() {
    loadPatients();
    int choice;
    cout << "****** Welcome to ER Patient Queue Manager ******\n";
    do {
        cout << "\n1. Add New Patient\n2. Display Patient Queue\n3. Serve Next Patient\n4. View ER Summary\n5. Exit\n> ";
        cin >> choice;
        switch (choice) {
        case 1: addPatient(); break;
        case 2: displayQueue(); break;
        case 3: servePatient(); break;
        case 4: showSummary(); break;
        case 5: savePatients(); cout << "Patient queue saved to patients.txt. Stay safe!\n"; break;
        default: cout << "Invalid option.\n";
        }
    } while (choice != 5);
    return 0;
}