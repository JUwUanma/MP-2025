#ifndef _TABLERO_H_
#define _TABLERO_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../ModuloMemoria/Datos.h"

#define MAX_RANDOM_TRIES 300

//enum para bool en C
enum bool {false, true};

//Motes para elegir tableros
enum motesTableros {FLOTA, OPONENTE};

//Orientación de colocación de barcos en tablero. Grados en eje cartesiano habitual. Nomenclatura: G(grado)
enum orientacion {G0, G45, G90, G135, G180, G225, G270, G315};

//Dirección de rotación -> rotar()
enum direccion {IZQUIERDA, DERECHA};

/*P: n > 0
Q: Salta n número de líneas
*/
inline void jump(int n);

//Devuelve 1 si se ha respondido Y o y
//Devuelve 0 si se ha respondido N o n
//Vuelve a preguntar hasta que se hayan introducido alguno de esos valores
int respuesta(char c);

/*P: filas > 0, columnas > 0;
Q: Crea un tablero vacío (' ') de un nº indicado de filas y columnas*/
Tablero* crearTablero(int maxLado);

/*P: N/A
Q: Muestra por pantalla la flota del Jugador indicado*/
void mostrarFlota(Jugador* j);

/*P: N/A
Q: Muestra por pantalla el Tablero oponente del Jugador indicado*/
void mostrarOponente(Jugador* j);

/*P: N/A
Q: Accede al menú para colocar los barcos de manera manual en el Tablero flota*/
void colocarManual(Jugador* j, Vector_Barcos vect);

/*P: N/A
Q: Genera un mapa de barcos aleatorio en el Tablero flota*/
void colocarAleatorio(Jugador* j);

/*UTILIZAR SOLO PARA OPERACIONES FUERA DEL JUEGO -> registrarDisparo()
P: Existe el tablero T. 0 <= x,y < maxLado
Q: Coloca en la casilla [x,y] del jugador j del tablero indicado el caracter introducido. 
Devuelve 1 si se ha colocado correctamente, 0 sino.
ENUM: FLOTA(0) OPONENTE(1)*/
int colocarCasilla(char c, Tablero* T, int x, int y);

/*P: Tablero creado, caracter válido, nCasillas, x, y dentro de tablero
Q: Rellena nCasillas del tablero T con el caracter c desde la casilla x, y con orientacion orient*/
void rellenarCasillas(Tablero* T, char c, int nCasillas, int orient, int x, int y);

/*P: Existe el tablero T. 0 <= x,y < maxLado
Q: Devuelve lo que hay en la casilla [x,y] del jugador j del tablero indicado
ENUM: FLOTA(0) OPONENTE(1)*/
char devolverCasilla(Tablero* T, int x, int y);

/*P: Tablero T creado, nCasilas > 0, x, y e orient válidos
Q: Pone a vacío nCasillas, desde x e y en el tablero T en la orientacion indicada
*/
void vaciarEspacio(Tablero* T, int nCasillas, int orient, int x, int y);

/*P: Tablero T creado
Q: Devuelve 1 si la casilla x, y está dentro del tablero y está libre (' ') y 0 si está ocupada
*/
int verificarCasilla(Tablero* T, int x, int y);

/*P: Tablero T creado, Barco B existente, orientación válida -> enum: orientacion [0, 7], x,y pertenece a tablero
Q: Devuelve 1 si el barco B cabe en el tablero T con la orientación indicada desde x,y.
*/
int verificarEspacio(Tablero * T, Barco B, int orientacion, int x, int y);

/*P: Tablero T creado
Q: Devuelve por referencia las primeras coordenadas libres A PARTIR de las coordenadas x,y iniciales.
Si no hubiera devuelve [-1,-1]*/
void devolverCoordenadasLibres(Tablero* T, int x, int y);

/*P: Tablero T creado, [x,y] dentro del tablero (No hace falta que sus alrededores también)
Q: En el tablero T, coloca alrededor de la posición [x,y] el caracter "charToPlace" y machaca
los demás EXCEPTO charToIgnore. Si por ejemplo queremos colocar un barco, utilizaremos para
cada casilla (T, x, y, 'X', '0'), siendo X el barco y 0 el carácter de ocupación.*/
void colocarAdyacentes(Tablero* T, int x, int y, char charToIgnore, char charToPlace);

//P: orientacion válida -> enum orientacion.
//Q: Mueve la coordenada x, y una casilla a la orientación indicada.
void moverAOrientacion(Tablero* T, int orientacion, int* x, int* y);

/*P: orientBase y grados válida -> enum orientacion. dirección válida -> enum direccion
Q: Rota orientBase los grados indicados a la dirección indicada. Da la vuelta si lo necesita.*/
void rotar(int* orientBase, int grados, int direccion);

#endif //_TABLERO_H_
