#ifndef SCREEN_H
#define SCREEN_H
#include <iostream>
#include <iomanip>

class Screen
{
public:
    static void clrscr();
#ifdef _WIN32
    static std::_Smanip<std::streamsize> space(int size = 60);
#else
    static std::_Setw space(int size = 60);
#endif
};

#endif