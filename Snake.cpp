//
// Created by Gabriele Preti on 02/03/25.
//
#include "Snake.h"
#include <iostream>
using namespace std;

Snake::Snake() : Position::Position(){
    xoff = 4; //offset impostati e definiti (da non cambiare) per centrare correttamente la finestra di visualizzazione
    yoff = 6; //del serpente
    get_terminal(xMax, yMax); //la funzione prende i due valori e assegna a questi valori la dimensione del terminale
    snake_win = centered_win(rows + xoff, cols + yoff, xMax, yMax); //creazione della finestra centrata
    keypad(snake_win, TRUE); //attivazione dell'input delle freccette
    for (int i = 0; i < rows; i++) { //imposta tutta la matrice booleana a 0/false
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = false;
        }
    }
    for (int k = 0; k < snake_length; k++) {
        matrix[coord[k][0]][coord[k][1]] = true;  //imposta le coordinate di riferimento della matrice booleana a true
                                                 //se tali coordinate solo inserite all'interno dell'array bidimensionale
                                                //definito in Position.h/Position.cpp
    }
    head_row = coord[0][0]; //copia delle coordinate della testa per lavorare più velocemente
    head_col = coord[0][1];
}
void Snake::position() { //debug
    for (int i = 0; i < snake_length; i++) {
        mvprintw(i + 2,2,"%d", coord[i][0]);
        mvprintw(i + 2,2,"%d", coord[i][1]);
    }
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
/*void Snake::display_good() {
    box(snake_win, 0, 0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == true) {
                wattron(snake_win, A_BOLD);
                mvwprintw(snake_win, i+ (xoff)/2, j + (yoff)/2, "%s", "@");
                wattroff(snake_win, A_BOLD);
            }
            else {
                mvwprintw(snake_win, i+ (xoff)/2, j + (yoff)/2, "%s", " ");
            }
        }
    }
    wrefresh(snake_win);
}*/

void Snake::offsegment() {//imposto le coordinate associate alla matrice che sono definite all'interno dell'array bidimensionale uguali a false
    matrix[coord[snake_length-1][0]][coord[snake_length-1][1]] = false;
    //ESEMPIO coord[0][0] = 1 e coord[0][1] = 2 ==> matrix[1][2] = 0/false
}
void Snake::onsegment() {//imposto le coordinate associate alla matrice che sono definite all'interno dell'array bidimensionale uguali a true
    matrix[coord[0][0]][coord[0][1]] = true;
    //ESEMPIO coord[0][0] = 1 e coord[0][1] = 2 ==> matrix[1][2] = 1/true
}

void Snake::moveup() {
    Snake::offsegment(); //spegno la coda --> Uguale per tutti i metodi
    Position::Pop(); //la rimuovo dall'array che gestisce i segmenti
    head_row = head_row - 1; //mi sposto verso l'alto, diminuisco le righe
    if (head_row < 0) {head_row = rows - 1; } //controllo sul bordo
    Position::Push(head_row, head_col); //inserisco nuova testa
    Snake::onsegment(); //riaccendo segmenti associato alla matrice
}
void Snake::movedown() {
    Snake::offsegment();
    Position::Pop();
    head_row = head_row + 1; //mi sposto verso il basso, aumento le righe
    if (head_row > rows - 1) {head_row = 0; } //controllo sul bordo
    Position::Push(head_row, head_col); //inserisco nuova testa
    Snake::onsegment(); //riaccendo segmenti associato alla matrice
}
void Snake::moveleft() {
    Snake::offsegment();
    Position::Pop();
    head_col = head_col - 1; //mi sposto verso sinistra, diminuisco le colonne
    if (head_col < 0) {head_col = cols - 1; }
    Position::Push(head_row, head_col);
    Snake::onsegment();
}
void Snake::moveright() {
    Snake::offsegment();
    Position::Pop();
    head_col = head_col + 1;  //mi sposto verso destra, aumento le colonne
    if (head_col > cols - 1) {head_col = 0; }
    Position::Push(head_row, head_col);
    Snake::onsegment();
}

void Snake::move() { //SU = 1; GIU = -1; SINISTRA = 2; DESTRA = 3
    curs_set(0); //nascondo il cursore
    halfdelay(5); //imposto un delay
    int direction = 2; //direzione di partenza
    bool end = false;
    while (end != true) {
        int ch = wgetch(snake_win); //prendo il carattere dalla finestra
        if (Position::Dups() == true) { //prima controlla la presenza di duplicati
            end = true;
            mvprintw(0, 0, "%s", "MORTO! - SERPENTE SI E' MORSO"); //se ci sono, allora il serpente si è morso
            refresh();
        }
        else if (ch == 16) { //control + p
            end = true;
            mvprintw(0, 0, "%s", "PAUSA");
            refresh();
        }
        else {
            if (ch != ERR) { //se il carattere viene premuto allora eseguo controlli sulla direzione
                switch (ch) { //direzione che non può essere opposta a quella attuale
                    case KEY_UP:
                        if (direction != -1){ direction = 1;}
                        break;
                    case KEY_DOWN:
                        if (direction != 1){ direction = -1;}
                        break;
                    case KEY_LEFT:
                        if (direction != 3){ direction = 2;}
                        break;
                    case KEY_RIGHT:
                        if (direction != 2){ direction = 3;}
                        break;
                    default:
                        break;
                }
            }

            switch (direction) {
                case 1:
                    moveup();
                    if (Position::Dups() == true) {end = true; mvprintw(0, 0, "%s", "MORTO! - SERPENTE SI E' MORSO");} //controllo sul morso
                    break;
                case -1:
                    movedown();
                    if (Position::Dups() == true) {end = true; mvprintw(0, 0, "%s", "MORTO! - SERPENTE SI E' MORSO");} //controllo sul morso
                    break;
                case 2:
                    moveleft();
                    if (Position::Dups() == true) {end = true; mvprintw(0, 0, "%s", "MORTO! - SERPENTE SI E' MORSO");} //controllo sul morso
                    break;
                case 3:
                    moveright();
                    if (Position::Dups() == true) {end = true; mvprintw(0, 0, "%s", "MORTO! - SERPENTE SI E' MORSO");} //controllo sul morso
                    break;
                default:
                    break;
            }
        }
        Snake::display(); //Visualizzazione, metodo che viene reimplementato dalla Grazia
        napms(200);
    }
}


