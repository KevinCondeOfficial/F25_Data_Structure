#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// Templated struct for Appointment
// T1 = ID type (string or int)
// T2 = Bill type (float or double)
template <typename T1, typename T2>
struct Appointment {
    T1 id;             // appointment ID
    string name;       // patient name
    string type;       // appointment type (General/Dental/Emergency/etc.)
    int timeUntil;     // time until appointment in hours
    T2 bill;           // estimated bill
    string status;     // "Pending" or "Completed"
};

// Load appointments from file
template <typename T1, typename T2>
int loadAppointments(Appointment<T1, T2> appointments[]) {
    ifstream inFile("appointments.txt");
    int count = 0;
    if (inFile.is_open()) {
        while (inFile >> ws && !inFile.eof()) {
            string idStr, billStr;
            getline(inFile, idStr, ',');
            if (idStr.empty()) break;
            appointments[count].id = idStr; // using string ID here
            getline(inFile, appointments[count].name, ',');
            getline(inFile, appointments[count].type, ',');
            inFile >> appointments[count].timeUntil;
            inFile.ignore(); // skip comma
            getline(inFile, billStr, ',');
            appointments[count].bill = stof(billStr);
            getline(inFile, appointments[count].status);
            count++;
        }
        inFile.close();
    }
    return count;
}

// Save appointments to file
template <typename T1, typename T2>
void saveAppointments(Appointment<T1, T2> appointments[], int count) {
    ofstream outFile("appointments.txt");
    for (int i = 0; i < count; i++) {
        outFile << appointments[i].id << ","
            << appointments[i].name << ","
            << appointments[i].type << ","
            << appointments[i].timeUntil << ","
            << fixed << setprecision(2) << appointments[i].bill << ","
            << appointments[i].status << endl;
    }
    outFile.close();
}

// Add new appointment
template <typename T1, typename T2>
void addAppointment(Appointment<T1, T2> appointments[], int& count) {
    cout << "Enter appointment ID: ";
    cin >> appointments[count].id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter patient name: ";
    getline(cin, appointments[count].name);
    cout << "Enter appointment type: ";
    getline(cin, appointments[count].type);
    cout << "Enter time until appointment (hours): ";
    cin >> appointments[count].timeUntil;
    cout << "Enter estimated bill: ";
    cin >> appointments[count].bill;
    appointments[count].status = "Pending";
    count++;
    cout << "Appointment added!\n";
}

// Display all appointments
template <typename T1, typename T2>
void displayAppointments(Appointment<T1, T2> appointments[], int count) {
    cout << "\nAPPOINTMENTS\n";
    cout << left << setw(8) << "ID"
        << setw(15) << "Name"
        << setw(12) << "Type"
        << setw(8) << "Time"
        << setw(10) << "Bill"
        << setw(12) << "Status" << endl;

    for (int i = 0; i < count; i++) {
        cout << left << setw(8) << appointments[i].id
            << setw(15) << appointments[i].name
            << setw(12) << appointments[i].type
            << setw(8) << appointments[i].timeUntil
            << "$" << setw(9) << fixed << setprecision(2) << appointments[i].bill
            << setw(12) << appointments[i].status << endl;
    }
}

// Mark appointment as completed
template <typename T1, typename T2>
void markCompleted(Appointment<T1, T2> appointments[], int count) {
    T1 id;
    cout << "Enter appointment ID to mark as completed: ";
    cin >> id;
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (appointments[i].id == id) {
            appointments[i].status = "Completed";
            cout << "Appointment " << id << " marked as Completed.\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "Appointment not found.\n";
}

// Appointment summary
template <typename T1, typename T2>
void appointmentSummary(Appointment<T1, T2> appointments[], int count) {
    int completed = 0, pending = 0;
    double earnings = 0;
    for (int i = 0; i < count; i++) {
        if (appointments[i].status == "Completed") {
            completed++;
            earnings += appointments[i].bill;
        }
        else {
            pending++;
        }
    }
    cout << "\nAPPOINTMENT SUMMARY\n";
    cout << "Total Appointments: " << count << endl;
    cout << "Completed: " << completed << endl;
    cout << "Pending: " << pending << endl;
    cout << "Total Earnings: $" << fixed << setprecision(2) << earnings << endl;
}

int main() {
    Appointment<string, float> appointments[100]; // using string IDs and float bills
    int count = loadAppointments(appointments);
    int choice;

    cout << "******* Welcome to Clinic Appointment Manager *******\n";
    do {
        cout << "\n1. Add New Appointment\n2. Display All Appointments\n3. Mark Appointment as Completed\n4. View Appointment Summary\n5. Exit\n> ";
        cin >> choice;
        switch (choice) {
        case 1: addAppointment(appointments, count); break;
        case 2: displayAppointments(appointments, count); break;
        case 3: markCompleted(appointments, count); break;
        case 4: appointmentSummary(appointments, count); break;
        case 5: saveAppointments(appointments, count);
            cout << "Data saved to appointments.txt. Goodbye!\n"; break;
        default: cout << "Invalid option.\n";
        }
    } while (choice != 5);

    return 0;
}