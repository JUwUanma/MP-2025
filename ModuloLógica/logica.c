#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> //sleep(tiempo)
#include "logica.h"
#include "..\\ModuloMemoria\Datos.h"
#include "..\\ModuloTablero\Tablero.h"
#include "..\\ModuloInterfaz\Interfaz.h"

void dispararAleatorio(Tablero* T, Registro_Maquina* reg)
{
    int resDisparo;
    int xAux = reg.x_maq;
    int yAux = reg.y_maq;
    int orientAux = reg.orient_maq;
    int flagValidPosition = false;
    //¿Se ha encontrado un barco?
    if(!reg.flagEncontrado){
        //No se ha encontrado --> Disparo aleatorio

        //Elige una posición aleatoria del tablero
        do{
            reg.x_maq = 0 + rand() % T.maxLado;
            reg.y_maq = 0 + rand() % T.maxLado;
        }while(devolverCasilla(T, reg.x_maq, reg.y_maq) != ' ');
        //¿Es vacía?

        //Dispara en la casilla elegida. ¿Ha sido agua?
        if((resDisparo = disparo(T, reg.x_maq, reg.y_maq) != AGUA))
            reg.flagEncontrado = reg.flagEncontrado == 2 ? false : true;
            //¿Lo ha hundido?
        
    }else{
        //Se ha encontrado --> ¿Se sabe la dirección?

        //¿Se ha encontrado la orientación del barco?
        if(reg.orient_maq == -1){
            //No se ha encontrado la orientación del barco

            //Rota la orientación a una aleatoria
            do{
               orientAux = G0 + rand() % (G315 + 1);
               moverAOrientacion(orientAux, &xAux, &yAux);
                
               //¿Es agua?
                if(devolverCasilla(T, reg.x_maq, reg.y_maq) != '*') 
                    flagValidPosition = true;
                else{
                    orientAux = reg.orient_maq;
                    xAux = reg.x_maq; yAux = reg.y_maq;
                }
            }while(!flagValidPosition);
            
            reg.orient_maq = orientAux;

            //Dispara en la casilla elegida
            //¿Ha sido agua?
            if(resDisparo = disparo(T, reg.x_maq, reg.y_maq)){
                //No ha sido agua

                //¿Lo ha hundido?
                if(resDisparo == 2) reg.flagEncontrado = false;
        
            }else{
                //Si ha sido agua, no es esa orientación
                reg.orient_maq = -1;
            }


        }else{
            //Se ha encontrado la orientación del barco
            moverAOrientacion(reg.orient_maq, &reg.x_maq, &reg.y_maq);

            //¿Ha sido agua?
            if(resDisparo = disparo(T, reg.x_maq, reg.y_maq)){
                //No ha sido agua

                //¿Lo ha hundido?
                if(resDisparo == 2) reg.flagEncontrado = false;
            }else{
                //Si ha sido agua
                rotar(&orientAux, G180, DERECHA); //Indistinto derecha o izquierda
                do{
                    moverAOrientacion(orientAux, &xAux, &yAux);
                    if(devolverCasilla(T, xAux, yAux) != ' '){
                        flagValidPosition = true;
                    }
                }while(!flagValidPosition); //Técnicamente no es necesario aquí las variables aux

                moverAOrientacion(reg.orient_maq, &xAux, &yAux);
                reg.x_maq = xAux;
                reg.y_maq = yAux;
                reg.orient_maq = orientAux;
                //Se preparan las coordenadas para que la próxima iteración dispare al barco
            }
        
            
        }
    }
}


void disparo_menu(Jugador *j,Tablero *t, Registro_Maquina *reg_maq){

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


                printf("Has acertado!!");
                colocarCasilla('T', t, x, y);
                // _ _____                   _       _ 
                // (_)_   _|__   ___ __ _  __| | ___ | |
                // | | | |/ _ \ / __/ _` |/ _` |/ _ \| |
                // | | | | (_) | (_| (_| | (_| | (_) |_|
                // |_| |_|\___/ \___\__,_|\__,_|\___/(_)
                sleep(3);
                system("cls");
                mostrarOponente(j);
            }
            else{
                
                system("cls");
                colocarCasilla('*', t, x, y);
                printf("  _ _    _              __      _ _           _       _ \n");
                printf(" (_) |  | |            / _|    | | |         | |     | |\n");
                printf(" | | |__| | __ _ ___  | |_ __ _| | | __ _  __| | ___ | |\n");
                printf(" | |  __  |/ _` / __| |  _/ _` | | |/ _` |/ _` |/ _ \\| |\n");
                printf(" | | |  | | (_| \\__ \\ | || (_| | | | (_| | (_| | (_) |_|\n");
                printf(" |_|_|  |_|\\__,_|___/ |_| \\__,_|_|_|\\__,_|\\__,_|\\___/(_)\n");
                printf("Has tocado agua.\n");
                sleep(3);
                system("cls");
                mostrarOponente(j);

            }

        (j->Num_disparos)++;
    }
    else{ //Bloque de disparo automático

        do{
        srand(time(NULL));              //Semilla generada a partir de la hora actual
        x=rand() % (t->maxLado + 1);       //Número aleatorio entre 0 y xMax
        y=rand() % (t->maxLado + 1);       //Igual pero con y
        
        }while(t->casillas[x][y]!=' '); //t->casillas puede que lo cambie por otra función

        disparo_aleatorio(t, reg_maq);

        (j->Num_disparos)++;
    }
}


void reiniciarPartida(){


ConfiguracionJuego ConfiguracionJuego_L = cargar_config();
Vector_Barcos Vector_Barcos_L = cargar_barcos();

int dim = ConfiguracionJuego_L.Tama_tablero;
//Se crea el tablero del tamaño especificado en la configuración
crearTablero(dim);


//Estructura dedicada a guardar datos sobre coordenadas que necesita el algoritmo para que funcione y evitar perder información vital.
Registro_Maquina reg_maquina;
//Inicialización de las variables
reg_maquina.flagEncontrado_maq=false;
reg_maquina.orient_maq=-1;
reg_maquina.x_maq=0;
reg_maquina.y_maq=0;



//Estructuras de los jugadores
Jugador j1;
Jugador j2;

int x_maq, y_maq; //
int orient_maq=-1;
int flagEncontrado_maq=false;

//Cargamos los datos guardados en la configuración en la estructura de los jugadores
cargar_jugador(&j1, ConfiguracionJuego_L, 1);
cargar_jugador(&j2, ConfiguracionJuego_L, 2);

char eleccion_barco_j1, eleccion_barco_j2;
//Elección de colocar barcos

    f_eleccion_barcos(&j1,Vector_Barcos_L,eleccion_barco_j1);
    f_eleccion_barcos(&j2,Vector_Barcos_L,eleccion_barco_j2);
    
    int opcion_salir;

    do{

        if(!j2.Ganador)
        turno(&j1, &opcion_salir, &reg_maquina);
        else
        fin_partida();



        if(!j1.Ganador)
        turno(&j2, &opcion_salir, &reg_maquina);
        else
        fin_partida();

    }while(opcion_salir);

salir_partida(ConfiguracionJuego_L);

}


void turno(Jugador* j, int *opcion_salir, Registro_Maquina *reg_maq){

    Tablero tablero = j->Tablero_oponente;
    printf("Es el turno de %s\n", j->Nomb_jugador);
    sleep(3);
    system("cls");
    disparo_menu(j,&j->Tablero_oponente, reg_maq);

    mostrarOponente(j);

    do{printf("¿Quieres continuar(Pulsa la opción que desees)?:\nSí: [1]\nNo: [0]");

        scanf("%i", &opcion_salir);
        
    }while((*opcion_salir!=0)&&(*opcion_salir!=1));
}

void salir_partida(ConfiguracionJuego ConfiguracionJuego){

    guardar_config(ConfiguracionJuego);
    MenuPrincipal();

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
