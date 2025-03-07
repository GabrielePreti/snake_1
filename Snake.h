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
#define snake_length 3

class Snake {
protected:
    bool matrix[rows][cols];
    int xMax;
    int yMax;
    WINDOW* snake_win;
    int xoff;
    int yoff;

    struct index {
        int headr;
        int headc;
        int tailr;
        int tailc;
    };
    index point;

public:
    Snake();
    void position();
    void display();
    void move();
};



#endif //SNAKE_H