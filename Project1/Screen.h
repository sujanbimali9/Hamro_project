#ifndef SCREEN_H
#define SCREEN_H
#include <iostream>
#include <iomanip>

class Screen
{
public:
    static void clrscr();
    static std::string space(int size = 60);
};

#endif