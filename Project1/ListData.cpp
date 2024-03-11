#include <iostream>
#include <fstream>
#include "ListData.h"

using namespace std;

void ListData() {
    string storedUsername, storedPassword;
    ifstream infile("user_data.txt");

    cout << "User data in 'user_data.txt':" << endl;
    if (infile.is_open()) {
        while (infile >> storedUsername >> storedPassword) {
            cout << "Username: " << storedUsername << ", Password: " << storedPassword << endl;
        }

        infile.close();
    }
    else {
        cerr << "Error opening the file." << endl;
    }
}
