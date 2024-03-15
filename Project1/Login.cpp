#include "HomeScreen.h"
#include "Screen.h"
#include "Password.h"

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

string userId;
string userName;

void loginDialog();
void Signup();
bool checkCredentials(const string &username, const string &password);

string generateUserId()
{
    time_t currentTime = time(nullptr);
    return to_string(currentTime);
}

int main()
{
    Screen::clrscr();

    int value;
    cout << "Please sign up or login" << endl;
    cout << "\nEnter 1 for sign up 2 for login 3 for exit: " << endl;

    while (!(cin >> value) || (value != 1 && value != 2 && value != 3))
    {
        cout << "Invalid input" << endl;
        cin.clear();
        cin.ignore(100, '\n');
    };
    if (value == 1)
    {
        Signup();
    }
    else if (value == 2)
    {
        loginDialog();
    }
    else
    {
        exit(0);
    }

    return 0;
}

void loginDialog()
{
    string username, password;

    cout << "Enter username: ";
    while (!(cin >> username))
    {
        cout << "Invalid input" << endl;
        cin.clear();
        cin.ignore(100, '\n');
    };
    userName = username;
    cout << "Enter password: ";
    echo(false);
    cin >> password;
    echo(true);
    if (checkCredentials(username, password))
    {
        cout << "Login successful." << endl;
        cout << "Press any key to continue..." << endl;
        cin.get();
        homeScreen();
    }
    else
    {
        cout << "\nInvalid username or password. Please try again." << endl;
        cout << "\n\n";
        cin.get();
        loginDialog();
    }
}

void Signup()
{
    string username, password;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    echo(false);
    cin >> password;
    echo(true);
    cout << endl;
    userName = username;
    userId = generateUserId();
    if (checkCredentials(username, password))
    {
        cout << "User already exists. Please login." << endl;
        loginDialog();
    }
    else
    {
        cout << "comfirm password: ";
        echo(false);
        string conpassword;
        cin >> conpassword;
        echo(true);
        if (conpassword != password)
        {
            cout << "password not matched" << endl;
            Signup();
        }
        ofstream outfile("user_data.txt", ios::app);

        if (outfile.is_open())
        {
            outfile << userId << " " << username << " " << password << endl;
            cout << "Signup successful. User data stored in 'user_data.txt'." << endl;
            outfile.close();
            homeScreen();
        }
        else
        {
            cerr << "Error opening the file." << endl;
        }
    }
    cout << endl;
    cout << endl;
}

bool checkCredentials(const string &username, const string &password)
{
    string storedUsername, storedPassword, id;
    ifstream infile("user_data.txt");

    if (infile.is_open())
    {
        while (infile >> id >> storedUsername >> storedPassword)
        {
            if (storedUsername == username && storedPassword == password)
            {
                userId = id;
                infile.close();
                return true;
            }
        }
        infile.close();
    }

    return false;
}