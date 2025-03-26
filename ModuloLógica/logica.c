#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> //sleep(tiempo)
#include "..\\ModuloMemoria\Datos.h"
#include "..\\ModuloTablero\Tablero.h"

void disparo(Jugador *j,Tablero *t){

    int x=0, y=0;

    if(j->Tipo_disparo=='M'){
        int coordsCorrectas=0;
        
        do{
        
        puts("Introduce unas coordenadas (X,Y) para disparar.");
        scanf("%i %i",&x, &y);
        
        if(0<x<=(t->maxLado)&&0<y<=(t->maxLado)){

            coordsCorrectas=1;
        }
        else{puts("Coordenadas no válidas");}
        
        }while(coordsCorrectas!=1&&isLibre(t,x,y));//nota para el futuro: mostrar mensaje según contenido de la casilla
        
        //j: Jugador que ejecuta el disparo, 1: tablero del oponente, x y: coords

            if (devolverCasilla(j,1,x,y)=='X'){//Caso de que haya tocado un barco




            }
            else{
                
                colocarCasilla('*', j, 1, x, y);
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


void iniciarPartida(){

ConfiguracionJuego ConfiguracionJuego_L = cargar_config();
Vector_Barcos Vector_Barcos_L = cargar_barcos();




}
