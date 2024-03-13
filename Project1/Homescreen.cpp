#include <iostream>
#include "Product.h"
#include <vector>
#include<string>
#include"Screen.h"
#include"apis.h"

using namespace std;
void show(int screen, vector<Product> product);

void homeScreen() {
	Screen::clrscr();
	vector<Product> product;
	try { 
		if (getData(product)) { throw 1; }
		else
		{
			ProductCart productCart(product[0],5,"1234","jhapa","sujan");
			orderFood(productCart);
		//show(0, product);
		}
	}
	catch (...) {

	}
}

void show(int screen, vector<Product> product) {
	int length = screen * 10 + product.size() % 10;
	if (length >= product.size()) {
		length = product.size() - 1;
	}
	for (int i = screen * 10; i < length; i++) {
		cout << Screen::space(40) << i + 1 << ". " << product[i].title << endl;
		cout << Screen::space(49) << "Price: " << product[i].price << endl;
		cout << Screen::space() << "Rating: " << product[i].rating << endl;
		cout << Screen::space(70) << "-----------------------------------" << endl;
	}
	cout << "for more enter '0'" << endl;
	cout << "enter the number of the product for more details" << endl;

	int choice;
	cin >> choice;
	if (choice == 0) {
		cout<<  product.size() << screen << endl;
		if ((screen+1) * 10 < product.size()) {
			screen++;
			show(screen, product);
		}
		else {
			screen = 0;
			show(screen, product);
		}
	}
	else {
		if (choice >= product.size())  cout << "invalid input";
	}
	cout<< "press any key to continue   "<<choice<<endl;
	return;
}