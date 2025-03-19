#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Datos.h"
#include "Tablero.h"

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

void disparo(Jugador *j,Tablero *t){

    int x=0, y=0;

    if(j->Tipo_disparo=='M'){

        //Bloque de disparo manual

    }
    else{ //Bloque de disparo automático

        srand(time(NULL));              //Semilla generada a partir de la hora actual
        x=rand() % (t->xMax + 1);       //Número aleatorio entre 0 y xMax
        y=rand() % (t->xMax + 1);       //Igual pero con y

        //if(verificar_posicion(x, y, t)){}

        resultado_disparo(x,y,*t);

        (j->Num_disparos)++; //Se supone que está inicializado a 0 al inicio del juego
    }

}

void resultado_disparo(int i, int j, Tablero *t, Jugador *j){


}
