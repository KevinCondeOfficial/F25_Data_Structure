/*
* Name: Kevin Conde
* Assignment: Assignment #1 - Simple Gradebook
* Date: 8/22/25
*/

#include <iostream>
#include <string>
#include <iomanip> // Allows for setfill to be used
using namespace std;

#pragma region Structs
struct Name
{
	string first;
	string last;
};
struct Scores
{
	double exam1 = 0; // 0–100
	double exam2 = 0; // 0–100
	double exam3 = 0; // 0–100
	double average; // computed as (e1 + e2 + e3)/3.0
	char letter; // A/B/C/D/F based on average
};
struct Student
{
	int id; // auto-generated
	Name name;
	string semester; // e.g., "Fall 2025", "Spring 2026"
	Scores scores; // can begin as zeros until entered
};
#pragma endregion

int main()
{
#pragma region Variables
	int mainChoice = 0;
	Student gradebook[100]; 
	int count = 0;
	bool idValid = false;
	int idCheck;
	int idUse;
	string sem;
	double wholeAvg;
	char wholeLetter;

	//int score;
	//int sum = 0;
#pragma endregion
#pragma region Main Code
	do
	{
		cout << setfill('*');
		cout << right << setw(24) << "Teacher " << left << setw(25) << "Gradebook" << endl;
		
		cout << "Choose an option: \n";
		cout << "1) Add new student\n";
		cout << "2) Enter/Updates scores\n";
		cout << "3) Display report for one student\n";
		cout << "4) Display report for whole semester\n";
		cout << "5) List all students\n";
		cout << "0) Exit\n";
		cout << "Choice: ";
		cin >> mainChoice;

		if (mainChoice != 1 && mainChoice != 2 && mainChoice != 3 && mainChoice != 4 && mainChoice != 5)
		{
			mainChoice = 0;
		}

		if (mainChoice == 1)
		{
			cout << "\nEnter new student info:\n";

			cout << "First name: ";
			cin >> gradebook[count].name.first;
			cout << "Last name: ";
			cin >> gradebook[count].name.last;
			cout << "Current semester(Fall 25): ";
			cin.ignore();
			getline(cin, gradebook[count].semester);
			gradebook[count].id = 10000 + rand() % 90000;
			for (int i = 0; i < count; i++)
			{
				if (gradebook[count].id == gradebook[i].id)
				{
					gradebook[count].id = 10000 + rand() % 90000;
				}
			}
			cout << "New ID: " << gradebook[count].id << endl;
			gradebook[count].scores.average = 0;
			gradebook[count].scores.letter = 'F';
			count++;

			cout << "New student added successfully!\n\n";
		}
		else if (mainChoice == 2)
		{
			cout << "\nGradebook updates: \n";

			cout << "Enter student ID: ";
			cin >> idCheck;
			idValid = false;
			if (count > 0)
			{
				for (int i = 0; i < count; i++)
				{
					if (idCheck == gradebook[i].id)
					{
						idValid = true;
						idUse = i;
					}
				}

				if (idValid == true)
				{
					cout << "Enter student exam grades: \n";
					cout << "Exam 1: ";
					cin >> gradebook[idUse].scores.exam1;
					cout << "Exam 2: ";
					cin >> gradebook[idUse].scores.exam2;
					cout << "Exam 3: ";
					cin >> gradebook[idUse].scores.exam3;

					gradebook[idUse].scores.average = (gradebook[idUse].scores.exam1 + gradebook[idUse].scores.exam2 + gradebook[idUse].scores.exam3) / 3;

					if (gradebook[idUse].scores.average >= 90)
					{
						gradebook[idUse].scores.letter = 'A';
					}
					else if (gradebook[idUse].scores.average >= 80)
					{
						gradebook[idUse].scores.letter = 'B';
					}
					else if (gradebook[idUse].scores.average >= 70)
					{
						gradebook[idUse].scores.letter = 'C';
					}
					else if (gradebook[idUse].scores.average >= 60)
					{
						gradebook[idUse].scores.letter = 'D';
					}
					else
					{
						gradebook[idUse].scores.letter = 'F';
					}
				}
				else
				{
					cout << "No student exist.\n\n";
				}
			}
			else
			{
				cout << "No students exist.\n\n";
			}

			cout << "Student grades updated successfully!\n\n";
		}
		else if (mainChoice == 3)
		{
			cout << "\nStudent Grades: \n";

			cout << "Enter student ID: ";
			cin >> idCheck;
			idValid = false;
			if (count > 0)
			{
				for (int i = 0; i < count; i++)
				{
					if (idCheck == gradebook[i].id)
					{
						idValid = true;
						idUse = i;
					}
				}

				if (idValid == true)
				{
					cout << "Name: " << gradebook[idUse].name.last << ", " << gradebook[idUse].name.first << endl;
					cout << "ID: " << gradebook[idUse].id << endl;
					cout << "Semester: " << gradebook[idUse].semester << endl;
					cout << "Grade: " << gradebook[idUse].scores.average << ", " << gradebook[idUse].scores.letter << "\n\n";
					cout << "Exam 1: " << gradebook[idUse].scores.exam1 << endl;
					cout << "Exam 2: " << gradebook[idUse].scores.exam2 << endl;
					cout << "Exam 3: " << gradebook[idUse].scores.exam3 << endl;
				}
				else
				{
					cout << "No student exist.\n\n";
				}
			}
			else
			{
				cout << "No students exist.\n\n";
			}

			cout << "Student grades updated successfully!\n\n";
		}
		else if (mainChoice == 4)
		{
			cout << "\nSemester Review: \n";

			cin.ignore();
			cout << "Semester: ";
			getline(cin, sem);
			wholeAvg = 0;
			wholeLetter = 'F';
			if (count > 0)
			{
				for (int i = 0; i < count; i++)
				{
					if (sem == gradebook[i].semester)
					{
						cout << "Name: " << gradebook[i].name.last << ", " << gradebook[i].name.first << endl;
						cout << "ID: " << gradebook[i].id << endl;
						cout << "Semester: " << gradebook[i].semester << endl;
						cout << "Grade: " << gradebook[i].scores.average << ", " << gradebook[i].scores.letter << endl;
						cout << "Exam 1: " << gradebook[i].scores.exam1 << endl;
						cout << "Exam 2: " << gradebook[i].scores.exam2 << endl;
						cout << "Exam 3: " << gradebook[i].scores.exam3 << "\n\n";

						wholeAvg += gradebook[i].scores.average;
					}
				}
			}
			else
			{
				cout << "No students exist.\n\n";
			}

			wholeAvg = wholeAvg / count;
			if (wholeAvg >= 90)
			{
				wholeLetter = 'A';
			}
			else if (wholeAvg >= 80)
			{
				wholeLetter = 'B';
			}
			else if (wholeAvg >= 70)
			{
				wholeLetter = 'C';
			}
			else if (wholeAvg >= 60)
			{
				wholeLetter = 'D';
			}
			else
			{
				wholeLetter = 'F';
			}

			cout << "Whole semester average : " << wholeAvg << ", " <<  wholeLetter << "\n\n";
		}
		else if (mainChoice == 5)
		{
			cout << "\nStudent List: \n";

			if (count > 0)
			{
				for (int i = 0; i < count; i++)
				{
					cout << "Name: " << gradebook[i].name.last << ", " << gradebook[i].name.first << endl;
					cout << "ID: " << gradebook[i].id << endl;
					cout << "Semester: " << gradebook[i].semester << "\n\n";
				}
			}
			else
			{
				cout << "No students exist.\n\n";
			}
		}
	} while(mainChoice != 0); //Do while repeats the instance at least once
#pragma endregion
	system("pause");
	return 0;
}