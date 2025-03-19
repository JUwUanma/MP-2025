#ifndef DATOS_H_INCLUDED
#define DATOS_H_INCLUDED
#define LONG_MAX_BARCO 100
#define LONG_MAX_JUEGO 100
#define LONG_MAX_CONFIG 100

#include "Tablero.h"

//Estructura Barco: Almacena la informacion de cada barco en el sistema
typedef struct{
    char Nomb_barco[20];    //Nombre del barco
    char Id_barco;          //Identificador unico del barco (una letra en mayusculas)
    int Tam_barco;          //Tama�o del barco (numero de casillas que ocupa)
}Barco;

//Vector de estructuras Barco
typedef struct{
    Barco *Barcos;
    int tam;
}Vector_Barcos;


//Estructura Jugador: almacena la informacion de los jugadores
typedef struct{
    int Id_jugador;             		//Identificador unico de cada jugador
    char Nomb_jugador[20];      		//Nombre del jugador
    char Tipo_disparo;          		//Tipo de disparo seleccionado (A -> Automatico [sistema], M -> Manual [pregunta al jugador])
    int Num_disparos;           		//Contador del numero de disparos de dicho jugador en cada turno
    int Ganador;                		//Indicador de si ha ganado la partida (0 -> Falso, 1 -> Verdadero)
    Tablero Tablero_flota;       	    //Tablero de la flota del jugador
    Tablero Tablero_oponente;    	    //Tablero del oponente
}Jugador;


//Estructura Juego: Almacena la informacion del juego
typedef struct {
    char Nomb_J1[20];          // Nombre del jugador 1
    char Tipo_disparo_J1;      // Tipo de disparo del jugador 1 (M o A)
    char Nomb_J2[20];          // Nombre del jugador 2
    char Tipo_disparo_J2;      // Tipo de disparo del jugador 2 (M o A)
    int Tama_tablero;          // Tama�o del tablero (nxn)
    char *Tipo_barcos;         // Vector din�mico de tipos de barcos (un car�cter por tipo)
    int *num_barcos;           // Vector din�mico del n�mero de barcos de cada tipo
    int Tama_flota;            // N�mero de tipos de barcos
    char Primer_Jugador[20];   // Nombre del jugador que comienza
} ConfiguracionJuego;
//Esta estructura se carga en memoria nada mas empezar la ejecucion del programa



//Definiciones de funciones:

//======================================FUNCIONES DE CARGA=============================================================
//Precondici�n: Ninguna
//Postcondici�n: Devuelve un vector de Barcos, con todos los Barcos almacenados en Barcos.txt
Vector_Barcos cargar_barcos();

//Precondici�n: Ninguna
//Postcondici�n: Devuelve la estructura Juego rellena, del fichero Juego.txt
ConfiguracionJuego cargar_config();
//=====================================================================================================================


//======================================FUNCIONES DE GUARDADO==========================================================
//Precondici�n: Recibe una estructura tipo Vect_Barcos (vector de estructuras Barco)
//Postcondici�n: Guarda todos los barcos almacenados en memoria en Barcos.txt
/*

void guardar_barcos(Vector_Barcos);
Esta funcion hay que mirar si es necesaria, ya que no hay posibilidad de modificar los barcos durante una sesion

*/

//Precondici�n: Recibe la estructura ConfiguracionJuego
//Postcondici�n: Devuelve la estructura ConfiguracionJuego modificada con los parametros que indique el usuario

void guardar_config(ConfiguracionJuego);

//=====================================================================================================================

//Precondici�n: Recibe una estructura tipo Vect_Barcos (vector de estructuras Barco)
//Postcondici�n: Muestra por pantalla un listado con todos los barcos almacenados, junto con sus atributos
void mostrar_barcos(Vector_Barcos);


//Precondici�n: Recibe una estructura tipo ConfiguracionJuego
//Postcondici�n: Muestra por pantalla un listado con la configuraci�n inicial del juego
void mostrar_configuracion(ConfiguracionJuego);


//Precondici�n: Recibe la referencia de la estructura ConfiguracionJuego para modificarla
//Postcondici�n: Modifica la estructura ConfiguracionJuego con los parametros que indique el usuario
void modificar_config(ConfiguracionJuego*);

#endif //BARCO_H_INCLUDED
