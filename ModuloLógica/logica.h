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
    int esAgua;
}Registro_Maquina;


typedef struct{

    int id;
    int opcion_salir;
    Jugador jugador1;
    Jugador jugador2;

}ControlPartida;

//FUNCIONES RELACIONADAS CON EL DISPARO

/*P: Tableros existen, x,y dentro de Tableros. 
- T_Receive: TABLERO FLOTA AL QUE SE DISPARA
- T_Shoot: TABLERO OPONENTE EN EL QUE SE REGISTRA EL DISPARO

Q: Devuelve AGUA(0) si en [x,y] de T_Receive NO hay barco
Devuelve TOCADO(1) si en [x,y] de T_Receive SI hay barco, pero NO lo ha hundido
Devuelve HUNDIDO(2) si en [x,y] de T_Receive SI hay barco y lo HA HUNDIDO.
En todos los casos se guarda en T_Shoot la información resultante.
*/
int disparo(Tablero* T_Receive, Tablero* T_Shoot, int x, int y);

void disparo_menu(Jugador *j, Tablero *t, Registro_Maquina *reg_maq);
void dispararAleatorio(Tablero *t, Registro_Maquina *reg_maq);

/*P: Tableros existen, x, y dentro de tablero
Q: Recorre el barco empezando desde x,y y comprueba si las casillas entre T_Flota y T_Oponente coinciden
cómo disparadas y que haya un barco, si es así --> true, sino --> false*/
int recorrerBarco(Tablero* T_Flota, Tablero* T_Oponente, int x, int y);

//FUNCIONES DE DESARROLLO DE LA PARTIDA

//Pre: Ninguna
//Post: Función por defecto que reinicia el juego, prepara los tableros, carga los archivos y carga la configuración en la partida.
void reiniciarPartida();

void continuarPartida();

void flujoPartida(ConfiguracionJuego ConfiguracionJuego_L, Registro_Maquina *reg_maquina, ControlPartida ControlPartida);




/*Precondición: Recibe un puntero a estructura de un jugador, el vector de barcos cargado y la elección del jugador
Postcondición: Ejecuta la acción de colocar barcos en función del modo escogido*/
void f_eleccion_barcos(Jugador *pj, Vector_Barcos vectBarcos, char eleccion_barco);


void f_turno(Jugador* j, Registro_Maquina *reg_maq, ControlPartida *ControlPartida);


void salir_partida(ConfiguracionJuego ConfiguracionJuego, ControlPartida ControlPartida);


void fin_partida(ConfiguracionJuego config, ControlPartida ControlP);

void buscarNcasillas(Tablero t, int *valor, char c);






//FUNCIONES DE CARGADO Y GUARDADO

/*Precondición: Recibe la estructura de la configuración ya cargada y un entero con el id del jugador
Postcondición: Devuelve una estructura cargada con los datos del jugador especificado 
*/

void cargar_jugador(Jugador *j, ConfiguracionJuego config, int id);

#endif //LOGICA_H
