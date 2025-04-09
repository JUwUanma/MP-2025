#ifndef DATOS_H_INCLUDED
#define DATOS_H_INCLUDED
#define LONG_MAX_BARCO 100
#define LONG_MAX_JUEGO 100
#define LONG_MAX_CONFIG 100


//Estructura Barco: Almacena la informacion de cada barco en el sistema
typedef struct{
    char Nomb_barco[20];    //Nombre del barco
    char Id_barco;          //Identificador unico del barco (una letra en mayusculas)
    int Tam_barco;          //Tamaño del barco (numero de casillas que ocupa)
}Barco;


//Vector de estructuras Barco
typedef struct{
    Barco *Barcos;
    int tam;
}Vector_Barcos;


//Estructura Tablero: Almacena la informacion del tablero de la partida
typedef struct{
    char** casillas; 		//Guarda la matriz que representa el tablero
    int maxLado;			//Tamaño maximo de la matriz (cuadrada)
}Tablero;



//Estructura Juego: Almacena la informacion del juego
typedef struct {
    char Nomb_J1[20];          // Nombre del jugador 1
    char Tipo_disparo_J1;      // Tipo de disparo del jugador 1 (M o A)
    char Nomb_J2[20];          // Nombre del jugador 2
    char Tipo_disparo_J2;      // Tipo de disparo del jugador 2 (M o A)
    int Tama_tablero;          // Tamaño del tablero (nxn)
    char *Tipo_barcos;         // Vector dinámico de tipos de barcos (un carácter por tipo)
    int *num_barcos;           // Vector dinámico del número de barcos de cada tipo
    int Tama_flota;            // Número de tipos de barcos
    char Primer_Jugador[20];   // Nombre del jugador que comienza
    Tablero Tablero_flota1;       	    //Tablero de la flota del jugador1
    Tablero Tablero_oponente1;    	    //Tablero del oponente1
    Tablero Tablero_flota2;       	    //Tablero de la flota del jugador2
    Tablero Tablero_oponente2;    	    //Tablero del oponente2
} ConfiguracionJuego;
//Esta estructura se carga en memoria nada mas empezar la ejecucion del programa



//Definiciones de funciones:

//======================================FUNCIONES DE CARGA=============================================================
//Precondición: Ninguna
//Postcondición: Devuelve un vector de Barcos, con todos los Barcos almacenados en Barcos.txt
Vector_Barcos cargar_barcos();

//Precondición: Ninguna
//Postcondición: Devuelve la estructura Juego rellena, del fichero Juego.txt
ConfiguracionJuego cargar_config();
//=====================================================================================================================


//======================================FUNCIONES DE GUARDADO==========================================================
//Precondición: Recibe una estructura tipo Vect_Barcos (vector de estructuras Barco)
//Postcondición: Guarda todos los barcos almacenados en memoria en Barcos.txt
/*

void guardar_barcos(Vector_Barcos);
Esta funcion hay que mirar si es necesaria, ya que no hay posibilidad de modificar los barcos durante una sesion

*/

//Precondición: Recibe la estructura ConfiguracionJuego
//Postcondición: Devuelve la estructura ConfiguracionJuego modificada con los parametros que indique el usuario

void guardar_config(ConfiguracionJuego);

//=====================================================================================================================

//Precondición: Recibe una estructura tipo Vect_Barcos (vector de estructuras Barco)
//Postcondición: Muestra por pantalla un listado con todos los barcos almacenados, junto con sus atributos 
void mostrar_barcos(Vector_Barcos);


//Precondición: Recibe una estructura tipo ConfiguracionJuego
//Postcondición: Muestra por pantalla un listado con la configuración inicial del juego
void mostrar_configuracion(ConfiguracionJuego);


//Precondición: Recibe la referencia de la estructura ConfiguracionJuego para modificarla
//Postcondición: Modifica la configuracion del juego con los parametros que indique el usuario
void modificar_config(ConfiguracionJuego*);


//Precondición: Recibe la referencia de la estructura ConfiguracionJuego para reiniciar su contenido
//Postcondición: Borra la configuracion del juego
void borrar_config(ConfiguracionJuego*);

#endif //BARCO_H_INCLUDED
