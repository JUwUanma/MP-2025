#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Modulo_Datos/Datos.h"
#include "../Modulo_Tablero/Tablero.h"
/*
int verificar_barco(ConfiguracionJuego ConfiguracionJuego,int x, int y){


}

int verificar_posicion(int i, int j, Tablero t){

    int dim= Tablero.xMax; //Dimensión del tablero, como el tablero debe ser cuadrado xMax=yMax
    //int yMax= Tablero.yMax;  

    if (i >= 0 && i <= dim && j >= 0 && j <= dim){
        return 1;
    }
    else{
        return 0;
    }

}
*/
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
        
        }while(coordsCorrectas!=1&&t->casillas[x][y]!=' ');
        
    

        //Realizar el cambio
        (j->Num_disparos)++;
    }
    else{ //Bloque de disparo automático

        do{
        srand(time(NULL));              //Semilla generada a partir de la hora actual
        x=rand() % (t->maxLado + 1);       //Número aleatorio entre 0 y xMax
        y=rand() % (t->maxLado + 1);       //Igual pero con y
        
        }while(t->casillas[x][y]!=' '); //t->casillas puede que lo cambie por otra función



        (j->Num_disparos)++; //Se supone que está inicializado a 0 al inicio del juego
    }

}