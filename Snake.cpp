//
// Created by Gabriele Preti on 02/03/25.
//
#include "Snake.h"
#include <iostream>
using namespace std;

Snake::Snake() {
    xoff = 4;
    yoff = 6;
    get_terminal(xMax, yMax);
    snake_win = centered_win(rows + xoff, cols + yoff, xMax, yMax);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = false;
        }
    }
}
void Snake::display() {
    wclear(snake_win);
    box(snake_win, 0, 0);
    wrefresh(snake_win);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mvwprintw(snake_win, i+ (xoff)/2, j + (yoff)/2, "%d", matrix[i][j]);
        }
    }
    wrefresh(snake_win);
}