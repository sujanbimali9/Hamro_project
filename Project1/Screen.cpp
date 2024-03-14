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

#ifdef _WIN32
std::_Smanip<std::streamsize> Screen::space(int size)
{
    return std::setw(size);
}
#else
std::_Setw Screen::space(int size)
{
    return std::setw(size);
}
#endif