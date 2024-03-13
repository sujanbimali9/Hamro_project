#include <iostream>
#include "Product.h"
#include "Screen.h"
#include "apis.h"
#include "Description.h"
#include "CartScreen.h"

#include <vector>
#include <string>

using namespace std;
void show(int screen, vector<Product> product);

void homeScreen()
{
	Screen::clrscr();
	vector<Product> product;
	try
	{
		if (getData(product))
		{
			throw 1;
		}
		else
		{
			show(0, product);
		}
	}
	catch (...)
	{
	}
}

void show(int screen, vector<Product> product)
{
	Screen::clrscr();
	int length = screen * 10 + product.size() % 10;
	if (length >= product.size())
	{
		length = product.size() - 1;
	}
	for (int i = screen * 10; i <= length; i++)
	{	
		cout << Screen::space(50) << i + 1 << ". " << product[i].title << endl;
		cout << Screen::space(59) << "Price: " << product[i].price << endl;
		cout << Screen::space() << "Rating: " << product[i].rating << endl;
		cout << Screen::space(90) << "-----------------------------------" << endl;
	}
	cout << "\n\n";
	cout << Screen::space(90) << "For more enter '0' and to go to cart enter '100'" << endl;
	cout << Screen::space(90) << "Enter the number of the product for more details" << endl;

	int choice;
	cin >> choice;
	if (choice == 0)
	{
		if ((screen + 1) * 10 < product.size())
		{
			screen++;
			show(screen, product);
		}
		else
		{
			screen = 0;
			show(screen, product);
		}
	}
	else if (choice == 100)
	{
		cartScreen();
	}
	else
	{
		if (choice >= product.size())
		{
			cout << "invalid input" << endl;
			show(screen, product);
		}
		else
		{
			descripScreen(product[choice - 1]);
		}
	}
	return;
}