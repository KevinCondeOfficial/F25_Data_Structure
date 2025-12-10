#include <iostream>
#include <string>
#include <queue>
#include <iomanip>
#include <cstdlib>
using namespace std;

struct Name {
    string first;
    string last;
};
struct Birthdate {
    int day, month, year;
};
struct Date {
    int day, month, year;
    int hour, minute;
};
struct Appointment {
    Date date;
    Birthdate birthdate;
    Name name;
    int id;
    string purpose;
};

// Date Vaildation 
bool isValidDate(int day, int month, int year) {
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Leap year check
    bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (leap && month == 2)
        return (day >= 1 && day <= 29);

    return (day >= 1 && day <= daysInMonth[month - 1]);
}

// Date/Time Duplicate check
bool isDuplicate(queue<Appointment> q, Appointment newAppt) {
    while (!q.empty()) {
        Appointment a = q.front();
        q.pop();

        if (a.date.day == newAppt.date.day &&
            a.date.month == newAppt.date.month &&
            a.date.year == newAppt.date.year &&
            a.date.hour == newAppt.date.hour &&
            a.date.minute == newAppt.date.minute) {
            return true;
        }
    }
    return false;
}

int main() {
    queue<Appointment> apptQueue;
    int choice;

    cout << setfill('*');
    cout << right << setw(24) << "Appointment " << left << setw(25) << "Scheduler" << endl;

    do {
        cout << "\nChoose an option:\n";
        cout << "1) Schedule appointment (ahead of time)\n";
        cout << "2) Walk-in appointment (added to queue)\n";
        cout << "3) View waiting appointments\n";
        cout << "4) Dispatch next appointment\n";
        cout << "0) Exit\nChoice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1 || choice == 2) {
            Appointment appt;
            cout << "First name: "; cin >> appt.name.first;
            cout << "Last name: "; cin >> appt.name.last;

            cout << "Enter birthday (MM DD YYYY): ";
            cin >> appt.birthdate.month >> appt.birthdate.day >> appt.birthdate.year;

            cout << "Purpose: "; cin.ignore(); getline(cin, appt.purpose);

            // Date Validation 
            do {
                cout << "Enter appointment date (MM DD YYYY): ";
                cin >> appt.date.month >> appt.date.day >> appt.date.year;

                if (!isValidDate(appt.date.day, appt.date.month, appt.date.year)) {
                    cout << "Invalid date! Please enter a valid calendar date.\n";
                }
            } while (!isValidDate(appt.date.day, appt.date.month, appt.date.year));

            // Time Validation 
            int hour, minute;
            string ampm;

            do {
                cout << "Enter appointment time (HH MM AM/PM): ";
                cin >> hour >> minute >> ampm;

                if (!(ampm == "AM" || ampm == "PM" || ampm == "am" || ampm == "pm") ||
                    hour < 1 || hour > 12 || minute < 0 || minute > 59) {

                    cout << "Invalid time! Please enter a correct time.\n";
                    continue;
                }

                break;

            } while (true);

            // Convert to 24-hour time
            if (ampm == "PM" || ampm == "pm") {
                if (hour != 12) hour += 12;
            }
            else { // AM
                if (hour == 12) hour = 0;
            }

            appt.date.hour = hour;
            appt.date.minute = minute;

            // Random ID
            appt.id = 100 + rand() % 900;

            // Check for duplicates
            if (isDuplicate(apptQueue, appt)) {
                cout << "Error: Appointment already exists on "
                    << appt.date.month << "/" << appt.date.day << "/" << appt.date.year;

                int displayHour = appt.date.hour % 12;
                if (displayHour == 0) displayHour = 12;
                string dispAMPM = (appt.date.hour >= 12 ? "PM" : "AM");

                cout << " at " << displayHour << ":" << setw(2) << setfill('0')
                    << appt.date.minute << " " << dispAMPM << "\n";
                cout << setfill('*');
            }
            else {
                apptQueue.push(appt);
                cout << "Appointment booked! ID: " << appt.id << "\n";
            }
        }

        else if (choice == 3) {
            if (apptQueue.empty()) {
                cout << "No appointments waiting.\n";
            }
            else {
                cout << "\nWAITING APPOINTMENTS (Front to Rear):\n";
                queue<Appointment> temp = apptQueue;
                while (!temp.empty()) {
                    Appointment a = temp.front();
                    temp.pop();

                    int displayHour = a.date.hour % 12;
                    if (displayHour == 0) displayHour = 12;
                    string dispAMPM = (a.date.hour >= 12 ? "PM" : "AM");

                    cout << "ID: " << a.id << " | "
                        << a.name.first << " " << a.name.last << " | "
                        << a.date.month << "/" << a.date.day << "/" << a.date.year << " "
                        << displayHour << ":" << setw(2) << setfill('0') << a.date.minute << " " << dispAMPM
                        << " | Purpose: " << a.purpose << "\n";
                    cout << setfill('*');
                }
            }
        }

        else if (choice == 4) {
            if (apptQueue.empty()) {
                cout << "No appointments to dispatch.\n";
            }
            else {
                Appointment a = apptQueue.front();
                apptQueue.pop();
                cout << "Dispatched appointment:\n";
                cout << "ID: " << a.id << " | "
                    << a.name.first << " " << a.name.last
                    << " | Purpose: " << a.purpose << "\n";
            }
        }

    } while (choice != 0);

    cout << "Goodbye!\n";
    return 0;
}
