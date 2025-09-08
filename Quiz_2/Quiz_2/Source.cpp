/*
* Name: Kevin Conde
* Assignment: Quiz #2 - 
* Date: 9/7/25
*/

#include <iostream>
#include <string>
#include <iomanip> // Allows for setfill to be used
using namespace std;

#pragma region Classes
class Task
{
private:
	int id; //task ID
	string title;
	bool complete; //true if complete, false if uncomplete
public:
	// Default constructor
	Task()
	{
		id = 0;
		title = "";
		complete = false;
	}
	//Constructor parameterized.
	Task(int i, string t, bool com)
	{
		id = i;
		title = t;
		complete = com;
	}
	void addTask()
	{
		cin.ignore();
		cout << "\nAdd Task\n";
		cout << "Enter info: \n";
		cout << "Title: ";
		getline(cin, title);
		id = 10000 + rand() % 89999;

		cout << "\nTask created successfully.\n";
		cout << title << " | " << id << "\n\n";
	}
	//Getters and setters for accessing private data.
	bool markTask(int idCheck) //sets available = false if available.
	{
		if (id == idCheck)
		{
			if (complete == false)
			{
				cout << "\'" << title << "\' successfully completed!\n\n";
				complete = true;
			}
		}
		return complete;
	}
	void displayAll() //prints book details(ID, title, author, year, status).
	{
		cout << title << " | " << id << "\n";
	}
};
#pragma endregion

int main()
{
#pragma region Variables
	Task task[100];
	int count = 0;
	int mainChoice = 0;
	int idCheck;
#pragma endregion
#pragma region Main Code
	cout << setfill('*');
	cout << right << setw(24) << "To-Do " << left << setw(25) << "Manager" << endl;

	do
	{
		cout << "Select one: \n";
		cout << "1) Add Task\n";
		cout << "2) Mark off Task\n";
		cout << "3) Display all Tasks\n";
		cout << "0) Exit\n";
		cout << "Choice: ";
		cin >> mainChoice;

		switch (mainChoice)
		{
		case 1:
			task[count].addTask();
			count++; break;
		case 2:
			cout << "\nTask completion\n";
			cout << "Enter info: \n";
			cout << "ID: ";
			cin >> idCheck;

			for (int i = 0; i < count; i++)
			{
				task[i].markTask(idCheck);
				if (task[i].markTask(idCheck) == true)
				{
					for (int x = i; x < count; x++)
					{
						task[x] = task[x + 1];
					}
					count--;
					break;
				}
			} break;
		case 3:
			cout << "\nAll books: \n";
			for (int i = 0; i < count; i++)
			{
				task[i].displayAll();
			} 
			cout << endl; break;
		case 0:
			cout << "Have a great day.\n"; break;
		default:
			cout << "Invalid choice.\n";  break;
		}

	} while (mainChoice != 0); //Do while repeats the instance at least once

#pragma endregion
	system("pause");
	return 0;
}