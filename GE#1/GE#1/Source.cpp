/*
* Name: Kevin Conde, Ethan Thompson
* Assignment: Group Exercise #1
* Date: 8/22/25
*/

#include <iostream>
#include <string>
using namespace std;

struct {
	string className;
	int students;
	double average;
	string sName[100];
	int grades[100];
	int minScore;
	int maxScore;
}p1;

int main()
{
	//Variables
	int score;
	int sum = 0;

	cout << "Enter a class name: ";
	getline(cin, p1.className);

	cout << "Enter the number of students: ";
	cin >> p1.students;

	p1.maxScore = 0;
	p1.minScore = 100;

	for (int i = 0; i < p1.students; i++)
	{
		cin.ignore(); // Keeps the loop from skipping questions
		cout << "Enter student name: ";
		getline(cin, p1.sName[i]);
		cout << "Enter student grade(number): ";
		cin >> p1.grades[i];
		sum += p1.grades[i];
		if (p1.grades[i] > p1.maxScore)
		{
			p1.maxScore = p1.grades[i];
		}
		if (p1.grades[i] < p1.minScore)
		{
			p1.minScore = p1.grades[i];
		}
	}

	p1.average = sum / p1.students;

	//p1.minScore = numeric_limits<int>::max();
	//p1.maxScore = numeric_limits<int>::min();

	//Display the results
	cout << "\nClass Name: " << p1.className << endl;
	cout << "\nNumber of Students: " << p1.students << endl;
	cout << "\nAverage grade score: " << p1.average << endl;
	cout << "\nTop score: " << p1.maxScore << endl;
	cout << "\nLowest score: " << p1.minScore << endl;

	system("pause");
	return 0;
}