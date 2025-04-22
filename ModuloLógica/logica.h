#ifndef LOGICA_H
#define LOGICA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "Datos.h"



enum TIPO_DISPARO {AGUA, TOCADO, HUNDIDO};
enum ESTADOS_PARTIDA {NO_FINALIZADA, GANA_J1, GANA_J2, EMPATE};

//--------------------------------ESTRUCTURAS--------------------------------

//Estructura Registro_Máquina: registro que usa el programa como apoyo principalmente para disparar automático
typedef struct{
    int x_maq, y_maq;           //Coordenadas x,y que recibe el algoritmo por si necesita guardarlas
    int orient_maq;             //Orientación de un barco
    int flagEncontrado_maq;     //Boolenao que indica si se ha encontrado un barco
}Registro_Maquina;

//Estructura Jugador: almacena la informacion de los jugadores
typedef struct{
    int Id_jugador;             		//Identificador unico de cada jugador
    char Nomb_jugador[20];      		//Nombre del jugador
    char Tipo_disparo;          		//Tipo de disparo seleccionado (A -> Automatico [sistema], M -> Manual [pregunta al jugador])
    int Num_disparos;           		//Contador del numero de disparos de dicho jugador en cada turno
    int Ganador;                		//Indicador de si ha ganado la partida (0 -> Falso, 1 -> Verdadero)
    int barcos_restantes;               //Contador que decrece en función de los barcos que faltan por hundir
    Tablero Tablero_flota;       	    //Tablero de la flota del jugador
    Tablero Tablero_oponente;    	    //Tablero del oponente
}Jugador;

//Estructura ControlPartida: almacena los valores fundamentales durante el desarrollo de una partida
typedef struct{

    int id_turno;                       //Turno actual -> Sólo para f_turno, al cargar partida siempre empieza J1
    int n_ronda;                        //Número de rondas jugadas
    int nBarcosRestantes[3];            //Vector estática que almacena los barcos restantes POR DISPARAR de cada jugador [1]: J1, [2]: J2, [0]: N/A        
    int hayGanador;                     //0 si NO hay ganador, 1 si J1 es ganador, 2 si J2 es ganador, 3 si empate.
    Jugador jugador1;                   //Estructuras de los jugadores
    Jugador jugador2;

}ControlPartida;


//--------------------------------FUNCIONES--------------------------------


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

/*P: Jugadores creados y registro máquina inicializado
Q: Según el tipo de disparo del jugador Shoot, entra en el menú de disparo y devuelve el resultado
del disparo contra el jugador J_Receive, en disparos aleatorios se utiliza Registro_Maquina, en
manuales no.*/
int disparo_menu(Jugador* J_Shoot, Jugador* J_Receive, Registro_Maquina *reg_maq);

/*P: Tableros existen
- T_Receive: TABLERO FLOTA AL QUE SE DISPARA
- T_Shoot: TABLERO OPONENTE EN EL QUE SE REGISTRA EL DISPARO
Q: Entra en el menú de disparo manual, se muestra el tablero oponente (T_Shoot)
*/
int dispararManual(Tablero* T_Receive, Tablero* T_Shoot);

/*P: Tableros y registros máquinas existen
- T_Receive: TABLERO FLOTA AL QUE SE DISPARA
- T_Shoot: TABLERO OPONENTE EN EL QUE SE REGISTRA EL DISPARO
Q: Dispara a una posición aleatoria, si encuentra un barco, registra la posición y en el siguiente turno
dispará para encontrar la orientación, una vez encontrada, disparará hasta derribarlo.*/
int dispararAleatorio(Tablero* T_Receive, Tablero* T_Shoot, Registro_Maquina *reg);

/*P: Tableros existen, x, y dentro de tablero
Q: Recorre el barco empezando desde x,y y comprueba si las casillas entre T_Flota y T_Oponente coinciden
cómo disparadas y que haya un barco, si es así --> true, sino --> false*/
int recorrerBarco(Tablero* T_Flota, Tablero* T_Oponente, int x, int y);

/*P: Tableros existen y x,y dentro de tablero. Hay una casilla de barco en x,y
Q: Devuelve la orientación (GX) del barco en x, y. Devuelve G315 + 1 (8) si es un barco de una sola casilla*/
int encontrarOrientación(Tablero* T_Flota, int x, int y);

/*P: Tablero existe, x, y dentro de tablero, orient es la orientación del barco (encontrarOrientacion)
Q: Devuelve por referencia las coordenadas del extremo*/
void encontrarExtremo(Tablero* T_Flota, int* x, int* y, int orient);







//FUNCIONES DE DESARROLLO DE LA PARTIDA

/*Pre: Ninguna
Post: Función por defecto que reinicia (inicia desde 0) el juego, prepara los tableros, 
carga los archivos y carga la configuración en la partida Devuelve lo mismo que flujoPartida.
Es decir, 1 si se ha completado la partida, 0 sino.*/
int reiniciarPartida();


/*P: Todos los registros cargados e inicializados
Q: Realiza el flujo normal de partida. Devuelve 1 si se ha terminado, 0 si no. Los datos de partida están en partida*/
int flujoPartida(ConfiguracionJuego* config, Registro_Maquina *reg_maquina, ControlPartida* partida);

/*P: Todos los registros cargados e inicializados
Q: Realiza un turno normal del jugador j, cambia partida->hayGanador si no quedan barcos restantes por hundir del oponente*/
void f_turno(Registro_Maquina *reg_maq, ControlPartida *partida);

/*Precondición: Recibe un puntero a estructura de un jugador y el vector de barcos cargado
Postcondición: Ejecuta la acción de colocar barcos en función del modo escogido y devuelve el carácter indicador*/
char f_eleccion_barcos(Jugador *pj, Vector_Barcos vectBarcos);

/*
Precondición: Recibe las estructuras principales del programa para realizar todos los guardados
Postcondición: Concluye el flujo de la partida en caso de querer salir o haber terminado la partida
*/
void salir_partida(ConfiguracionJuego* ConfiguracionJuego, ControlPartida* ControlPartida);

/*
Precondición: Recibe un tablero, un puntero a entero y un carácter a buscar dentro del tablero
Postcondición: Cambia el valor en la dirección apuntada con el número de casillas en el tablero en el que se encuentre el carácter
Nota: Función usada para mostrar el resumen de la partida
*/
void buscarNcasillas(Tablero t, int *valor, char c);


void resumen_partida(ConfiguracionJuego config, ControlPartida ControlP);



//FUNCIONES DE CARGADO Y GUARDADO

/*Precondición: Recibe la estructura de la configuración ya cargada y un entero con el id del jugador
Postcondición: Devuelve una estructura cargada con los datos del jugador especificado 
*/

void cargar_jugador(Jugador *j, ConfiguracionJuego config, int id);

/*Precondición: Recibe una estructura de configuración previamente inicializada
Postcondición: Devuelve una estructura cargada con los datos inicializados para el control de la partida
*/
ControlPartida cargar_controlPartida(ConfiguracionJuego config);

void guardar_jugadores(Jugador* j1, Jugador* j2, ConfiguracionJuego *config);


#endif //LOGICA_H
