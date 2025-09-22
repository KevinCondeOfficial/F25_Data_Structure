/*
* Name: Kevin Conde
* Assignment: Quiz #3
* Date: 9/21/25
*/

#include <iostream>
#include <string>
#include <iomanip> // Allows for setfill to be used
using namespace std;

#pragma region Classes
class Item
{
	private:
		string name;
		double price;
	
	protected: //constructor to initialize name and price.
		Item(string n, double p) : name(n), price (p) {}
	
	public: //virutal methods
		virtual void display() const = 0;// Shows item info.
		virtual double getPrice() const { return price; }
		virtual void receiptEntry() const = 0;
		string getName() const { return name; }
		virtual ~Item() {}
};
	//Create two derived classes : FoodItem, ElectronicItem
class FoodItem : public Item
{
private: 
		string expirationDate;

public:
	//Constructor : takes name, price, and expiration date
	FoodItem(string n, double p, string exp):
		Item(n, p), expirationDate(exp) { }
	//Override methods :
	void display() const override //shows name, price, expiration date
	{
		cout << "Name: " << getName()
			<< " | Price: " << getPrice()
			<< " | Expires: " << expirationDate << endl;
	}
	double getPrice() const override
	{
		return Item::getPrice();
	}
	void receiptEntry() const override //shows name and price only
	{
		cout << getName() << " - $" << getPrice() << endl;
	}
};
class ElectronicItem : public Item
{
private: 
	int warrantyMonths;

public:
	//Constructor : takes name, price, and warranty duration
	ElectronicItem(string n, double p, int w) :
		Item(n, p), warrantyMonths(w) {}

	//Override methods : CMPS 385 : Data Structures Fall 2025
	void display() const override //shows name, price, expiration date
	{
		cout << "Name: " << getName()
			<< " | Price: " << getPrice()
			<< " | Warranty: " << warrantyMonths << "months\n";
	}
	double getPrice() const override
	{
		return Item::getPrice();
	}
	void receiptEntry() const override //shows name and price only
	{
		cout << getName() << " - $" << getPrice() << endl;
	}
};
#pragma endregion

int main()
{
#pragma region Variables
	const int MAX_STORE = 50;
	const int MAX_PURCHASES = 20;
	Item* store[MAX_STORE];
	Item* purchases[MAX_PURCHASES];
	int storeCount = 0;
	int purchaseCount = 0;
	int choice;
#pragma endregion
#pragma region Main Code
	cout << setfill('*');
	cout << right << setw(24) << "QuickMart" << left << setw(25) << " POS" << endl;

	do
	{
		cout << "Select one: \n";
		cout << "1) Add item to Store\n";
		cout << "2) Display available items\n";
		cout << "3) Buy item available items\n";
		cout << "4) View receipt\n";
		cout << "0) Exit\n";
		cout << "Choice: ";
		cin >> choice;

		switch (choice)
		{
		case 0:
			break;
		case 1:
		{
			string type, name, exp;
			double price;
			int warranty;

			cout << "Enter Item type (Food/Tech): ";
			cin >> type;
			cout << "Enter item name : ";
			cin >> name;
			cout << "Enter price: ";
			cin >> price;

			if (type == "Food")
			{
				cout << "Enter expiration date : ";
				cin >> exp;
				store[storeCount++] = new FoodItem(name, price, exp);
			}
			else
			{
				cout << "Enter warranty in months: ";
				cin >> warranty;
				store[storeCount++] = new ElectronicItem(name, price, warranty);
			}
			cout << "Item added successfully!\n";
		}break;
		case 2:
			for (int i = 0; i < storeCount; ++i)
			{
				store[i] -> display();
			}
			break;
		case 3:
		{
			string name;
			cout << "Enter item name: ";
			cin >> name;
			bool found = false;
			for (int i = 0; i < storeCount; ++i)
			{
				if (store[i]->getName() == name)
				{
					purchases[purchaseCount++] = store[i];
					cout << "Purchased " << name << " for $" <<
						store[i]->getPrice() << endl;
					found = true;
					break;
				}
			}
			if (!found) cout << "Item not found.\n";
		}break;
		case 4:
		{
			double total = 0;
			cout << "Reciept\n";
			for (int i = 0; i < purchaseCount; ++i)
			{
				purchases[i]->receiptEntry();
				total += purchases[i]->getPrice();
			}
			cout << "Total: $" << total << endl;
		}break;
		default:
			cout << "Invalid choice.\n";  break;
		}

	} while (choice != 0); //Do while repeats the instance at least once
	for (int i = 0; i < storeCount; ++i)
		delete store[i];
#pragma endregion
	system("pause");
	return 0;
}