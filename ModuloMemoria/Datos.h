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
	int Id_J1;					// Identificador unico del primer jugador
    char Nomb_J1[20];          	// Nombre del jugador 1
    char Tipo_disparo_J1;      	// Tipo de disparo del jugador 1 (M o A)
    int Num_disparos_J1;		// Numero de disparos del jugador 1
    int Ganador_J1;				// Indicador de si jugador 1 ha ganado la partida (0 -> Falso, 1 -> Verdadero)
    int Id_J2;					// Identificador unico del segundo jugador
    char Nomb_J2[20];          	// Nombre del jugador 2
    char Tipo_disparo_J2;      	// Tipo de disparo del jugador 2 (M o A)
    int Num_disparos_J2;		// Numero de disparos del jugador 2
    int Ganador_J2;				// Indicador de si jugador 2 ha ganado la partida (0 -> Falso, 1 -> Verdadero)
    int Tama_tablero;          	// Tamaño del tablero (nxn)
    int Tama_flota;            	// Número de barcos
    int Tama_tipos_barco;      	// Número de tipos de barcos
    char *Tipo_barcos;         	// Vector dinámico de tipos de barcos (un carácter por tipo)
    int *Num_barcos;           	// Vector dinámico del número de barcos de cada tipo
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
//Precondición: Recibe la estructura ConfiguracionJuego
//Postcondición: Devuelve la estructura ConfiguracionJuego modificada con los parametros que indique el usuario

void guardar_config(ConfiguracionJuego);
//=====================================================================================================================



//======================================FUNCIONES DE MOSTRADO==========================================================
//Precondición: Recibe una estructura tipo Vect_Barcos (vector de estructuras Barco)
//Postcondición: Muestra por pantalla un listado con todos los barcos almacenados, junto con sus atributos 
void mostrar_barcos(Vector_Barcos);

//Precondición: Recibe una estructura tipo ConfiguracionJuego
//Postcondición: Muestra por pantalla un listado con la configuración inicial del juego
void mostrar_configuracion(ConfiguracionJuego);
//=====================================================================================================================



//======================================FUNCION DE MODIFICADO==========================================================
//Precondición: Recibe la referencia de la estructura ConfiguracionJuego para modificarla
//Postcondición: Modifica la configuracion del juego con los parametros que indique el usuario
void modificar_config(ConfiguracionJuego*);


//Precondición: Recibe la referencia de la estructura ConfiguracionJuego para modificarla (solo para los barcos)
//Postcondición: Modifica la configuracion del juego con los parametros que indique el usuario (solo para modificar los barcos)
void modificar_barcos(ConfiguracionJuego*);
//=====================================================================================================================



//======================================FUNCION DE BORRADO=============================================================
//Precondición: Recibe la referencia de la estructura ConfiguracionJuego para reiniciar su contenido
//Postcondición: Borra la configuracion del juego
void borrar_config(ConfiguracionJuego*);
//=====================================================================================================================

#endif //BARCO_H_INCLUDED
