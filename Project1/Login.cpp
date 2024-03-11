#include<iostream>
#include<fstream>
#include "ListData.h"
#include<Windows.h>

using namespace std;

void LoginDialog();
void Signup();
void Exit();
bool checkCredentials(const string& username, const string& password);

int main() {
    int value;
    system("cls");

    cout << "Please sign up or login" << endl;
    cout << "Enter 1 for sign up, 2 for login, and 3 for exit: " << endl;

    cin >> value;

    if (value == 1) {
        Signup();
    }
    else if (value == 2) {
        LoginDialog();
    }
    else if (value == 3) {
        Exit();
    }
    else {
        cout << "Please enter a valid number." << endl;
    }

    return 0;
}

void LoginDialog() {
    string username, password;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    if (checkCredentials(username, password)) {
        cout << "Login successful." << endl;
        ListData();
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

    ofstream outfile("user_data.txt", ios::app);

    if (outfile.is_open()) {
        outfile << username << " " << password << endl;
        cout << "Signup successful. User data stored in 'user_data.txt'." << endl;
        outfile.close();
    }
    else {
        cerr << "Error opening the file." << endl;
    }
    cout << "\n" << endl;
    cout << "\n" << endl;


    ListData();
}

void Exit() {
    cout << "Exit here" << endl;
}

bool checkCredentials(const string& username, const string& password) {
    string storedUsername, storedPassword;
    ifstream infile("user_data.txt");

    if (infile.is_open()) {
        while (infile >> storedUsername >> storedPassword) {
            if (storedUsername == username && storedPassword == password) {
                infile.close();
                return true;
            }
        }

        infile.close();
    }

    return false;
}