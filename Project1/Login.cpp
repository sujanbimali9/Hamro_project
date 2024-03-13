#include "Homescreen.h"
#include "Screen.h"
#include<string>
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<ctime> 
#include "Description.h"


using namespace std;

string userId;
string userName;

void loginDialog();
void Signup();
void Exit();
bool checkCredentials(const string& username, const string& password);

string generateUserId() {
    time_t currentTime = time(nullptr); // Get the current time
    return to_string(currentTime); // Convert time to string and return
}


int main() {
    Screen::clrscr();;
    int value;
    cout << "Please sign up or login" << endl;
    cout << "Enter 1 for sign up, 2 for login, and 3 for exit: " << endl;

    cin >> value;

    if (value == 1) {
        Signup();
    }
    else if (value == 2) {
        loginDialog();
    }
    else if (value == 3) {
        Exit();
    }
    else {
        cout << "Please enter a valid number." << endl;
    }

    return 0;
}

void loginDialog() {
    string username, password;

    cout << "Enter username: ";
    cin >> username;
    userName = username;

    cout << "Enter password: ";
    cin >> password;
    if (checkCredentials(username, password)) {
        cout << "Login successful." << endl;
        cout << "Press any key to continue..." << endl;
        cin.get();
        descripScreen();
        
   
    }
    else {
        cout << "Invalid username or password. Please try again." << endl;
    }
}

void Signup() {
    string username, password;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    userName = username;
    userId = generateUserId();

    ofstream outfile("user_data.txt", ios::app);

    if (outfile.is_open()) {
        outfile<<userId<< username << " " << password << endl;
        cout << "Signup successful. User data stored in 'user_data.txt'." << endl;
        outfile.close();
        homeScreen();
    }
    else {
        cerr << "Error opening the file." << endl;
    }
    cout << "\n" << endl;
    cout << "\n" << endl;


}

void Exit() {
    cout << "Exit here" << endl;
}

bool checkCredentials(const string& username, const string& password) {
    string storedUsername, storedPassword,id;
    ifstream infile("user_data.txt");

    if (infile.is_open()) {
        while (infile >>id>> storedUsername >> storedPassword) {
            if (storedUsername == username && storedPassword == password) {
                userId = id;
                infile.close();
                return true;
            }
        }

        infile.close();
    }

    return false;
}
