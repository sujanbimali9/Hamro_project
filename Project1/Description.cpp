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
	cout << Screen::space(63) << data.title << endl;
	cout << Screen::space(30)<<' ' << data.description << endl;
	cout << Screen::space(60) << "Price: " << data.price << endl;
	cout << Screen::space(61) << "Rating: " << data.rating << endl;
	cout << Screen::space(67) << "Rating count: " << data.ratingCount << endl;
	cout << Screen::space(90) << "--------------------------------------------------------" << endl;

	int userChoice, Quantity;
	string Address;
	cout <<endl<< Screen::space(70) << "To go back Enter 0:" << endl;
	cout << Screen::space(67) << "Buy Enter 1:\n";
	cin >> userChoice;

	if (userChoice == 1)
	{
		cout << "Enter the total quantity you want:\n";
		cin >> Quantity;
		cout << endl;
		cout << "Enter your Address:\n";
		cin >> Address;

		ProductCart cart(data, Quantity, userId, Address, userName);
		try {
			orderFood(cart);
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