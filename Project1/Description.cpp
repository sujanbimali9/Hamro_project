#include "apis.h"
#include "Product.h"
#include "ProductCart.h"
#include "Screen.h"
#include "Login.h"
#include "HomeScreen.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void descripScreen(Product &data)
{
	Screen::clrscr();
	cout << "\n\n\n\n\n\n";
	cout << Screen::space(62) << data.title << endl;
	cout << Screen::space(30) << ' ' << data.description << endl;
	cout << Screen::space(60) << "Price: " << data.price << endl;
	cout << Screen::space(61) << "Rating: " << data.rating << endl;
	cout << Screen::space(67) << "Rating count: " << data.ratingCount << endl;
	cout << Screen::space(90) << "--------------------------------------------------------" << endl;

	int userChoice, Quantity;
	string Address;
	cout << endl;
	cout << Screen::space(70) << "To go back Enter 0:" << endl;
	cout << Screen::space(67) << "Buy Enter 1:\n";
	while (!(cin >> userChoice) || (userChoice != 0 && userChoice != 1))
	{
		cout << "Invalid input" << endl;
		cin.clear();
		cin.ignore(100, '\n');
	};

	if (userChoice == 1)
	{
		cout << "Enter the total quantity you want:\n";
		while (!(cin >> Quantity) || (Quantity < 0 || Quantity > 100))
		{
			cout << "invalid input" << endl;
			if (Quantity < 0)
			{
				cout << "Quantity cannot be negative" << endl;
			}
			else if (Quantity > 100)
			{
				cout << "Quantity cannot be more than 100" << endl;
			}
			cin.clear();
			cin.ignore(100, '\n');
		}
		cout << endl;
		cout << "Enter your Address:\n";
		while (!(cin >> Address))
		{
			cout << "Invalid input" << endl;
			cin.clear();
			cin.ignore(100, '\n');
		}

		ProductCart cart(data, Quantity, userId, Address, userName);
		try
		{
			orderFood(cart);
			Screen::clrscr();
			cout << Screen::space(20) << "Order placed successfully" << endl;
			cin.get();
			homeScreen();
		}
		catch (string error)
		{
			Screen::clrscr();
			cout << Screen::space(20) << error << endl;
			cin.get();
			homeScreen();
		}
		catch (...)
		{
			Screen::clrscr();
			cout << Screen::space(20) << "Error occured " << endl;
			cin.get();
			homeScreen();
		}
	}
	else
	{
		homeScreen();
	}
}