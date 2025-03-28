#ifndef LOGICA_H
#define LOGICA_H

#include <stdio.h>
#include <stdlib.h>
#include "Datos.h"
#include "Tablero.h"

//Funciones:



//FUNCIONES DE LOS DISPAROS [POSIBLE MÓDULO APARTE SI SE NECESITAN FUTURAS FUNCIONES]

//Precondición: Recibe una estructura como puntero (Ya sea de J1 o J2)
//Postcondición:En función del tipo de disparo del jugador, se modifica la estructura
//              si el disparo es tipo automático, se ejecuta un algoritmo que realice el disparo
//              de lo contrario, el usuario introduce las coordenadas.
//NOTA: Esta función puede cambiar, es decir, puede ser modificada de manera que haga los cambios y muestre
//      los resultados en pantalla, eliminando la siguiente función a esta y añadiendo sus argumentos. 
void disparo(Jugador *j, Tablero *t);



//Precondición: Recibe las coordenadas del disparo, el puntero a estructura Tablero[Del módulo de tu mama]
//Postcondición: Modifica el resultado en el tablero.
void resultado_disparo(int i, int j, Tablero *t);

//Pre: Ninguna
//Post: Función por defecto que reinicia el juego, prepara los tableros, carga los archivos y carga la configuración en la partida.
void reiniciarPartida();



void recorrer_barco();

//Nota el disparo automático no es tonto, va a disparar alrededor de su disparo si da en un barco



#endif //LOGICA_H