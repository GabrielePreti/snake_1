//
// Created by Gabriele Preti on 02/03/25.
//

#ifndef SNAKE_H
#define SNAKE_H
#include <ncurses.h>
#include <iostream>
#include "default_functions.h"
using namespace std;
#define rows 20
#define cols 30

class Snake {
protected:
    bool matrix[rows][cols];
    int xMax;
    int yMax;
    WINDOW* snake_win;
    int xoff;
    int yoff;

public:
    Snake();
    void display();

};



#endif //SNAKE_H