#include "P1.h"
#include "P2.h"
#include "P3.h"
#include <iostream>
using namespace std;

int main()
{
	int choice;

	cout << "Enter choice 1-3";
	cin >> choice;
	switch (choice)
	{
	case 1: p1();
		break;
	case 2: p2();
		break;
	case 3: p3();
		break;
	}
	

	system("pause");
	return 0;
}