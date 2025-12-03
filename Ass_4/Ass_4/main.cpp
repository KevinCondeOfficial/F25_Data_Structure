/*
* Kevin Conde
* Assignment 4
* 12/3/25
*/

#include <iostream>
using namespace std;

// Recursive function to display grades
// Parameters: grades array, total size, current index (default = 0)
void displayGrades(int grades[], int size, int index = 0) {
    if (index == size) {
        // Base case: if index reaches size, stop recursion
        return;
    }
    cout << grades[index] << " "; // Print current grade
    displayGrades(grades, size, index + 1); // Recursive call for next grade
}

// Recursive function to sum all grades
// Returns the total sum of grades
int sumGrades(int grades[], int size, int index = 0) {
    if (index == size) {
        // Base case: no more grades left
        return 0;
    }
    // Add current grade + recursive sum of remaining grades
    return grades[index] + sumGrades(grades, size, index + 1);
}

// Recursive function to count failing grades (< 60)
int countFailing(int grades[], int size, int index = 0) {
    if (index == size) {
        // Base case: no more grades left
        return 0;
    }
    // If current grade < 60, count it + recurse
    if (grades[index] < 60) {
        return 1 + countFailing(grades, size, index + 1);
    }
    else {
        return countFailing(grades, size, index + 1);
    }
}

// Recursive function to find the maximum grade
int findMax(int grades[], int size, int index = 0, int currentMax = -1) {
    if (index == size) {
        // Base case: return the maximum found
        return currentMax;
    }
    // Update currentMax if current grade is larger
    if (grades[index] > currentMax) {
        currentMax = grades[index];
    }
    // Recursive call for next grade
    return findMax(grades, size, index + 1, currentMax);
}

int main() {
    const int MAX_SIZE = 100; // Maximum number of grades
    int grades[MAX_SIZE];     // Array to store grades
    int size = 0;             // Number of grades entered
    int choice;

    cout << "****** Welcome to Recursive Grade Analyzer ******" << endl;

    do {
        cout << "\nPlease choose one of the following operations:\n";
        cout << "1 - Enter Grades\n";
        cout << "2 - Display Grades\n";
        cout << "3 - Calculate Average Grade (using Recursion)\n";
        cout << "4 - Count Failing Grades (using Recursion)\n";
        cout << "5 - Find Highest Grade (using Recursion)\n";
        cout << "6 - Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "How many grades do you want to enter? ";
            cin >> size;
            for (int i = 0; i < size; i++) {
                cout << "Enter grade #" << (i + 1) << ": ";
                cin >> grades[i];
            }
            cout << "Grades successfully saved!" << endl;

        }
        else if (choice == 2) {
            cout << "Grades entered: ";
            displayGrades(grades, size);
            cout << endl;

        }
        else if (choice == 3) {
            if (size > 0) {
                double average = (double)sumGrades(grades, size) / size;
                cout << "The average grade is: " << average << endl;
            }
            else {
                cout << "No grades entered yet!" << endl;
            }

        }
        else if (choice == 4) {
            int failingCount = countFailing(grades, size);
            cout << "Number of failing grades: " << failingCount << endl;

        }
        else if (choice == 5) {
            if (size > 0) {
                int highest = findMax(grades, size);
                cout << "Highest grade: " << highest << endl;
            }
            else {
                cout << "No grades entered yet!" << endl;
            }
        }

    } while (choice != 6);

    cout << "Thank you for using Recursive Grade Analyzer!" << endl;
    return 0;
}