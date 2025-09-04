/*
* Name: Kevin Conde
* Assignment: Assignment #2 - Library Management System
* Date: 9/2/25
*/

#include <iostream>
#include <string>
#include <iomanip> // Allows for setfill to be used
using namespace std;

#pragma region Classes
class Book
{
private:
	int id; //book ID
	string title;
	string author;
	int year;
	bool available; //true if available, false if borrowed
public:
	// Default constructor
	Book()
	{
		id = 0;
		title = "";
		author = "";
		year = 0;
		available = true;
	}
	//Constructor parameterized.
	Book(int i, string t, string a, int y, bool ava)
	{
		id = i;
		title = t;
		author = a;
		year = y;
		available = ava;
	}
	void addBook()
	{
		cin.ignore();
		cout << "\nAdd Book\n";
		cout << "Enter info: \n";
		cout << "Title: ";
		getline(cin, title);
		cout << "Author: ";
		getline(cin, author);
		cout << "Year: ";
		cin >> year;
		id =  10000 + rand() % 89999;

		cout << "\nBook created successfully.\n";
		cout << title << " by " << author << ", " << year << ", " << id << "\n\n";
	}
	//Getters and setters for accessing private data.
	void borrowBook(int idCheck) //sets available = false if available.
	{
		if (id == idCheck)
		{
			if (available == true)
			{
				cout << "\'" << title << "\' successfully checked out!\n\n";
				available = false;
			}
			else
			{
				cout << "Book not available.\n\n";
			}
		}
	}
	void returnBook(int idCheck) //sets available = true if currently borrowed.
	{
		if (id == idCheck)
		{
			if (available == false)
			{
				cout << "\'" << title << "\' successfully returned!\n\n";
				available = true;
			}
			else
			{
				cout << "Book not checked out.\n\n";
			}
		}
	}
	void display(int idCheck) //prints book details(ID, title, author, year, status).
	{
		if (id == idCheck)
		{
			cout << title << " by " << author << ", " << year << ", " << id << "\n\n";
		}
	}
	void displayAll() //prints book details(ID, title, author, year, status).
	{
		cout << title << " by " << author << ", " << year << ", " << id << "\n\n";
	}
};
#pragma endregion

int main()
{
#pragma region Variables
	Book book[100];
	int count = 0;
	int mainChoice = 0;
	int idCheck;
#pragma endregion
#pragma region Main Code
	cout << setfill('*');
	cout << right << setw(24) << "Book " << left << setw(25) << "Library" << endl;

	do
	{
		cout << "Select one: \n";
		cout << "1) Add Book\n";
		cout << "2) Checkout Book\n";
		cout << "3) Return Book\n";
		cout << "4) Display Book Info\n";
		cout << "5) Display all Books\n";
		cout << "0) Exit\n";
		cout << "Choice: ";
		cin >> mainChoice;

		switch (mainChoice)
		{
			case 1:
				book[count].addBook(); 
				count++; break;
			case 2:
				cout << "\nBook checkout\n";
				cout << "Enter info: \n";
				cout << "ID: ";
				cin >> idCheck;
				
				for (int i = 0; i < count; i++)
				{
					book[i].borrowBook(idCheck);
				} break;
			case 3:
				cout << "\nBook return\n";
				cout << "Enter info: \n";
				cout << "ID: ";
				cin >> idCheck;

				for (int i = 0; i < count; i++)
				{
					book[i].returnBook(idCheck);
				} break;
			case 4: 
				cout << "\nBook detail search\n";
				cout << "Enter info: \n";
				cout << "ID: ";
				cin >> idCheck;

				for (int i = 0; i < count; i++)
				{
					book[i].display(idCheck);
				} break;
			case 5:
				cout << "\nAll books: \n";
				for (int i = 0; i < count; i++)
				{
					book[i].displayAll();
				} break;
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