#include "ProductCart.h"
#include"Screen.h"
#include"apis.h"
#include "Homescreen.h"
#include "Login.h"

#include <iostream>
#include <vector>
#include<string>


using namespace std;

void cartScreen() {
	Screen::clrscr();
	vector<ProductCart> productCart;
	try {
		if (getCart(userId, productCart)) { throw 1; }
		else
		{
			cout<< Screen::space(70) << "My Orders" << endl<<endl;

			for (int i = 0; i <productCart.size() ; i++) {
				cout << Screen::space(56) << i + 1 << ". " << productCart[i].title << endl;
				cout << Screen::space(68) << "Quantity: " << productCart[i].quantity << endl;
				cout << Screen::space(74) << "Price per item: " << productCart[i].price << endl;
				cout << Screen::space(67) << "Address: " << productCart[i].location << endl;
				cout << Screen::space(71) << "Total Price: " << productCart[i].price * productCart[i].quantity << endl;
				cout << Screen::space(71) << "Total Price: " << productCart[i].price  * productCart[i].quantity << endl;
				cout << Screen::space(89) << string(35,'-') << endl;
			}
			cout<<"\n\n" << Screen::space(87) << "enter 1 to return to homescreen" << endl;

			int choice;
			cin >> choice;
			if (choice == 1) {
				homeScreen();
			}
			else {
				cout << "invalid input" << endl;
			}
			cout << "press any key to continue   " << choice << endl;
		}
	}
	catch (string error) {
		cout<< error << endl;
	}
	catch (...) {
		cout << "error in getting cart" << endl;
	}
}

