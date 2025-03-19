#ifndef LOGICA_H
#define LOGICA_H

#include <stdio.h>
#include <stdlib.h>

//Funciones:


//FUNCIONES DE VERIFICACI�N

//Precondici�n: Recibe la estructura rellena de ConfiguracionJuego [M�dulo Datos], y las posiciones ocupadas del barco(a�n por determinar)
//Postcondici�n: Devuelve un entero que indica si la posici�n del barco es v�lida o no. 1=V�lida 0=No v�lida
int verificar_barco(ConfiguracionJuego ConfiguracionJuego,"posiciones");


//Precondici�n: Recibe unas coordenadas x,y (expresadas como n�meros enteros) y la estructura del tablero[M�dulo de tableros]
//Postcondici�n: Devuelve un entero que indica si esa posici�n es v�lida
int verificar_posicion(int i, int j, Tablero t);



//FUNCIONES DE LOS DISPAROS [POSIBLE M�DULO APARTE SI SE NECESITAN FUTURAS FUNCIONES]

//Precondici�n: Recibe una estructura como puntero (Ya sea de J1 o J2)
//Postcondici�n:En funci�n del tipo de disparo del jugador, se modifica la estructura
//              si el disparo es tipo autom�tico, se ejecuta un algoritmo que realice el disparo
//              de lo contrario, el usuario introduce las coordenadas.
//NOTA: Esta funci�n puede cambiar, es decir, puede ser modificada de manera que haga los cambios y muestre
//      los resultados en pantalla, eliminando la siguiente funci�n a esta y a�adiendo sus argumentos.
void disparo(Jugador *j, Tablero *t);



//Precondici�n: Recibe las coordenadas del disparo, el puntero a estructura Tablero[Del m�dulo de tu mama]
//Postcondici�n: Modifica el resultado en el tablero.
void resultado_disparo(int i, int j, Tablero *t);


#endif //LOGICA_H
