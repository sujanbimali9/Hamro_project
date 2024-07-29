#include "ProductCart.h"
#include "Screen.h"
#include "apis.h"
#include "HomeScreen.h"
#include "Login.h"

#include <fmt/color.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void cartScreen()
{
	Screen::clrscr();
	vector<ProductCart> productCart;
	try
	{
		if (getCart(user.getUserId(), productCart))
		{
			throw 1;
		}
		else
		{
			fmt::print(fg(fmt::color::sea_green) | fmt::emphasis::bold, "{}My Orders\n", Screen::space(62));

			for (int i = 0; i < productCart.size(); i++)
			{
				cout << Screen::space(57) << i + 1 << ". " << productCart[i].title << endl;
				cout << Screen::space() << "Quantity: " << productCart[i].quantity << endl;
				cout << Screen::space() << "Price per item: " << productCart[i].price << endl;
				cout << Screen::space() << "Address: " << productCart[i].location << endl;
				cout << Screen::space() << "Total Price: " << productCart[i].price * productCart[i].quantity << endl;
				cout << Screen::space(48) << string(40, '-') << endl;
			}
			cout << "\n\n"
				 << Screen::space(56) << "enter 1 to return to homescreen" << endl;

			int choice;
			while (!(cin >> choice) || (choice != 1))
			{
				cout << "Invalid input" << endl;
				cin.clear();
				cin.ignore(100, '\n');
			}
			if (choice == 1)
			{
				homeScreen();
			}
		}
	}
	catch (string error)
	{
		cerr << error << endl;
	}
	catch (...)
	{
		cerr << "error in getting cart" << endl;
	}
}
