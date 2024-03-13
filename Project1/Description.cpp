#include "apis.h"
#include "Product.h"
#include "ProductCart.h"
#include "Screen.h"
#include "Login.h"
#include "Homescreen.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void descripScreen(Product &data)
{
	Screen::clrscr();
	cout << userName << endl;
	cout << "\n\n\n\n\n\n\n";
	cout << Screen::space(62) << data.title << endl;
	cout << Screen::space(50) << data.description << "\n"
		 << endl;
	cout << Screen::space(60) << "Price: " << data.price << endl;
	cout << Screen::space(61) << "Rating: " << data.rating << endl;
	cout << Screen::space(67) << "Rating count: " << data.ratingCount << endl;
	cout << Screen::space(90) << "--------------------------------------------------------" << endl;

	int userChoice, Quantity;
	string Address;
	cout << Screen::space(70) << "To go back Enter 0:" << endl;
	cout << Screen::space(65) << "Buy Enter 1:\n";
	cin >> userChoice;

	if (userChoice == 1)
	{
		cout << "Enter the total quantity you want:\n";
		cin >> Quantity;
		cout << endl;
		cout << "Enter your Address:\n";
		cin >> Address;

		ProductCart cart(data, Quantity, userId, Address, userName);
		if (orderFood(cart))
		{
			Screen::clrscr();
			cout << "Error occured while ordering item" << endl;
		}
		else
		{
			Screen::clrscr();
			cout << "\n\n\n";
			cout << Screen::space(20) << "Order placed successfully" << endl;
			homeScreen();
			cin.get();
		}
	}
	else
	{
		homeScreen();
	}
}