//
// Created by Gabriele Preti on 09/03/25.
//

#ifndef POSITION_H
#define POSITION_H

#include <iostream>
using namespace std;
#include "Constant.h"


class Position {
protected:
    int coord[snake_length][2]; //contiene le coordinate di ogni segmento del serpente
public:
    Position(); //Costruttore
    void debug(); //Funzione di Debug per visualizzare le coordinate di ogni segmento
    void Shift(); //sposta a destra di 1 posizione tutte le coordinate e lascia la coordinata in coord[0][0] impostata a (0, 0)
    void Push(int row_d, int col_d); //inserisce in coord[0][0] la coordinata della testa del serpente
    void Pop(); //rimuove dalla coda dell'array l'ultima coordinata dell'ultimo segmento del serpente
    bool Dups(); //Verifica se il serpente di è morso
};



#endif //POSITION_H
