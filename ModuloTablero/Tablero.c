#include "Tablero.h"

Tablero* crearTablero(int filas, int columnas)
{
    Tablero* t = malloc(sizeof(Tablero));
    if(!t){
        printf("ERROR DE MEMORIA", stderr);
        free(t);
        return NULL;
    }
    //Reservar memoria para filas
    t->casillas = malloc(filas * sizeof(char*));
    if(!t->casillas){
        printf("ERROR DE MEMORIA", stderr);
        free(t);
    }

    // Reservar memoria para cada fila (columnas)
    for (int i = 0; i < filas; i++) {
        t->casillas[i] = malloc(columnas * sizeof(char));
        if (!t->casillas[i]) {
            printf("Error al asignar memoria para la fila %d.\n", i);
            // Liberar memoria ya asignada
            for (int j = 0; j < i; j++) free(t->casillas[j]);
            free(t->casillas);
            free(t);
            return NULL;
        }
    }

    //Inicializar tablero a ' '
    for(int i = 0 ; i < filas ; ++i)
        for(int j = 0 ; j < columnas ; ++j)
            t->casillas[i][j] = ' ';

}

void mostrarFlota(Jugador* j)
{
    printf("\n\nFLOTA DEL JUGADOR %d: %s\n\n---------------------", j->Nomb_jugador, j->Id_jugador);
    //Método Privado para mostrar el tablero
    mostrarTablero(j->flota);
}

void mostrarOponente(Jugador* j)
{
    printf("\n\nTABLERO OPONENTE DEL JUGADOR %d: %s\n\n---------------------", j->Nomb_jugador, j->Id_jugador);
    //Método Privado para mostrar el tablero
    mostrarTablero(j->oponente);
}

static void mostrarTablero(Tablero* t)
{
    char cBuff;
    //Se recorre el tablero y se imprime cada casilla
    for(int j=0; j < t->yMax; ++j){
        for(int i=0; i < t->xMax; ++i){

            //Caso especial: 0 representa las casillas no ocupables
            if(cBuff = t->casillas[i][j] == '0'){
                printf("[ ] ");
            }else{
                printf("[%c] ", cBuff);
            }
        }
        printf("\n");
    }
}

void colocarManual(Jugador* j, Vector_Barcos vect)
{

}

void colocarAleatorio(Jugador* j, Vector_Barcos vect)
{

}
