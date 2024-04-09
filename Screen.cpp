#include "Screen.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif
#include <iomanip>

void Screen::clrscr()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
};

std::string Screen::space(int size)
{
    return std::string(size, ' ');
}