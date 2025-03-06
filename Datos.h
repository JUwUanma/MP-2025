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


//Estructura Jugador: almacena la informacion de los jugadores
typedef struct{
    int Id_jugador;             		//Identificador unico de cada jugador
    char Nomb_jugador[20];      		//Nombre del jugador
    char Tipo_disparo;          		//Tipo de disparo seleccionado (A -> Automatico [sistema], M -> Manual [pregunta al jugador])
    int Num_disparos;           		//Contador del numero de disparos de dicho jugador en cada turno
    int Ganador;                		//Indicador de si ha ganado la partida (0 -> Falso, 1 -> Verdadero)
    char Tablero_flota[15][15];       	//Tablero de la flota del jugador
    char Tablero_oponente[15][15];    	//Tablero del oponente
}Jugador;


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


//=====================================================================================================================

//Precondición: Recibe una estructura tipo Vect_Barcos (vector de estructuras Barco)
//Postcondición: Muestra por pantalla un listado con todos los barcos almacenados, junto con sus atributos 
void mostrar_barcos(Vector_Barcos);


//Precondición: Recibe una estructura tipo ConfiguracionJuego
//Postcondición: Muestra por pantalla un listado con la configuración inicial del juego
void mostrar_configuracion(ConfiguracionJuego);

#endif //BARCO_H_INCLUDED