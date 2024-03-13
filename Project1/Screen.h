#ifndef SCREEN_H
#define SCREEN_H
#include <iostream>
#include <iomanip>


class Screen
{
public:
    static void clrscr();
    static std::_Smanip<std::streamsize>  space(int size = 10);
};

#endif