#include "clear.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

void Screen::clrscr()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
};
