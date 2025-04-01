#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> //sleep(tiempo)
#include "logica.h"
#include "..\\ModuloMemoria\Datos.h"
#include "..\\ModuloTablero\Tablero.h"

void disparo(Jugador *j,Tablero *t){

    int x=0, y=0;

    if(j->Tipo_disparo=='M'){
        int coordsCorrectas=0;
        
        do{
        
        puts("Introduce unas coordenadas (X,Y) para disparar.");
        scanf("%i %i",&x, &y);
        
        if(x > 0 && x <= t->maxLado && y > 0 && y <= t->maxLado) {
            //Verificar que la casilla no haya sido disparada antes
            if(t->casillas[x-1][y-1] == ' ') { //Resta 1 porque los vectores empiezan en 0
                coordsCorrectas = 1;
            } else {
                printf("Ya has disparado a esta posición (%d,%d). Intenta otra.\n", x, y);
            }
        } else {
            puts("Coordenadas no válidas. Deben estar dentro del rango del tablero.");
        }
        
        }while(coordsCorrectas!=1);

            if (devolverCasilla(t,x,y)=='X'){//Caso de que haya tocado un barco


                recorrer_barco();
                //IA super loca


            }
            else{
                
                colocarCasilla('*', t, x, y);
                printf("  _ _    _              __      _ _           _       _ \n");
                printf(" (_) |  | |            / _|    | | |         | |     | |\n");
                printf(" | | |__| | __ _ ___  | |_ __ _| | | __ _  __| | ___ | |\n");
                printf(" | |  __  |/ _` / __| |  _/ _` | | |/ _` |/ _` |/ _ \\| |\n");
                printf(" | | |  | | (_| \\__ \\ | || (_| | | | (_| | (_| | (_) |_|\n");
                printf(" |_|_|  |_|\\__,_|___/ |_| \\__,_|_|_|\\__,_|\\__,_|\\___/(_)\n");
                printf("Has tocado agua.\n");
                sleep(3);
                
                mostrarOponente(j);
                //Limpiar terminal y cambiar de turno

            }

        (j->Num_disparos)++;
    }
    else{ //Bloque de disparo automático

        do{
        srand(time(NULL));              //Semilla generada a partir de la hora actual
        x=rand() % (t->maxLado + 1);       //Número aleatorio entre 0 y xMax
        y=rand() % (t->maxLado + 1);       //Igual pero con y
        
        }while(t->casillas[x][y]!=' '); //t->casillas puede que lo cambie por otra función



        (j->Num_disparos)++;
    }
}


void reiniciarPartida(){


ConfiguracionJuego ConfiguracionJuego_L = cargar_config();
int dim = ConfiguracionJuego_L.Tama_tablero;
//Se crea el tablero del tamaño especificado en la configuración
crearTablero(dim);
Vector_Barcos Vector_Barcos_L = cargar_barcos();
//Estructuras de los jugadores
Jugador j1;
Jugador j2;
//Punteros a las estructuras
Jugador *pj1= &j1;
Jugador *pj2= &j2;

cargar_jugador(pj1, ConfiguracionJuego_L, 1);
cargar_jugador(pj2, ConfiguracionJuego_L, 2);

char eleccion_barco_j1, eleccion_barco_j2;
//Elección de colocar barcos

    f_eleccion_barcos(pj1,Vector_Barcos_L,eleccion_barco_j1);
    f_eleccion_barcos(pj2,Vector_Barcos_L,eleccion_barco_j2);
    
    //turno(j1);

}


void turno(){

    //puts("Es el turno de %s", );

}



void f_eleccion_barcos(Jugador *pj, Vector_Barcos vectBarcos, char eleccion_barco){

    do{

        printf("%s: Introduce un carácter para elegir modo de colocación de barcos\n", pj->Nomb_jugador);
        printf("'M' == Manual    'A' == Automático");
        
        scanf("%c",&eleccion_barco);
        
        
        }while(eleccion_barco!='M'||eleccion_barco!='A');
    
        if(eleccion_barco=='M'){

            colocarManual(pj,vectBarcos);
        
        }else{

            colocarAleatorio(pj);

        }
        

}


void cargar_jugador(Jugador *j, ConfiguracionJuego config, int id){

    j->Id_jugador = id;


    if (id == 1){
        
        strcpy(j->Nomb_jugador,config.Nomb_J1);
        j->Tipo_disparo=config.Tipo_disparo_J1;
        j->Tablero_flota = config.Tablero_flota1;
        j->Tablero_oponente = config.Tablero_oponente1;
    
    }
    else{
        
        strcpy (j->Nomb_jugador,config.Nomb_J2);
        j->Tipo_disparo=config.Tipo_disparo_J2;
        j->Tablero_flota = config.Tablero_flota2;
        j->Tablero_oponente = config.Tablero_oponente2;
    
    }
     
}