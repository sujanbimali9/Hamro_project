#include <iostream>
#include "ProductCart.h"
#include"Screen.h"
#include"apis.h"
#include "Homescreen.h"

#include <vector>
#include<string>


using namespace std;
void showCart(int screen, vector<ProductCart> product);

void cartScreen() {
	Screen::clrscr();
	vector<ProductCart> productCart;
	try {
		if (getCart("12345", productCart)) { throw 1; }
		else
		{
			showCart(0, productCart);
		}
	}
	catch (...) {

	}
}

void showCart(int screen, vector<ProductCart> product) {
	int length = screen * 10 + product.size() % 10;
	if (length >= product.size()) {
		length = product.size() - 1;
	}
	for (int i = screen * 10; i < length; i++) {
		cout << Screen::space(40) << i + 1 << ". " << product[i].title << endl;
		cout << Screen::space() << "Quantity: " << product[i].quantity << endl;
		cout << Screen::space(49) << "Price per item: " << product[i].price << endl;
		cout << Screen::space(49) << "Address: " << product[i].location << endl;
		cout << Screen::space(49) << "Total Price: " << product[i].price-'0'* product[i].quantity << endl;

		cout << Screen::space(70) << "-----------------------------------" << endl;
	}
	cout << "enter 1 to return to homescreen" << endl;

	int choice;
	cin >> choice;
	if (choice == 1) {
		homeScreen();
	}
	else {
		cout<< "invalid input"<<endl;
	}
	cout << "press any key to continue   " << choice << endl;
	return;
}