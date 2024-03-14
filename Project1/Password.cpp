#include <iostream>
#include <string>

#ifdef _WIN32
#include <conio.h> // For _getch() function (Windows-specific)
#else
#include <termios.h>
#include <unistd.h>
#endif

// Function to read password without echoing characters to the console
std::string getPassword()
{
    std::string password;
    char ch;
#ifdef _WIN32
    while ((ch = _getch()) != '\r')
    { // Read characters until Enter key is pressed
        if (ch == '\b')
        { // Handle backspace
            if (!password.empty())
            {
                password.pop_back();  // Remove the last character from password
                std::cout << "\b \b"; // Move cursor back, print space, move cursor back again
            }
        }
        else
        {
            password.push_back(ch); // Append the character to password
            std::cout << '*';       // Print '*' instead of the actual character
        }
    }
    std::cout << std::endl; // New line after password input
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt); // Save current terminal attributes
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);        // Turn off canonical mode and echoing
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Apply new terminal attributes

    while ((ch = getchar()) != '\n')
    { // Read characters until Enter key is pressed
        if (ch == '\b')
        { // Handle backspace
            if (!password.empty())
            {
                password.pop_back();  // Remove the last character from password
                std::cout << "\b \b"; // Move cursor back, print space, move cursor back again
            }
        }
        else
        {
            password.push_back(ch); // Append the character to password
            std::cout << '*';       // Print '*' instead of the actual character
        }
    }
    std::cout << std::endl; // New line after password input

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old terminal attributes
#endif
    return password;
}
