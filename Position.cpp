//
// Created by Gabriele Preti on 09/03/25.
//

#include "Position.h"

Position::Position() { //inizializzazione della posizione iniziale del serpente
    int j = (cols - 1)/2 - snake_length/2; //punto di partenza per posizionare serpente al centro della matrice
    for (int i = 0; i < snake_length; i++) { //ciclo inizializzazione coordinate //stessa riga, colonne diverse
        coord[i][0] = (rows - 1)/2;
        coord[i][1] = j;
        j++; //incremento della colonna
    }
}

void Position::debug() {
    for (int i = 0; i < snake_length; i++) {
        cout << "( "<< coord[i][0] << " : ";
        cout << coord[i][1] << " )" << endl;
    }
}
void Position::Shift() {
    for (int i = snake_length-1; i > 0; i--) { //ciclo che sposta verso destra le coordinate di ogni segmento
        coord[i][0]= coord[i-1][0];
        coord[i][1] = coord[i-1][1];
    }
    coord[0][0] = 0; //a [0][0] imposto 0
    coord[0][1] = 0; //a [0][1] imposto 0
                     //segmento in testa ha con coordinate (0, 0)
}

void Position::Push(int row_coord, int col_coord) {
    coord[0][0] = row_coord; //inserisce le coordinate della testa del serpente in testa all'array bidimensionale
    coord[0][1] = col_coord;
}

void Position::Pop() { //elimina la coda del serpente, inizializza la coordinata a zero
    coord[snake_length-1][0] = 0;
    coord[snake_length-1][1] = 0;
    Shift(); //sposta verso destra tutte le coordinate diverse da zero, lasciando libera la testa dell'array
}

bool Position::Dups() {
    for (int i = 0; i < snake_length - 1; i++) { //prende una coordinata dell'array
        for (int j = i + 1; j < snake_length; j++) { //controlla se è già presente
            if (coord[i][0] == coord[j][0] && coord[i][1] == coord[j][1]) {
                return true; //se è già presente ritorno true, quindi il serpente si è ucciso
            }
        }
    }
    return false; //altrimenti è ancora vivo
}

