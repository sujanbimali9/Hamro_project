#include "HomeScreen.h"
#include "Screen.h"
#include "Password.h"
#include "apis.h"
#include "User.h"

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <functional>

using namespace std;

User user;
void loginDialog();
void Signup();
bool checkCredentials(const string &email, const string &password);
int hashPassword(string password);

int generateUserId()
{
    time_t currentTime = time(nullptr);
    std::stringstream ss;
    ss << currentTime;
    return std::stoi(ss.str());
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

    cout << "Enter email: ";
    while (!(cin >> username))
    {
        cout << "Invalid input" << endl;
        cin.clear();
        cin.ignore(100, '\n');
    };
    cout << "Enter password: ";
    echo(false);
    cin >> password;
    echo(true);
    try
    {
        if (checkCredentials(username, password))
        {
            cout << "Login successful." << endl;
            cout << "Press any key to continue..." << endl;
            homeScreen();
            cout << user.getName() << endl;
            cout << user.getEmail() << endl;
            cout << user.getUserId() << endl;
            cout << "password: " << endl;
        }
        else
        {
            Screen::clrscr();
            cout << "\nInvalid username or password. Please try again." << endl;
            cout << "\n\n";
            cin.get();
            loginDialog();
        }
    }
    catch (string &e)
    {
        Screen::clrscr();
        cout << e << endl;
        cin.get();
        loginDialog();
    }
}

void Signup()
{
    string email, password, username;

    cout << "Enter email: ";
    cin >> email;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    echo(false);
    cin >> password;
    echo(true);
    cout << endl;
    cout << "comfirm password: ";
    echo(false);
    string compassword;
    cin >> compassword;
    echo(true);
    if (compassword != password)
    {
        cout << "password not matched" << endl;
        Signup();
    }
    else
    {
        try
        {
            bool loggedin = false;
            try
            {
                loggedin = checkCredentials(email, password);
            }
            catch (string &e)
            {
            }

            if (loggedin)
            {
                Screen::clrscr();
                cout << "User already exists. Please login." << endl;
                loginDialog();
            }
            else
            {
                user.setEmail(email);
                user.setUsername(username);
                user.setPassword(hashPassword(password));
                user.setUserId(generateUserId());

                if (!signup(user))
                {
                    cout << "signed up successfully." << endl;
                    cout << "Press any key to continue..." << endl;
                    cin.get();
                    homeScreen();
                }
                else
                {
                    cout << "User registration failed. Please try again." << endl;
                    cin.get();
                    Signup();
                }
            }
        }

        catch (string &e)
        {
            Screen::clrscr();
            if (e == "Invalid login credentials")
            {
                cout << "Invalid email address or password" << endl;
            }
            else
            {
                cout << e << endl;
            }
            Signup();
        }
        cout << endl;
        cout << endl;
    }
}

bool checkCredentials(const string &email, const string &password)
{
    string storedUsername, storedPassword, id;

    user.setEmail(email);
    user.setPassword(hashPassword(password));

    try
    {
        return !login(user);
    }
    catch (string &e)
    {
        throw e;
        return false;
    }
}

int hashPassword(string password)
{
    std::hash<std::string> hasher;
    return static_cast<unsigned int>(hasher(password));
}