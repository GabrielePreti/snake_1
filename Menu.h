//
// Created by Gabriele Preti on 07/03/25.
//

#ifndef MENU_H
#define MENU_H
#include <iostream>
using namespace std;
#include <ncurses.h>
#include <string>
#include "default_functions.h"


class Menu {
protected:
    std::string options[2];
    int pointing;
    WINDOW *menu_win;
public:
    Menu();
    int Navigate();

};



#endif //MENU_H
