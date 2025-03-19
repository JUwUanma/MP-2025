#ifndef LOGICA_H
#define LOGICA_H

#include <stdio.h>
#include <stdlib.h>

//Funciones:


//FUNCIONES DE VERIFICACIÓN

//Precondición: Recibe la estructura rellena de ConfiguracionJuego [Módulo Datos], y las posiciones ocupadas del barco(aún por determinar)
//Postcondición: Devuelve un entero que indica si la posición del barco es válida o no. 1=Válida 0=No válida
int verificar_barco(ConfiguracionJuego ConfiguracionJuego,"posiciones");


//Precondición: Recibe unas coordenadas x,y (expresadas como números enteros) y la estructura del tablero[Módulo de tableros]
//Postcondición: Devuelve un entero que indica si esa posición es válida
int verificar_posicion(int i, int j, Tablero t);



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


#endif //LOGICA_H
