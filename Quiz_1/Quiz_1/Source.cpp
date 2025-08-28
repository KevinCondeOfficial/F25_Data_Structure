/*
* Name: Kevin Conde
* Assignment: Quiz 1 - Appointment system
* Date: 8/27/25
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
struct Birthdate //Can begin as zeros until entered
{
	int day;
	int month;
	int year;
};
struct Date
{
	int day;
	int month;
	int year;
};
struct Appointment
{
	Date date;
	Birthdate birthdate; //Initializes birthdate struct
	Name name; // Initializes name struct
	int id;
	string purpose;
};
#pragma endregion

int main()
{
#pragma region Variables
	int mainChoice = 0;
	Appointment schedule[100];
	int count = 0;
	int dayC;
	int monthC;
	int yearC;
	//string sem;
	//double wholeAvg;
	//char wholeLetter;

	//int score;
	//int sum = 0;
#pragma endregion
#pragma region Main Code
	do
	{
#pragma region Intro
		cout << setfill('*');
		cout << right << setw(24) << "Appointment " << left << setw(25) << "Schedular" << endl;

		cout << "Choose an option: \n";
		cout << "1) Schedule appointment\n";
		cout << "2) View appointments\n";
		cout << "0) Exit\n";
		cout << "Choice: ";
		cin >> mainChoice;

		if (mainChoice != 1 && mainChoice != 2)
		{
			mainChoice = 0;
		}
#pragma endregion

		if (mainChoice == 1)
		{
			cout << "\nSchedule Appointment:\n";

			//Initializing basic info
			cout << "First name: ";
			cin >> schedule[count].name.first;
			cout << "Last name: ";
			cin >> schedule[count].name.last;
			cout << "Enter birthday(MM DD YYYY): ";
			cin >> schedule[count].birthdate.month;
			cin >> schedule[count].birthdate.day;
			cin >> schedule[count].birthdate.year;
			cout << "Purpose: ";
			cin.ignore();
			getline(cin, schedule[count].purpose);
			cout << "Enter appointment date(MM DD YYYY): ";
			cin >> schedule[count].date.month;
			cin >> schedule[count].date.day;
			cin >> schedule[count].date.year;
			schedule[count].id = 100 + rand() % 900;
			for (int i = 0; i < count; i++)
			{
				if (schedule[count].id == schedule[i].id)
				{
					schedule[count].id = 100 + rand() % 900;
				}
			}
			cout << "Appointment ID: " << schedule[count].id << endl;
			cout << "Appointment Date: " << schedule[count].date.month << " " <<
				schedule[count].date.day << " " <<
				schedule[count].date.year << endl;
			count++;

			cout << "New student added successfully!\n\n";
		}
		else if (mainChoice == 2)
		{
			cout << "\nFind appointment: \n";

			cout << "Appointment Date(MM DD YYYY): "; //Collects appointment date
			cin >> monthC;
			cin >> dayC;
			cin >> yearC;
			if (count > 0)
			{
				for (int i = 0; i < count; i++) //Checks all parts of appointment to find appointments
				{
					if (monthC == schedule[i].date.month)
					{
						if (dayC == schedule[i].date.day)
						{
							if (yearC == schedule[i].date.year)
							{
								cout << "Name: " << schedule[i].name.last << ", " << schedule[i].name.first << endl;
								cout << "ID: " << schedule[i].id << endl;
								cout << "Purpose: " << schedule[i].purpose << endl;
							}
							else
							{
								cout << "No appointment exist.\n";
							}
						}
						else
						{
							cout << "No appointment exist.\n";
						}
					}
					else
					{
						cout << "No appointment exist.\n";
					}
				}
			}
			else
			{
				cout << "No appointment exist.\n";
			}

			cout << endl;
		}
	} while (mainChoice != 0);//Do while repeats the instance at least once
#pragma endregion
	system("pause");
	return 0;
}