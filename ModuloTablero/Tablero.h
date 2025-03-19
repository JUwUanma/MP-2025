#ifndef _TABLERO_H_
#define _TABLERO_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct{
            char** casillas; //?????????????????
            int xMax;
            int yMax;
}Tablero;


/*P: filas > 0, columnas > 0;
Q: Crea un tablero vacío (' ') de un nº indicado de filas y columnas*/
Tablero* crearTablero(int filas, int columnas);

/*P: N/A
Q: Muestra por pantalla la flota del Jugador indicado*/
void mostrarFlota(Jugador* j);

/*P: N/A
Q: Muestra por pantalla el Tablero oponente del Jugador indicado*/
void mostrarOponente(Jugador* j);

//MÉTODO PRIVADO: Muestra el Tablero indicado
static void mostrarTablero(Tablero* t);

/*P: N/A
Q: Accede al menú para colocar los barcos de manera manual en el Tablero flota*/
void colocarManual(Jugador* j);

/*P: N/A
Q: Genera un mapa de barcos aleatorio en el Tablero flota*/
void colocarAleatorio(Jugador* j);

#endif //_TABLERO_H_
