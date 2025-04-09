#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> //sleep(tiempo)
#include "logica.h"
#include "..\\ModuloMemoria\Datos.h"
#include "..\\ModuloTablero\Tablero.h"
#include "..\\ModuloInterfaz\Interfaz.h"

static int isExtremo(Tablero* T_Flota, int x, int y, int orient);

int disparo(Tablero* T_Receive, Tablero* T_Shoot, int x, int y)
{
    char charBuffer = devolverCasilla(T_Receive, x, y); //Buffer para no llamar a la función dos veces

    if(charBuffer == ' ' || charBuffer == '0'){ //Si está vacía (o casilla ocupada) devuelve AGUA
        return AGUA;
    }else{//Sino, recorre el barco, si se ha recorrido por completo -> HUNDIDO, sino -> TOCADO
        return (recorrerBarco(T_Receive, T_Shoot, x, y) ? HUNDIDO : TOCADO);
    }
}

int recorrerBarco(Tablero* T_Flota, Tablero* T_Oponente, int x, int y)
{
    int orient = G0;
    int xIni = x, yIni = y;
    int cont = 0; //Contador para saber si es un barco de única casilla
    int flagHundido = false;
    char charBufferFlota;
    char charBufferOpon;

    moverAOrientacion(T_Flota, orient, &x, &y);

    //Mientras no encuentre la orientación del barco o, en su defecto, no la encuentra
    while(cont != (G315 + 1) && devolverCasilla(T_Flota, x, y) != 'X'){
        x = xIni; y = yIni; //Reinicia la posición
        rotar(&orient, G45, IZQUIERDA); //Rota a la siguiente orientación
        moverAOrientacion(T_Flota, orient, &x, &y);
        cont++;
    }

    //No se ha encontrado la orientación, es decir, es una casilla única --> HUNDIDO
    if(cont == G315 + 1) return true;

    //¿[x,y] está en un extremo del barco?
    while(!isExtremo(T_Flota, x, y, orient)){
        moverAOrientacion(T_Flota, orient, &x, &y);
    }

    rotar(&orient, 180, IZQUIERDA);

    do{
        moverAOrientacion(T_Flota, orient, &x, &y);
        charBufferFlota = devolverCasilla(T_Flota, x, y);
        charBufferOpon = devolverCasilla(T_Oponente, x, y);

        //¿Son ' ' en sus respectivos tableros?
        if(charBufferFlota == ' ' || charBufferFlota == '0' && charBufferOpon == ' ') return true;
        if(charBufferFlota != 'X' || charBufferOpon != 'T') return false;
                //Nota: No la mejor implementación pero en principio funciona
    }while(true);

}

/*P: Tablero existe, y orient es la orientación del barco, x, y dentro de tablero
Q: Devuelve true si la casilla se encuentra en un extremo del barco, es decir,
en la orientación dada, hay una casilla en un sentido y no en el contrario.

TODO's:
- Si es una casilla de un barco con una única casilla devolverá false
- El barco puede estar en un lateral del tablero --> ERROR ¿Comprobación en moverAOrientacion?*/
static int isExtremo(Tablero* T_Flota, int x, int y, int orient)
{
    int xIni = x, yIni = y;
    char charBuffer;

    moverAOrientacion(T_Flota, orient, &x, &y);
    charBuffer = devolverCasilla(T_Flota, x, y);

    rotar(orient, G180, IZQUIERDA);
    moverAOrientacion(T_Flota, orient, &xIni, &yIni);

    return (charBuffer != devolverCasilla(T_Flota, xIni, yIni));
}

void dispararAleatorio(Tablero* T_Receive, Tablero* T_Shoot, Registro_Maquina* reg)
{
    int resDisparo;
    int xAux = reg->x_maq;
    int yAux = reg->y_maq;
    int orientAux = reg->orient_maq;
    int flagValidPosition = false;
    int n = T_Receive->maxLado;
    //¿Se ha encontrado un barco?
    if(!reg->flagEncontrado_maq){
        //No se ha encontrado --> Disparo aleatorio

        //Elige una posición aleatoria del tablero
        do{
            reg->x_maq = 0 + rand() % n;
            reg->y_maq = 0 + rand() % n;
        }while(devolverCasilla(T_Receive, reg->x_maq, reg->y_maq) != ' ');
        //¿Es vacía?

        //Dispara en la casilla elegida. ¿Ha sido agua?
        if((resDisparo = disparo(T_Receive, T_Shoot, reg->x_maq, reg->y_maq) != AGUA))
            reg->flagEncontrado_maq = reg->flagEncontrado_maq == 2 ? false : true;
            //¿Lo ha hundido?
        
    }else{
        //Se ha encontrado --> ¿Se sabe la dirección?

        //¿Se ha encontrado la orientación del barco?
        if(reg->orient_maq == -1){
            //No se ha encontrado la orientación del barco

            //Rota la orientación a una aleatoria
            do{
               orientAux = G0 + rand() % (G315 + 1);
               moverAOrientacion(T_Shoot, orientAux, &xAux, &yAux);
                
               //¿Es agua?
                if(devolverCasilla(T_Shoot, reg->x_maq, reg->y_maq) != '*') 
                    flagValidPosition = true;
                else{
                    orientAux = reg->orient_maq;
                    xAux = reg->x_maq; yAux = reg->y_maq;
                }
            }while(!flagValidPosition);
            
            reg->orient_maq = orientAux;

            //Dispara en la casilla elegida
            //¿Ha sido agua?
            if(resDisparo = disparo(T_Receive, T_Shoot, reg->x_maq, reg->y_maq)){
                //No ha sido agua

                //¿Lo ha hundido?
                if(resDisparo == 2) reg->flagEncontrado_maq = false;
        
            }else{
                //Si ha sido agua, no es esa orientación
                reg->orient_maq = -1;
            }


        }else{
            //Se ha encontrado la orientación del barco
            moverAOrientacion(T_Receive, reg->orient_maq, &reg->x_maq, &reg->y_maq);

            //¿Ha sido agua?
            if(resDisparo = disparo(T_Receive, T_Shoot, reg->x_maq, reg->y_maq)){
                //No ha sido agua

                //¿Lo ha hundido?
                if(resDisparo == 2) reg->flagEncontrado_maq = false;
            }else{
                //Si ha sido agua
                rotar(&orientAux, G180, DERECHA); //Indistinto derecha o izquierda
                do{
                    moverAOrientacion(T_Receive, orientAux, &xAux, &yAux);
                    if(devolverCasilla(T_Shoot, xAux, yAux) != ' '){
                        flagValidPosition = true;
                    }
                }while(!flagValidPosition); //Técnicamente no es necesario aquí las variables aux

                moverAOrientacion(T_Receive, reg->orient_maq, &xAux, &yAux);
                reg->x_maq = xAux;
                reg->y_maq = yAux;
                reg->orient_maq = orientAux;
                //Se preparan las coordenadas para que la próxima iteración dispare al barco
            }
        
            
        }
    }
}


void disparoManual(Tablero *t, Registro_Maquina *reg_maq){
    //Inicializa coordenadas y si la coordenada es válida
    int x=0, y=0;
    int flagValidPosition = false;

    do{
        
        puts("Introduce unas coordenadas (X,Y) para disparar.");
        scanf("%i %i",&x, &y);
        
            if(x > 0 && x <= t->maxLado && y > 0 && y <= t->maxLado) {
            //Verificar que la casilla no haya sido disparada antes
                if(t->casillas[x][y] == ' ') { 
                    flagValidPosition = 1;
                } else {

                    printf("Ya has disparado a esta posición (%d,%d). Intenta otra.\n", x, y);
                
                }
            } else {
                puts("Coordenadas no válidas. Deben estar dentro del rango del tablero.");
            }
        }while(flagValidPosition!=1);

        //Guarda las coordenadas en el registro
        reg_maq->x_maq=x;
        reg_maq->y_maq=y;
}



void disparo_menu(Jugador *j,Tablero *t, Registro_Maquina *reg_maq){
    
    int resultado_disparo;
    int x,y;
    int long_barco=0;

    if(j->Tipo_disparo=='M'){
        
        disparoManual(t,reg_maq);
        
    }
    else{ //Bloque de disparo automático

            srand(time(NULL));              //Semilla generada a partir de la hora actual    
            dispararAleatorio(&j->Tablero_flota,&j->Tablero_oponente, reg_maq);
    
        }
        //Recupera las coordenadas guardadas de otras funciones
    x=reg_maq->x_maq;
    y=reg_maq->y_maq;

            if (devolverCasilla(t,reg_maq->x_maq,reg_maq->y_maq)=='X'){//Caso de que haya tocado un barco


                printf("¡¡Has acertado!!");
                reg_maq->esAgua=false;


                //recorrerBarco(&j->Tablero_flota,&j->Tablero_oponente,x,y);

                //Recorre el barco para comprobar si está hundido o solo tocado
                // while(devolverCasilla(t,reg_maq->x_maq,reg_maq->y_maq)!='*'){
                    
                    
                //     moverAOrientacion(t, reg_maq->orient_maq, &reg_maq->x_maq, &reg_maq->y_maq);


                // }
                // //Dar media vuelta para rellenar casillas
                // int orient_op;//Variable para guardar la dirección opuesta
                // if(reg_maq->orient_maq<=4){

                //     orient_op=reg_maq->orient_maq+4;//Si la orientación no es mayor de 180º, suma 180ª para dar la vuelta

                // }else{

                //     orient_op=reg_maq->orient_maq-4;//Si la orientación es mayor de 180º, resta 180ª para dar la vuelta

                // }
                
                // //Volver a recorrerlo para ver su longitud
                // while(devolverCasilla(t,reg_maq->x_maq,reg_maq->y_maq)!='*'){
                    
                    
                //     moverAOrientacion(reg_maq->orient_maq, &reg_maq->x_maq, &reg_maq->y_maq);
                //     long_barco++;

                // }

                // //Vuelve a dar media vuelta
                // if(reg_maq->orient_maq<=4){

                //     orient_op=reg_maq->orient_maq+4;//Si la orientación no es mayor de 180º, suma 180ª para dar la vuelta

                // }else{

                //     orient_op=reg_maq->orient_maq-4;//Si la orientación es mayor de 180º, resta 180ª para dar la vuelta

                // }
                
                // for(int i=0; i<long_barco; i++){


                //     moverAOrientacion(reg_maq->orient_maq, &reg_maq->x_maq, &reg_maq->y_maq);

                //     if(devolverCasilla(t,reg_maq->x_maq,reg_maq->y_maq)==' '){

                //         resultado_disparo=TOCADO;
                //         i=long_barco;
                //     }
                //     else{

                //         resultado_disparo=HUNDIDO;

                //     }
                // }

                if (!recorrerBarco(&j->Tablero_flota,&j->Tablero_oponente,x,y)){//El barco solo está tocado
                colocarCasilla('T', t, reg_maq->x_maq, reg_maq->y_maq);
                    printf("_ _____                   _       _ \n");
                    printf("(_)_   _|__   ___ __ _  __| | ___ | |\n");
                    printf("| | | |/ _ \\ / __/ _` |/ _` |/ _ \\| |\n");
                    printf("| | | | (_) | (_| (_| | (_| | (_) |_|\n");
                    printf("|_| |_|\\___/ \\___\\__,_|\\__,_|\\___/(_)\n");
                    printf("¡Has tocado un barco!\n");

                sleep(3);
                system("cls");
                mostrarOponente(j);
                }
            
            else{//Caso de que barco esté hundido
                    
                    // //Recorrer barco hasta el inicio de este
                    // while(devolverCasilla(t,reg_maq->x_maq,reg_maq->y_maq)!='*'){
                    
                    
                    //     moverAOrientacion(reg_maq->orient_maq,, &reg_maq->x_maq, &reg_maq->y_maq);


                    // }
                    // //Dar media vuelta para rellenar casillas
                    // int orient_op;//Variable para guardar la dirección opuesta
                    // if(reg_maq->orient_maq<=4){

                    //     orient_op=reg_maq->orient_maq+4;//Si la orientación no es mayor de 180º, suma 180ª para dar la vuelta

                    // }else{

                    //     orient_op=reg_maq->orient_maq-4;//Si la orientación es mayor de 180º, resta 180ª para dar la vuelta

                    // }

                    do{//Rellenar el barco con H
                    
                        moverAOrientacion(&j->Tablero_oponente,reg_maq->orient_maq, &reg_maq->x_maq, &reg_maq->y_maq);

                        if(devolverCasilla(t,reg_maq->x_maq,reg_maq->y_maq)!='*'){ //Doble seguridad para que no se rellenen casillas de más
                        colocarAdyacentes(t, reg_maq->x_maq, reg_maq->y_maq, '*', 'H');
                        colocarAdyacentes(t, reg_maq->x_maq, reg_maq->y_maq, 'H', '*');
                        }
                    }while(devolverCasilla(t,reg_maq->x_maq,reg_maq->y_maq)!='*');

                system("cls");
                printf("░█░█░█░█░█▀█░█▀▄░▀█▀░█▀▄░█▀█░█\n");
                printf("░█▀█░█░█░█░█░█░█░░█░░█░█░█░█░▀\n");
                printf("░▀░▀░▀▀▀░▀░▀░▀▀░░▀▀▀░▀▀░░▀▀▀░▀\n");
                printf("¡Has hundido un barco!\n");
                sleep(3);
                system("cls");

                j->barcos_restantes--;

                mostrarOponente(j);

                
            }
            }else{
                reg_maq->esAgua=true;
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

    ControlPartida ControlPartida_L;
    ControlPartida_L = cargar_controlPartida();

//Estructuras de los jugadores
Jugador *j1= &ControlPartida_L.jugador1;
Jugador *j2= &ControlPartida_L.jugador2;

int x_maq, y_maq; //nota: variables bien inicializadas?
int orient_maq=-1;
int flagEncontrado_maq=false;

//Cargamos los datos guardados en la configuración en la estructura de los jugadores
cargar_jugador(&j1, ConfiguracionJuego_L, 1);
cargar_jugador(&j2, ConfiguracionJuego_L, 2);

char eleccion_barco_j1, eleccion_barco_j2;
//Elección de colocar barcos

    f_eleccion_barcos(&j1,Vector_Barcos_L,eleccion_barco_j1);
    f_eleccion_barcos(&j2,Vector_Barcos_L,eleccion_barco_j2);
    
    //int opcion_salir; //Variable booleana
    int id = j1->Id_jugador; //Comienza siempre el jugador 1

    flujoPartida(ConfiguracionJuego_L, &reg_maquina, ControlPartida_L);
}

void flujoPartida(ConfiguracionJuego ConfiguracionJuego_L, Registro_Maquina *reg_maquina, ControlPartida ControlPartida){

    //int opcion_salir = ControlPartida.opcion_salir; //Variable booleana
    int id = 1;//ControlPartida.id; //Recupera el turno que tocaba en la partida
    Jugador j1 = ControlPartida.jugador1;
    Jugador j2 = ControlPartida.jugador2;

    do{ //Bucle principal del juego
    if(!j2.Ganador||!j1.Ganador){ //¿Ya hay ganador?

        if(id==1) //¿De quién es el turno?
            f_turno(&j1, &reg_maquina, &ControlPartida);
        else
            f_turno(&j2, &reg_maquina, &ControlPartida);

    }else{

        if(id==2) //¿Posible empate?
            
            f_turno(&j2, &reg_maquina, &ControlPartida);

        }
        fin_partida(ConfiguracionJuego_L,ControlPartida);
    
    }while(ControlPartida.opcion_salir);


salir_partida(ConfiguracionJuego_L, ControlPartida);

}


void f_turno(Jugador* j, Registro_Maquina *reg_maq, ControlPartida *ControlPartida){

    int *id = ControlPartida->id;
    int *opcion_salir = ControlPartida->opcion_salir;

    Tablero tablero = j->Tablero_oponente;


    printf("Es el turno de %s\n", j->Nomb_jugador);
    sleep(3);
    system("cls");
    
    do{
        
        disparo_menu(j,&j->Tablero_oponente, reg_maq);
    }while(reg_maq->esAgua!=true);//Repetir el disparo en caso de acertar

    //Gana en este turno?
    if(j->barcos_restantes==0)
        j->Ganador=true;

    *id = (*id==1) ? 2 : 1; //Cambio de turno (id == identificador jugador)
    
    printf("¿Quieres continuar(Pulsa la opción que desees)?:\nSí: [1]\nNo: [0]");
    do{

        scanf("%i", &opcion_salir);
        
    }while((*opcion_salir!=0)&&(*opcion_salir!=1));

}

void salir_partida(ConfiguracionJuego ConfiguracionJuego, ControlPartida ControlPartida){

    //guardar turno
    guardar_jugadores(ControlPartida.jugador1,ControlPartida.jugador2,&ConfiguracionJuego);
    guardar_config(ConfiguracionJuego);
    MenuPrincipal();

}

void fin_partida(ConfiguracionJuego config, ControlPartida ControlP){


    int nVacias[2], nAgua[2], nTocado[2], nHundido[2];
    //recorre el tablero en busca de *, T y H
    buscarNcasillas(config.Tablero_oponente1,&nVacias[0],' ');
    buscarNcasillas(config.Tablero_oponente1,&nAgua[0],'*');
    buscarNcasillas(config.Tablero_oponente1,&nTocado[0],'T');
    buscarNcasillas(config.Tablero_oponente1,&nHundido[0],'H');

    buscarNcasillas(config.Tablero_oponente1,&nVacias[1],' ');
    buscarNcasillas(config.Tablero_oponente2,&nAgua[1],'*');
    buscarNcasillas(config.Tablero_oponente2,&nTocado[1],'T');
    buscarNcasillas(config.Tablero_oponente2,&nHundido[1],'H');


    MenuJuego();

}

void resumen_partida(ConfiguracionJuego config, ControlPartida ControlP){
    
    
    int nVacias[2], nAgua[2], nTocado[2], nHundido[2];
    //recorre el tablero en busca de *, T y H
    buscarNcasillas(config.Tablero_oponente1,&nVacias[0],' ');
    buscarNcasillas(config.Tablero_oponente1,&nAgua[0],'*');
    buscarNcasillas(config.Tablero_oponente1,&nTocado[0],'T');
    buscarNcasillas(config.Tablero_oponente1,&nHundido[0],'H');

    buscarNcasillas(config.Tablero_oponente1,&nVacias[1],' ');
    buscarNcasillas(config.Tablero_oponente2,&nAgua[1],'*');
    buscarNcasillas(config.Tablero_oponente2,&nTocado[1],'T');
    buscarNcasillas(config.Tablero_oponente2,&nHundido[1],'H');
    
        printf("+----------------------+-----------+------------+------------+------------+------------+------------+------------+------------+\n");
        printf("|    Valor de las casillas                                                |    Barcos    |\n");
        printf("+----------------------+-----------+------------+------------+------------+------------+------------+------------+------------+\n");
        printf("| Jugador   | Disparos | Vacías    | Agua       | Tocadas    | Hundidas   | Hundidos   | Restan     | Ganador    |\n");
        printf("+-----------+----------+-----------+------------+------------+------------+------------+------------+------------+\n");
        
        // Datos de los jugadores
        printf("| Jugador1  |   %d     |   %d      |   %d       |   %d       |   %d       |   %d       |   %d       |   %d       |\n",ControlP.jugador1.Num_disparos,nVacias[0],nAgua[0],nTocado[0],nHundido[0],config.Tama_flota-ControlP.jugador2.barcos_restantes,ControlP.jugador1.barcos_restantes,ControlP.jugador1.Ganador);
        printf("+-----------+----------+-----------+------------+------------+------------+------------+------------+------------+\n");
        printf("| Jugador2  |   %d     |   %d      |   %d       |   %d       |   %d       |   %d       |   %d       |   %d       |\n",ControlP.jugador2.Num_disparos,nVacias[1],nAgua[1],nTocado[1],nHundido[1],config.Tama_flota-ControlP.jugador1.barcos_restantes,ControlP.jugador2.barcos_restantes,ControlP.jugador2.Ganador);
        printf("+-----------+----------+-----------+------------+------------+------------+------------+------------+------------+\n\n");
    
        sleep(8);//Cambiar por "pulse para mostrar lo siguiente"

        printf("Jugador 1: \n");
        mostrarFlota(&ControlP.jugador1);
        mostrarOponente(&ControlP.jugador1);

        sleep(8);


        printf("Jugador 2: \n");
        mostrarFlota(&ControlP.jugador2);
        mostrarOponente(&ControlP.jugador2);

    sleep(8);

    MenuJuego();    

}


void buscarNcasillas(Tablero t, int *valor, char c){

    valor=0;
    for(int i=0; i++; i<=t.maxLado){

        for(int j=0; j++; j<=t.maxLado)
            if(t.casillas[i][j]==c){valor++;}

    }

}

void f_eleccion_barcos(Jugador *pj, Vector_Barcos vectBarcos, char eleccion_barco){

        printf("%s: Introduce un carácter para elegir modo de colocación de barcos\n", pj->Nomb_jugador);
        int flag_valid_b=0;
        do{

            printf("'M' == Manual    'A' == Automático");
            scanf("%c",&eleccion_barco);
            if(eleccion_barco == 'm')
                eleccion_barco = 'M';
                
            if (eleccion_barco == 'a')
                eleccion_barco ='A';


            switch (eleccion_barco)
            {
            case 'M':
                colocarManual(pj,vectBarcos);
                flag_valid_b=1;
                break;


            case 'A':
                colocarAleatorio(pj);
                flag_valid_b=1;
                break;

            default:
                printf("No se reconoce el carácter\n");
                flag_valid_b=0;
                break;
            }
        }while(!flag_valid_b);
}




//FUNCIONES DE CARGADO Y GUARDADO

void cargar_jugador(Jugador *j, ConfiguracionJuego config, int id){

    j->Id_jugador = id;


    if (id == 1){//Copia los datos de J1 en la estructura de J1
        
        strcpy(j->Nomb_jugador,config.Nomb_J1);
        j->Tipo_disparo=config.Tipo_disparo_J1;
        j->Tablero_flota = config.Tablero_flota1;
        j->Tablero_oponente = config.Tablero_oponente1;
        j->barcos_restantes = config.Tama_flota;
    
    }
    else{//Copia los datos de J2 en la estructura de J2
        
        strcpy (j->Nomb_jugador,config.Nomb_J2);
        j->Tipo_disparo=config.Tipo_disparo_J2;
        j->Tablero_flota = config.Tablero_flota2;
        j->Tablero_oponente = config.Tablero_oponente2;
        j->barcos_restantes = config.Tama_flota;

    }
     
}

void guardar_jugadores(Jugador j1, Jugador j2, ConfiguracionJuego *config){

    config->Tablero_flota1 = j1.Tablero_flota;
    config->Tablero_flota2 = j2.Tablero_flota;

    config->Tablero_oponente1 = j1.Tablero_oponente;
    config->Tablero_oponente2 = j2.Tablero_oponente;

    //guardar n de disparos

}


ControlPartida cargar_controlPartida(){
    ControlPartida ControlPartida;
    ControlPartida.jugador1.Ganador = 0;
    ControlPartida.jugador2.Ganador = 0;
    ControlPartida.jugador1.Num_disparos = 0;
    ControlPartida.jugador2.Num_disparos = 0;
    ControlPartida.id = 1;
    ControlPartida.opcion_salir = -1;
    return ControlPartida;
}

void guardar_controlPartida(ControlPartida ControlPartida){


    //guardar id del turno que corresponde (fichero?)



}
