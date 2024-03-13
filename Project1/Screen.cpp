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
  std::_Smanip<std::streamsize> Screen::space(int size=10) {
     return std::setw(size);
 }
