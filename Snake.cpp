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
    keypad(snake_win, TRUE);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = false;
        }
    }
    point.headr = rows/2 + 1;
    point.tailr = rows/2 + 1;
    point.headc = cols/2;
    point.tailc = 0;

    for (int k = point.headc; k < point.headc + snake_length; k++) {
        matrix[point.headr][k] = true;
        point.tailc = k;
    }
}
void Snake::position() {
    cout << "HEAD: " << point.headr << " " << point.headc << endl;
    cout << "TAIL: " << point.tailr << " " << point.tailc << endl;

    mvprintw(0,0,"%d", point.headr + 1);
    mvprintw(4,0,"%d", point.headc + 1);
    mvprintw(8,0,"%d", point.tailr + 1);
    mvprintw(12,0,"%d", point.tailc + 1);
}

void Snake::display() {
    //wclear(snake_win);
    box(snake_win, 0, 0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == true) {
                wattron(snake_win, A_REVERSE);
            }
            mvwprintw(snake_win, i+ (xoff)/2, j + (yoff)/2, "%d", matrix[i][j]);
            wattroff(snake_win, A_REVERSE);
        }
    }
    wrefresh(snake_win);
}

void Snake::move() {
    nodelay(snake_win, TRUE);
    int direction = 1;
    bool end = false;

    while (end != true) {
        int ch = wgetch(snake_win);
        if (ch == 16) {
            end = true;
            mvprintw(0, 0, "%s", "PAUSA");
            refresh();
        }
        else {
            if (ch != ERR){
                switch (ch) {
                    case KEY_UP:
                        if (direction != -1) {
                            direction = 1;
                        }
                    break;
                    case KEY_DOWN:
                        if (direction != 1) {
                            direction = -1;
                        }
                    break;
                    case KEY_LEFT:
                        if (direction != 3) {
                            direction = 2;
                        }
                    break;
                    case KEY_RIGHT:
                        if (direction != 2) {
                            direction = 3;
                        }
                    break;
                    default:
                        break;
                }
            }
            switch (direction) {
                case 1:
                    matrix[point.tailr][point.tailc] = false;
                    if (point.headc == point.tailc) {
                        point.headr--;
                    }
                    else {
                        point.tailc--;
                        point.headr--;
                    }
                    matrix[point.headr][point.headc] = true;
                break;
                case -1:
                    matrix[point.tailr][point.tailc] = false;
                    point.tailc--;
                    point.headr++;
                    matrix[point.headr][point.headc] = true;
                break;
                case 2:
                    break;
                case 3:
                    break;
                default:
                    break;
            }
            Snake::display();
            napms(700);
        }
    }
}