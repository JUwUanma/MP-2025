#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h> //Para la función toupper()
#include <windows.h> //Sleep(tiempo)
#include "logica.h"
#include "..\\ModuloMemoria\Datos.h"
#include "..\\ModuloTablero\Tablero.h"
#include "..\\ModuloInterfaz\Interfaz.h"
/*P: Tablero existe, y orient es la orientación del barco, x, y dentro de tablero
Q: Devuelve true si la casilla se encuentra en un extremo del barco, es decir,
en la orientación dada, hay una casilla en un sentido y no en el contrario.*/
static int isExtremo(Tablero* T_Flota, int x, int y, int orient);

static int isExtremo(Tablero* T_Flota, int x, int y, int orient)
{
    int xIni = x, yIni = y;
    char charBuffer1, charBuffer2;

    moverAOrientacion(&T_Flota, orient, &x, &y);

    if(x == xIni || y == yIni) return true; //Si no se ha modificado la posición, es que está en un extremo

    charBuffer2 = devolverCasilla(&T_Flota, x, y);

    rotar(&orient, G180, IZQUIERDA);
    moverAOrientacion(&T_Flota, orient, &xIni, &yIni);

    if(x == xIni || y == yIni) return true; //Si no se ha modificado la posición, es que está en un extremo

    charBuffer2 = devolverCasilla(&T_Flota, xIni, yIni);

    /*
    NAND
    * *: true
    * X: true
    X *: true
    X X: false
    */
    return !((charBuffer1 == 'X') && (charBuffer2 == 'X'));
}

int disparo(Tablero* T_Receive, Tablero* T_Shoot, int x, int y)
{
    char charBuffer = devolverCasilla(T_Receive, x, y); //Buffer para no llamar a la función dos veces
    int resBarco;

    if(charBuffer == ' ' || charBuffer == '0'){ //Si está vacía (o casilla ocupada) devuelve AGUA
        resBarco = AGUA;

    }else{//Sino, recorre el barco, si se ha recorrido por completo -> HUNDIDO, sino -> TOCADO
        colocarCasilla('T', T_Shoot, x, y);
        resBarco = recorrerBarco(T_Receive, T_Shoot, x, y) ? HUNDIDO : TOCADO;

        //Si lo ha hundido, hay que marcarlo como tal en T_Shoot
        if(resBarco == HUNDIDO){
            int xBarco, yBarco, orientBarco;
            orientBarco = encontrarOrientacion(&T_Receive, xBarco, yBarco); //Encuentra la orientación del barco
            encontrarExtremo(&T_Receive, &xBarco, &yBarco, orientBarco); //Encuentra el extremo
            
            rotar(&orientBarco, G180, DERECHA);

            //Hasta que encuentre el otro extremo del barco, coloca casillas y sus adyacentes
            do{
                colocarCasilla('H', &T_Shoot, x, y);
                colocarAdyacentes(&T_Shoot, x, y, 'H', '*');
                moverAOrientacion(&T_Shoot, orientBarco, &x, &y);
                
            }while(!isExtremo(&T_Receive, x, y, orientBarco));
        }
    }

    return resBarco;
}

int encontrarOrientación(Tablero* T_Flota, int x, int y)
{
    int orient = G0;
    int xIni = x, yIni = y;
    int cont = 0; //Contador para saber si es un barco de única casilla

    moverAOrientacion(T_Flota, orient, &x, &y);

    //Mientras no encuentre la orientación del barco o, en su defecto, no la encuentra
    while(cont != (G315 + 1) && devolverCasilla(T_Flota, x, y) != 'X'){
        x = xIni; y = yIni; //Reinicia la posición
        rotar(&orient, G45, IZQUIERDA); //Rota a la siguiente orientación
        moverAOrientacion(T_Flota, orient, &x, &y);
        cont++;
    }

    if(cont == G315 + 1) return cont;
    else return orient;
}

void encontrarExtremo(Tablero* T_Flota, int* x, int* y, int orient)
{
     //¿[x,y] está en un extremo del barco?
     while(!isExtremo(T_Flota, x, y, orient)){
        moverAOrientacion(T_Flota, orient, &x, &y);
    }
}

int recorrerBarco(Tablero* T_Flota, Tablero* T_Oponente, int x, int y)
{
    int flagHundido = false;
    char charBufferFlota;
    char charBufferOpon;
//Busca la orientación del barco
    int orient = encontrarOrientación(&T_Flota, x, y); 
    if(orient == G315+1) return true;

    encontrarExtremo(&T_Flota, &x, &y, orient);
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

int dispararAleatorio(Tablero* T_Receive, Tablero* T_Shoot, Registro_Maquina* reg)
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

    return resDisparo;
}

/*TODO?: Cambiar modo de disparo a tablero visual?*/

int dispararManual(Tablero *T_Receive, Tablero* T_Shoot){
    //Inicializa coordenadas y si la coordenada es válida
    int x=0, y=0;
    int flagValidPosition = false;
    int maxLado = T_Receive->maxLado;

    do{
        
        puts("Introduce unas coordenadas (X,Y) para disparar.");
        scanf("%i %i",&x, &y);
        
            if(x > 0 && x < maxLado && y > 0 && y < maxLado){

            //Verificar que la casilla no haya sido disparada antes
                if(verificarCasilla(&T_Shoot, x, y)) 
                    flagValidPosition = true;
                else
                    printf("Ya has disparado a esta posición (%d,%d). Intenta otra.\n", x, y);
                
            }else{
                printf("\n\nCoordenadas no válidas. Deben estar dentro del rango del tablero.\n\n");
            }
    }while(flagValidPosition!=1);

    return disparo(&T_Receive, &T_Shoot, x, y);

}

int disparo_menu(Jugador* J_Shoot, Jugador* J_Receive, Registro_Maquina *reg_maq){
    
    int resDisparo;
    int x,y;
    int long_barco=0;

    Tablero* T_Receive = &J_Receive->Tablero_flota;
    Tablero* T_Shoot = &J_Shoot->Tablero_oponente;

    if(J_Shoot->Tipo_disparo == 'M'){//Tipo de disparo del jugador
        resDisparo = disparoManual();
    }else{
        resDisparo = dispararAleatorio(&T_Receive, &T_Shoot, &reg_maq);
    }

    if (resDisparo == TOCADO){//Caso de que haya tocado un barco

        system("cls");
        printf("░▀█▀░█▀█░█▀▀░█▀█░█▀▄░█▀█░█\n");
        printf("░░█░░█░█░█░░░█▀█░█░█░█░█░▀\n");
        printf("░░▀░░▀▀▀░▀▀▀░▀░▀░▀▀░░▀▀▀░▀\n");
        printf("\n\n¡Has tocado un barco!\n");

        Sleep(3);
        system("cls");
        mostrarOponente(J_Shoot);

    }else if(resDisparo == HUNDIDO){//Caso de que barco esté hundido
            
        system("cls");
        printf("░█░█░█░█░█▀█░█▀▄░▀█▀░█▀▄░█▀█░█\n");
        printf("░█▀█░█░█░█░█░█░█░░█░░█░█░█░█░▀\n");
        printf("░▀░▀░▀▀▀░▀░▀░▀▀░░▀▀▀░▀▀░░▀▀▀░▀\n");
        printf("\n\n¡Has hundido un barco!\n");

        Sleep(3);
        system("cls");
        mostrarOponente(J_Shoot);

    }else{//Caso que fallas ):

        system("cls");
        printf("░█░█░█▀█░█▀▀░░░█▀▀░█▀█░█░░░█░░░█▀█░█▀▄░█▀█░█\n");
        printf("░█▀█░█▀█░▀▀█░░░█▀▀░█▀█░█░░░█░░░█▀█░█░█░█░█░▀\n");
        printf("░▀░▀░▀░▀░▀▀▀░░░▀░░░▀░▀░▀▀▀░▀▀▀░▀░▀░▀▀░░▀▀▀░▀\n");
        printf("\n\nHas tocado agua.\n");
        Sleep(5);
        system("cls");
        mostrarOponente(J_Shoot);

    }

    J_Shoot->Num_disparos++;
    return resDisparo; //PROVISIONAL
}

int reiniciarPartida(){

ConfiguracionJuego ConfiguracionJuego_L = cargar_config();
Vector_Barcos Vector_Barcos_L = cargar_barcos();

//Estructura dedicada a guardar datos sobre coordenadas que necesita el algoritmo para que funcione y evitar perder información vital.
Registro_Maquina reg_maquina;

//Inicialización de las variables
reg_maquina.flagEncontrado_maq=false;
reg_maquina.orient_maq=-1;
reg_maquina.x_maq=0;
reg_maquina.y_maq=0;

ControlPartida ControlPartida_L;
ControlPartida_L = cargar_controlPartida(ConfiguracionJuego_L);

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

eleccion_barco_j1=f_eleccion_barcos(&j1,Vector_Barcos_L); //Guarda la colocación de los barcos en los tableros de cada jugador
eleccion_barco_j2=f_eleccion_barcos(&j2,Vector_Barcos_L);
    
return flujoPartida(&ConfiguracionJuego_L, &reg_maquina, &ControlPartida_L);
}

int flujoPartida(ConfiguracionJuego* config, Registro_Maquina *reg_maquina, ControlPartida* partida){

    char charBuffer;
    int flagStopGame = false;
    Jugador j1 = partida->jugador1;
    Jugador j2 = partida->jugador2;

    do{ //Bucle principal del juego
        partida->id_turno = 1; //Al comenzar una ronda siempre comienza el J1

        system("cls");
        printf("\n-----RONDA %d-----\n", partida->n_ronda);
        f_turno(&reg_maquina, &partida); //Al comienzo de una ronda siempre empieza J1
        f_turno(&reg_maquina, &partida); //No importa lo que pase, siempre juega tambien J2

        //Hay un ganador? 
        if(partida->hayGanador == NO_FINALIZADA){
            printf("\nRonda terminada. ¿Quieres guardar la partida? [Y/N]\n");
            scanf("%c", &charBuffer);

            if(respuesta(charBuffer)){
                system("cls");
                printf("Guardando partida...");
                //guardarPartida();
                flagStopGame = true;
            }else{
                partida->n_ronda++;
            }

        //Hay (al menos) un ganador
        }else{
            system("cls");
            printf("-----PARTIDA TERMINADA-----\n\n");
            if(partida->hayGanador == EMPATE){
                printf("███████╗███╗   ███╗██████╗  █████╗ ████████╗███████╗██╗\n");
                printf("██╔════╝████╗ ████║██╔══██╗██╔══██╗╚══██╔══╝██╔════╝██║\n");
                printf("█████╗  ██╔████╔██║██████╔╝███████║   ██║   █████╗  ██║\n");
                printf("██╔══╝  ██║╚██╔╝██║██╔═══╝ ██╔══██║   ██║   ██╔══╝  ╚═╝\n");
                printf("███████╗██║ ╚═╝ ██║██║     ██║  ██║   ██║   ███████╗██╗\n");
                printf("╚══════╝╚═╝     ╚═╝╚═╝     ╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝\n");



            }else{

                printf("Ha ganado el jugador %d! Enhorabuena! WP\n\n", partida->hayGanador);

                printf("░█▀▀░█▀█░█░█░█▀█░█▀▄░█▀█░█▀▄░█░█░█▀▀░█▀█░█▀█░░░▀▀█░█░█░█▀▀░█▀█░█▀▄░█▀█░█▀▄░░░░\n");
                printf("░█▀▀░█░█░█▀█░█░█░█▀▄░█▀█░█▀▄░█░█░█▀▀░█░█░█▀█░░░░░█░█░█░█░█░█▀█░█░█░█░█░█▀▄░░░░\n");
                printf("░▀▀▀░▀░▀░▀░▀░▀▀▀░▀░▀░▀░▀░▀▀░░▀▀▀░▀▀▀░▀░▀░▀░▀░░░▀▀░░▀▀▀░▀▀▀░▀░▀░▀▀░░▀▀▀░▀░▀░░░░\n");
                if(partida->hayGanador==GANA_J1){

                    printf("    ▄▄▄▄     \n");
                    printf("  ▄█░░░░▌    \n");
                    printf(" ▐░░▌▐░░▌    \n");
                    printf("  ▀▀ ▐░░▌    \n");
                    printf("     ▐░░▌    \n");
                    printf("     ▐░░▌    \n");
                    printf(" ▄▄▄▄█░░█▄▄▄ \n");
                    printf("▐░░░░░░░░░░░▌\n");
                    printf(" ▀▀▀▀▀▀▀▀▀▀▀ \n");


                }else{


                    printf(" ▄▄▄▄▄▄▄▄▄▄▄ \n");
                    printf("▐░░░░░░░░░░░▌\n");
                    printf(" ▀▀▀▀▀▀▀▀▀█░▌\n");
                    printf("          ▐░▌\n");
                    printf("          ▐░▌\n");
                    printf(" ▄▄▄▄▄▄▄▄▄█░▌\n");
                    printf("▐░░░░░░░░░░░▌\n");
                    printf("▐░█▀▀▀▀▀▀▀▀▀ \n");
                    printf("▐░█▄▄▄▄▄▄▄▄▄ \n");
                    printf("▐░░░░░░░░░░░▌\n");
                    printf(" ▀▀▀▀▀▀▀▀▀▀▀ \n");


                }

            }
            flagStopGame = true;
        }
    }while(!flagStopGame);

salir_partida(&config, &partida);
return (partida->hayGanador != NO_FINALIZADA);
}

void f_turno(Registro_Maquina *reg_maq, ControlPartida *partida)
{

    int flagResShot;
    Jugador *J_Turno; //Puntero al jugador que tiene el turno
    Jugador *J_Oponente; //Puntero al jugador oponente al del turno

    if(partida->id_turno == 1){//¿De quién es el turno?
        *J_Turno = partida->jugador1;
        *J_Oponente = partida->jugador2;
    }else{
        *J_Turno = partida->jugador2;
        *J_Oponente = partida->jugador1;
    }


    printf("\n\nEs el turno de %s\n\n", J_Turno->Nomb_jugador);
    Sleep(3);
    system("cls");
    
    do{
        
        //El jugador dispara, si acierta, puede volver a disparar
        if(flagResShot = disparo_menu(&J_Turno, &J_Oponente, &reg_maq) != AGUA){
            printf("\n\n¡Has acertado! Puedes volver a disparar");
            Sleep(3);

            if(flagResShot == HUNDIDO) partida->nBarcosRestantes[partida->id_turno]--;
        }

    }while(flagResShot != AGUA);//Repetir el disparo en caso de acertar

    //Gana en este turno?
    if(partida->nBarcosRestantes[partida->id_turno] == 0){
        J_Turno->Ganador = true;
        partida->hayGanador = partida->hayGanador == 0 ? partida->id_turno : EMPATE; //Si ya ha ganado alguien y gana este turno -> EMPATE
    }

    partida->id_turno = partida->id_turno == 1 ? 2 : 1;   //Cambio de turno

}

void salir_partida(ConfiguracionJuego* ConfiguracionJuego, ControlPartida* ControlPartida){

    //guardar turno
    guardar_jugadores(&ControlPartida->jugador1, &ControlPartida->jugador2, &ConfiguracionJuego); //Guarda los jugadores en configuración
    guardar_config(*ConfiguracionJuego); //Guarda configuración en fichero
    //MenuPrincipal();

}



void resumen_partida(ConfiguracionJuego config, ControlPartida ControlP){
    char enter;
    int nVacias[2], nAgua[2], nTocado[2], nHundido[2];
    //recorre el tablero en busca de *, T y H y las guarda en los vectores
    buscarNcasillas(config.Tablero_oponente1,&nVacias[0],' ');
    buscarNcasillas(config.Tablero_oponente1,&nAgua[0],'*');
    buscarNcasillas(config.Tablero_oponente1,&nTocado[0],'T');
    buscarNcasillas(config.Tablero_oponente1,&nHundido[0],'H');

    buscarNcasillas(config.Tablero_oponente1,&nVacias[1],' ');
    buscarNcasillas(config.Tablero_oponente2,&nAgua[1],'*');
    buscarNcasillas(config.Tablero_oponente2,&nTocado[1],'T');
    buscarNcasillas(config.Tablero_oponente2,&nHundido[1],'H');
    
        printf("+----------------------+-----------+------------+------------+------------+------------+------------+------------+------------+\n");
        printf("|    Valor de las casillas                                                |    Barcos                                         |\n");
        printf("+----------------------+-----------+------------+------------+------------+------------+------------+------------+------------+\n");
        printf("| Jugador   | Disparos | Vacías    | Agua       | Tocadas    | Hundidas   | Hundidos   | Restan     | Ganador    |\n");
        printf("+-----------+----------+-----------+------------+------------+------------+------------+------------+------------+\n");
        
        // Datos de los jugadores
        printf("| Jugador1  |   %d     |   %d      |   %d       |   %d       |   %d       |   %d       |   %d       |   %d       |\n",ControlP.jugador1.Num_disparos,nVacias[0],nAgua[0],nTocado[0],nHundido[0],config.Tama_flota-ControlP.jugador2.barcos_restantes,ControlP.jugador1.barcos_restantes,ControlP.jugador1.Ganador);
        printf("+-----------+----------+-----------+------------+------------+------------+------------+------------+------------+\n");
        printf("| Jugador2  |   %d     |   %d      |   %d       |   %d       |   %d       |   %d       |   %d       |   %d       |\n",ControlP.jugador2.Num_disparos,nVacias[1],nAgua[1],nTocado[1],nHundido[1],config.Tama_flota-ControlP.jugador2.barcos_restantes,ControlP.jugador2.barcos_restantes,ControlP.jugador2.Ganador);
        printf("+-----------+----------+-----------+------------+------------+------------+------------+------------+------------+\n\n");

        printf("Pulse cualquier Enter para mostrar el siguiente apartado.\n");
        scanf("%c",enter);
        getchar();//Limpiar buffer

        limpiarPantalla();
        printf("Jugador 1: \n");
        mostrarFlota(&ControlP.jugador1);
        mostrarOponente(&ControlP.jugador1);

        limpiarPantalla();
        printf("Pulse cualquier Enter para mostrar el siguiente apartado.\n");
        scanf("%c",enter);
        getchar();

        printf("Jugador 2: \n");
        mostrarFlota(&ControlP.jugador2);
        mostrarOponente(&ControlP.jugador2);

    }

    //Busca el carácter dado en un tablero y lo guarda en el puntero al valor
void buscarNcasillas(Tablero t, int *valor, char c){

    valor=0;
    for(int i=0; i++; i<=t.maxLado){

        for(int j=0; j++; j<=t.maxLado)
            if(t.casillas[i][j]==c){valor++;}

    }

}

char f_eleccion_barcos(Jugador *pj, Vector_Barcos vectBarcos) {
    int flag_valid_b = 0;
    char input;
    char eleccion_barco;

    do {
        printf("%s: Introduce un carácter para elegir modo de colocación de barcos:\n\n[M]: Manual\n[A]: Aleatorio\n\n", pj->Nomb_jugador);
        scanf(" %c", &input); 
        
        //Convertir a mayúscula para simplificar la comparación
        char upper_input = toupper(input);
        
        switch (upper_input) {
            case 'M'://Caso de colocación de barcos manual
                colocarManual(pj, vectBarcos);
                flag_valid_b = true;
                break;
                
            case 'A'://Caso de colocación de barcos automática
                colocarAleatorio(pj);
                flag_valid_b = true;
                break;
                
            default:
                printf("No se reconoce el carácter '%c'. Por favor introduce 'M' o 'A'.\n", input);
                while (getchar() != '\n');
                flag_valid_b = false;
                break;
        }
    } while (!flag_valid_b);
    
    // Asignar el valor elegido (en mayúscula) al parámetro de salida
    eleccion_barco = toupper(input);
    return eleccion_barco;
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

void guardar_jugadores(Jugador* j1, Jugador* j2, ConfiguracionJuego *config){
//Guarda contenidos en configuración de las estructuras de jugadores
    config->Tablero_flota1 = j1->Tablero_flota;
    config->Tablero_flota2 = j2->Tablero_flota;

    config->Tablero_oponente1 = j1->Tablero_oponente;
    config->Tablero_oponente2 = j2->Tablero_oponente;

}

ControlPartida cargar_controlPartida(ConfiguracionJuego config){
//Devuelve una estructura cargada con los datos inicializados para el control de la partida
    ControlPartida ControlPartida;
    ControlPartida.jugador1.Ganador = 0;
    ControlPartida.jugador2.Ganador = 0;
    ControlPartida.jugador1.Num_disparos = 0;
    ControlPartida.jugador2.Num_disparos = 0;
    ControlPartida.id_turno = 1;
    ControlPartida.nBarcosRestantes[1] , ControlPartida.nBarcosRestantes[2] = config.Num_barcos; //!!!

    return ControlPartida;
}
