#include <iostream>
#include "Product.h"
#include <vector>
#include<string>
#include"Screen.h"
#include"apis.h"

using namespace std;

void homeScreen() {
	Screen::clrscr();
	vector<Product> product;
	try { 
		if (getData(product)) { throw 1; }
		else
		{
			int length = product.size() >= 10 ? 10 : product.size();
			for (int i = 0; i < length; ++i) {
				cout<< i + 1 << ". " << product[i].title << endl;
				cout<< "Price: " << product[i].price << endl;
				cout<< "Rating: " << product[i].rating << endl;
				cout<< "-----------------------------------" << endl;

			}

		}
	}
	catch (...) {

	}

	
}