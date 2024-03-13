#include "apis.h"
#include "Product.h"
#include "ProductCart.h"
#include "Screen.h"
#include "Login.h"
#include "Homescreen.h"


#include<iostream>
#include<string>
#include <vector>


using namespace std;

void descripScreen(	Product data)
{
	Screen::clrscr();
			cout << "\n\n\n\n\n\n\n";
		cout <<Screen::space(42)<< data.title << endl;
		cout <<Screen::space(10)<<"Food Description:\n"<<Screen::space(10)<<data.description<<"\n" << endl;
		cout << Screen::space(40) <<"Price: "<< data.price << endl;
		cout << Screen::space(41) <<"Rating: " << data.rating << endl;
		cout << Screen::space(47) << "Rating count: " << data.ratingCount << endl;
		cout << Screen::space() << "--------------------------------------------------------------------------------------------------------\n" << endl;

	
		cout << "\n\n\n\n";
		int userChoice,Quantity;
		string Address;
		cout << Screen::space()<< "To go back Enter 0:\n\n"<< Screen::space(44)<<"Buy Enter 1:\n";
		cin >> userChoice;

		if (userChoice == 1)
		{
			cout << "Enter the total quantity you want:\n";
			cin >> Quantity;
			cout << endl;
			cout << "Enter your Address:\n";
			cin >> Address;


			//ProductCart(, Quantity, "", Address, "");
		}	
		else {
			homeScreen();
		}


}