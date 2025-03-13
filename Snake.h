//
// Created by Gabriele Preti on 02/03/25.
//

#ifndef SNAKE_H
#define SNAKE_H
#include <ncurses.h>
#include <iostream>
#include "default_functions.h"
#include "Position.h"
using namespace std;
#include "Constant.h"

class Snake : public Position {
protected:
    bool matrix[rows][cols]; //matrice booleana
    int xMax; //Larghezza massima terminale
    int yMax;//Altezza massima terminale
    WINDOW* snake_win; //finestra per visualizzare posizione del serpente
    int xoff; //offset di coordinata X per centrare matrice booleana nella finestra
    int yoff; //offset di coordinata Y per centrare matrice booleana nella finestra

    int head_row; //Coordinata della testa del serpente --> Corrisponde a coord[0][0] in Position.h /Position.cpp
    int head_col; //coordinata della testa del serpente --> Corrisponde a coord[0][1] in Position.h /Position.cpp


public:
    Snake(); //Costruttore
    void position(); //Debug
    void display(); //Visualizzazione del movimento del serpente in una matrice booleana
    //void display_good(); //Visualizzazione Alternativa --> È tutta commentata, si può eliminare volendo
    void offsegment(); //imposta uguale a true la coordinata della matrice booleana corrispondente a quella salvata nell'array bidimensionale in Position.h /Position.cpp
    void onsegment(); //imposta uguale a false la coordinata della matrice booleana corrispondente a quella salvata nell'array bidimensionale in Position.h /Position.cpp
    void move(); //aggiorna le coordinate del serpente, accendendo e spegnendo ogni coordinata della matrice booleana di riferimento
    void moveup();
    void movedown();
    void moveleft();
    void moveright();
};



#endif //SNAKE_H