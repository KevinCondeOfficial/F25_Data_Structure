#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAXQ = 100;

struct Taxi {
    int id;
    string driver;
    string model;
    string plate;
};

class Queue {
private:
    Taxi arr[MAXQ];
    int front, rear, count;
public:
    Queue() { front = 0; rear = -1; count = 0; }

    bool isEmpty() { return count == 0; }
    bool isFull() { return count == MAXQ; }

    void enqueue(Taxi t) {
        if (isFull()) {
            cout << "Queue is full. No more taxis can be added.\n";
            return;
        }
        rear = (rear + 1) % MAXQ;
        arr[rear] = t;
        count++;
        cout << "Taxi added to queue!\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "No taxis available for dispatch.\n";
            return;
        }
        Taxi t = arr[front];
        front = (front + 1) % MAXQ;
        count--;
        cout << "Taxi dispatched:\n";
        cout << "ID: " << t.id << ", Driver: " << t.driver
            << ", Car: " << t.model << ", Plate: " << t.plate << "\n";
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "WAITING TAXIS (Front to Rear)\n";
        for (int i = 0; i < count; i++) {
            int idx = (front + i) % MAXQ;
            cout << arr[idx].id << " | " << arr[idx].driver << " | "
                << arr[idx].model << " | " << arr[idx].plate << "\n";
        }
    }

    void summary() {
        if (isEmpty()) {
            cout << "No taxis waiting.\n";
            return;
        }
        cout << "QUEUE SUMMARY\n";
        cout << "Total Taxis Waiting: " << count << "\n";
        cout << "Front Taxi: ID " << arr[front].id << " - " << arr[front].driver << "\n";
        cout << "Rear Taxi: ID " << arr[rear].id << " - " << arr[rear].driver << "\n";
    }

    void saveToFile() {
        ofstream fout("taxis.txt");
        for (int i = 0; i < count; i++) {
            int idx = (front + i) % MAXQ;
            fout << arr[idx].id << "," << arr[idx].driver << ","
                << arr[idx].model << "," << arr[idx].plate << "\n";
        }
        fout.close();
        cout << "Taxi queue saved to taxis.txt. Have a safe dispatch!\n";
    }
};

int q() {
    Queue q;
    int choice;
    cout << "****** Welcome to Airport Taxi Queue System ******\n";
    do {
        cout << "\n1. Add Taxi to Queue\n2. View Waiting Taxis\n3. Dispatch Next Taxi\n";
        cout << "4. View Queue Summary\n5. Exit\nChoice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            Taxi t;
            cout << "Enter Taxi ID: "; cin >> t.id; cin.ignore();
            cout << "Enter Driver Name: "; getline(cin, t.driver);
            cout << "Enter Car Model: "; getline(cin, t.model);
            cout << "Enter License Plate: "; getline(cin, t.plate);
            q.enqueue(t);
        }
        else if (choice == 2) {
            q.display();
        }
        else if (choice == 3) {
            q.dequeue();
        }
        else if (choice == 4) {
            q.summary();
        }
        else if (choice == 5) {
            q.saveToFile();
        }
    } while (choice != 5);
    return 0;
}