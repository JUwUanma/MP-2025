#ifndef LOGICA_H
#define LOGICA_H

#include <stdio.h>
#include <stdlib.h>
#include "..\\ModuloMemoria\Datos.h"
#include "..\\ModuloTablero\Tablero.h"


enum TIPO_DISPARO {AGUA, TOCADO, HUNDIDO};

//Funciones:



//FUNCIONES DE LOS DISPAROS [POSIBLE MÓDULO APARTE SI SE NECESITAN FUTURAS FUNCIONES]

//Precondición: Recibe una estructura como puntero (Ya sea de J1 o J2)
//Postcondición:En función del tipo de disparo del jugador, se modifica la estructura
//              si el disparo es tipo automático, se ejecuta un algoritmo que realice el disparo
//              de lo contrario, el usuario introduce las coordenadas.
//NOTA: Esta función puede cambiar, es decir, puede ser modificada de manera que haga los cambios y muestre
//      los resultados en pantalla, eliminando la siguiente función a esta y añadiendo sus argumentos. 

typedef struct{
    int x_maq, y_maq; 
    int orient_maq;
    int flagEncontrado_maq;
}Registro_Maquina;

void disparo_menu(Jugador *j, Tablero *t, Registro_Maquina *reg_maq);
void disparo_aleatorio(Tablero *t, Registro_Maquina *reg_maq);
int disparo(Tablero *T, int *xmaq, int *ymaq);
//Precondición: Recibe las coordenadas del disparo, el puntero a estructura Tablero[Del módulo de tu mama]
//Postcondición: Modifica el resultado en el tablero.
//void resultado_disparo(int i, int j, Tablero *t);

//Pre: Ninguna
//Post: Función por defecto que reinicia el juego, prepara los tableros, carga los archivos y carga la configuración en la partida.
void reiniciarPartida();


void continuarPartida();

/*Precondición: Recibe un puntero a estructura de un jugador, el vector de barcos cargado y la elección del jugador
Postcondición: Ejecuta la acción de colocar barcos en función del modo escogido*/
void f_eleccion_barcos(Jugador *pj, Vector_Barcos vectBarcos, char eleccion_barco);


void turno(Jugador *j, int *opcion_salir, Registro_Maquina *reg_maq);


void salir_partida();


/*Precondición: Recibe la estructura de la configuración ya cargada y un entero con el id del jugador
Postcondición: Devuelve una estructura cargada con los datos del jugador especificado 
*/

void cargar_jugador(Jugador *j, ConfiguracionJuego config, int id);

#endif //LOGICA_H