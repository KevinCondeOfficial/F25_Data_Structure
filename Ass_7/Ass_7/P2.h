#include <iostream>
#include <fstream>
#include <list>
#include <iomanip>
#include <string>
using namespace std;

// Struct to represent a patient
struct Patient {
    string id;
    string name;
    string severity; // Low/Medium/High/Critical
    int waitTime;
    string status;   // "Waiting" or "Admitted"
};

// Load patients from file
void loadPatients(list<Patient>& patients) {
    ifstream inFile("patients.txt");
    if (inFile.is_open()) {
        while (inFile >> ws && !inFile.eof()) {
            Patient p;
            getline(inFile, p.id, ',');
            getline(inFile, p.name, ',');
            getline(inFile, p.severity, ',');
            inFile >> p.waitTime;
            inFile.ignore(); // skip comma
            getline(inFile, p.status);
            patients.push_back(p);
        }
        inFile.close();
    }
}

// Save patients to file
void savePatients(const list<Patient>& patients) {
    ofstream outFile("patients.txt");
    for (auto& p : patients) {
        outFile << p.id << "," << p.name << "," << p.severity << ","
            << p.waitTime << "," << p.status << endl;
    }
    outFile.close();
}

// Register new patient
void registerPatient(list<Patient>& patients) {
    Patient p;
    cout << "Enter patient ID: ";
    cin >> p.id;
    cout << "Enter name: ";
    cin >> ws;
    getline(cin, p.name);
    cout << "Enter condition severity (Low/Medium/High/Critical): ";
    getline(cin, p.severity);
    cout << "Enter estimated wait time (minutes): ";
    cin >> p.waitTime;
    p.status = "Waiting";
    patients.push_back(p);
    cout << "Patient registered successfully!\n";
}

// Display patient queue
void displayQueue(const list<Patient>& patients) {
    cout << "\nER WAITING LIST\n";
    cout << left << setw(6) << "ID"
        << setw(20) << "Name"
        << setw(10) << "Severity"
        << setw(10) << "Wait(min)"
        << setw(10) << "Status" << endl;

    for (auto& p : patients) {
        cout << left << setw(6) << p.id
            << setw(20) << p.name
            << setw(10) << p.severity
            << setw(10) << p.waitTime
            << setw(10) << p.status << endl;
    }
}

// Admit first patient in queue
void admitPatient(list<Patient>& patients) {
    if (!patients.empty()) {
        Patient& p = patients.front();
        p.status = "Admitted";
        cout << "Patient " << p.id << " has been admitted to the ER.\n";
    }
    else {
        cout << "No patients in queue!\n";
    }
}

// View ER summary
void viewSummary(const list<Patient>& patients) {
    int admitted = 0, waiting = 0;
    double totalWait = 0;
    for (auto& p : patients) {
        if (p.status == "Admitted") {
            admitted++;
        }
        else {
            waiting++;
            totalWait += p.waitTime;
        }
    }
    double avgWait = (waiting > 0) ? totalWait / waiting : 0;

    cout << "\nER SUMMARY\n";
    cout << "Total Patients: " << patients.size() << endl;
    cout << "Admitted: " << admitted << endl;
    cout << "Waiting: " << waiting << endl;
    cout << "Avg Wait Time (Waiting): " << fixed << setprecision(2) << avgWait << " minutes\n";
}

int p2() {
    list<Patient> patients;
    loadPatients(patients);
    int choice;

    cout << "****** Welcome to Emergency Room Queue Manager ******\n";

    do {
        cout << "\n1. Register New Patient\n2. Display Patient Queue\n3. Admit Patient\n4. View ER Summary\n5. Exit\n> ";
        cin >> choice;

        switch (choice) {
        case 1: registerPatient(patients); break;
        case 2: displayQueue(patients); break;
        case 3: admitPatient(patients); break;
        case 4: viewSummary(patients); break;
        case 5: savePatients(patients);
            cout << "Patient queue saved to patients.txt. Have a safe shift!\n";
            break;
        default: cout << "Invalid option. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}