#include "Tablero.h"

//TODO: ESTRUCTURA DE POSICION DE BARCOS + ORIENTACION MATRIZ DE 3 COLUMNAS

static void mostrarTablero(Tablero* t);
static int barcoSeleccionado(Vector_Barcos* vect, int* nBarcosRestantes);
static void compactarVector(Vector_Barcos* vect, int barcoSeleccionado, int nBarcos);
static void colocacionBarco(Barco B, Jugador* j);

inline static void jump(int j){for(int i=0; i<j; i++) printf("\n");}


Tablero* crearTablero(int maxLado)
{
    Tablero* t = malloc(sizeof(Tablero));
    if(!t){
        printf("ERROR DE MEMORIA", stderr);
        free(t);
        return NULL;
    }
    //Reservar memoria para maxLado
    t->casillas = malloc(maxLado * sizeof(char*));
    if(!t->casillas){
        printf("ERROR DE MEMORIA", stderr);
        free(t);
    }

    // Reservar memoria para cada fila (maxLado)
    for (int i = 0; i < maxLado; i++) {
        t->casillas[i] = malloc(maxLado * sizeof(char));
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
    for(int i = 0 ; i < maxLado ; ++i)
        for(int j = 0 ; j < maxLado ; ++j)
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
    //Se recorre el tablero y se imprime cada casilla (Tablero cuadrado)
    for(int j=0; j < t->maxLado; ++j){
        for(int i=0; i < t->maxLado; ++i){

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

int respuesta(char c)
{
    if(c == 'Y' || c == 'y'){
        return 1;
    }else{
        if(c == 'N' || c == 'n')
            return 0;
        else{
            printf("\nRespuesta invalida. Pruebe de nuevo: ");
            scanf("%c", &c);
            return respuesta(c);
        }
    }
}

    //IMPORTANTE PASAR EL VECTOR DE BARCOS POR VALOR O EN SU DEFECTO HACER UNA COPIA.
void colocarManual(Jugador* j, Vector_Barcos vect, ConfiguracionJuego c)
{
    char charBuffer;
    int nBarcosRestantes = c->tam_flota;
    int barcoSelect;
    int flagColocado = true;
    
    printf("\n\nCOLOCA TU FLOTA %s\n------------------------\n\n", j->Nomb_Jugador);
    printf("Modo de colocacion: \n\nEn primer lugar elige el barco a colocar de los ya preestablecidos con 'Y' y pasa al siguiente con 'N'\n\n");
    printf("Una vez seleccionado, se te mostrara el tablero.\n");
    printf("Este icono: '%c' es la casilla en la que te ubicas actualmente.\n Este icono: '%c' son las casillas que ocupará tu barco.\n\n", 178, 176);
    printf("Pulsa las siguientes teclas para moverte por el tablero y cambiar la dirección del barco:\n\n");
    printf("A: Moverte una casilla a la izq\nW: Moverte una casilla hacia arriba\nS: Moverte una casilla a la derecha\nD: Moverte una casilla hacia abajo\n\n");
    printf("J: Girar 90 g. a la izquierda\nL: Girar 90 g. a la derecha\nI: Girar 45 g. a la izquierda\nK: Girar 45 g. a la derecha\n\n");
    printf("Pulse [Y] para ir al menú de selección de barco. Pulse [N] para salir.");
    
    scanf("%c", &charBuffer);
    if(!respuesta(charBuffer)) return; //Si se responde N se sale;

    while(barcoSelect = barcoSeleccionado(&vect, &nBarcosRestantes) && flagColocado){
        flagColocado = colocacionBarco(vect->Barcos[barcoSelect], j);
    }

}


/*CASOS CONFLICTIVOS:
    - Posición inicial válida para barco B
    - Posición inicial válida pero encerrada, posiciones adyacentes no válidas.
        - Tecla para buscar aleatoriamente posición válida?
    - Tecla no válida.
    - N para salir?
    - No existe posición válida.
*/
static int colocacionBarco(Barco B, Jugador* j)
{
    srand(time(NULL));
    int x, y;
    
    //charOutBuffer: Caracteres que recibimos del tablero para guardarlos.
    //charInBuffer: Buffer para colocar los caracteres en el tablero.
    int charInBuffer, charOutBuffer;

    //ENCONTRAR HUECO POSIBLE PARA BARCO B

    {
        jump(30);
        printf("Pulsa las siguientes teclas para moverte por el tablero y cambiar la dirección del barco:\n\n");
        printf("A: Moverte una casilla a la izq\nW: Moverte una casilla hacia arriba\nS: Moverte una casilla a la derecha\nD: Moverte una casilla hacia abajo\n\n");
        printf("J: Girar 90 g. a la izquierda\nL: Girar 90 g. a la derecha\nI: Girar 45 g. a la izquierda\nK: Girar 45 g. a la derecha\n\n");


        charOutBuffer = devolverCasilla(j, FLOTA, x, y);
        charInBuffer = (char)178;

    }

}


int verificarEspacio(Tablero* T, Barco B, int orientacion, int x, int y)
{
    int flagStop = false;
    switch(orientacion){

        case G0: 
            if(x + B.tam_barco - 1 <= T->maxLado) flagStop = true;
            while(!flagStop && x < T->maxLado){
                if(T->casillas[x][y] != ' ') flagStop = true;

                x++;
            }
        break;
        
        case G45:
            if(x + B.tam_barco - 1 <= T->maxLado && y + B.tam_barco - 1 <= T->maxLado) flagStop = true;
            while(!flagStop && x < T->maxLado && y < T->maxLado){
                if(T->casillas[x][y] != ' ') flagStop = true;

                x++; y++;
            }
        break;

        //!!
        case G90:
            if(y + B.tam_barco - 1 <= T->maxLado) flagStop = true;
            while(!flagStop && x < T->maxLado && y < T->maxLado){
                if(T->casillas[x][y] != ' ') flagStop = true;

                y++;
            }
        break;

        case G135:
        if(x - B.tam_barco - 1 >= 0 && y + B.tam_barco - 1 <= T->maxLado) flagStop = true;
            while(!flagStop && x < T->maxLado && y < T->maxLado){
                if(T->casillas[x][y] != ' ') flagStop = true;

                x--; y++;
            }
        break;

        case G180:
        if(x - B.tam_barco - 1 >= 0) flagStop = true;
            while(!flagStop && x < T->maxLado && y < T->maxLado){
                if(T->casillas[x][y] != ' ') flagStop = true;

                x--;
            }
        break;

        case G225:
        if(x - B.tam_barco - 1 >= 0 && y + B.tam_barco - 1 >= 0) flagStop = true;
            while(!flagStop && x < T->maxLado && y < T->maxLado){
                if(T->casillas[x][y] != ' ') flagStop = true;

                x--; y--;
            }
        break;

        case G270:
        if(y + B.tam_barco - 1 >= 0) flagStop = true;
            while(!flagStop && x < T->maxLado && y < T->maxLado){
                if(T->casillas[x][y] != ' ') flagStop = true;

                y--;
            }
        break;

        case G315:
        if(x - B.tam_barco - 1 <= T->maxLado && y + B.tam_barco - 1 >= 0) flagStop = true;
            while(!flagStop && x < T->maxLado && y < T->maxLado){
                if(T->casillas[x][y] != ' ') flagStop = true;

                x++; y--;
            }
        break;
        }

        

    return !flagStop;
}

void devolverCoordenadasLibres(Tablero* T, int* x, int* y)
{
    int flagEncontrado = 0;

    for(*x ; *x < T->maxLado && !flagEncontrado ; x++)
        for(*y ; *y < T->maxLado && !flagEncontrado; y++)
            flagEncontrado = (T->casillas[*x][*y] == ' ') ? 1 : 0;

    if(!flagEncontrado){
        *x = -1;
        *y = -1;
    }
}

inline int isLibre(Tablero* T, int x, int y){return T->casillas[x][y] == ' ';}

static int barcoSeleccionado(Vector_Barcos* vect, int* nBarcosRestantes)
{
    char charBuffer;

    //Si no quedan barcos, devuelve 0
    if(!nBarcosRestantes)
        return 0;
    //Si aún quedan entra en la selección
    else{
        printf("\nSelección de Barco, quedan %d por elegir.\n\nPulse la tecla indicada para seleccionar el barco. [N] para salir.\n\n", nBarcosRestantes);
        //Listado de los barcos restantes en el vector
        for(int i=0; i<nBarcosRestantes; i++)
            printf("[%d]: %s\n", i, vect->Barcos[i]->Nomb_Barco);    
        
        //Se registra la tecla. Si es N/n termina la selección.
        scanf("%c", &charBuffer);
        if(charBuffer == 'N' || charBuffer == 'n') return 0;

        //Si la tecla está entre los valores validos, se selecciona.
        if((int)charBuffer >= 0 && (int)charBuffer < nBarcosRestantes){
            printf("\nSe ha seleccionado %c: %s", charBuffer, vect->Barcos[(int)charBuffer]->Nomb_barco);

            //Se quita el barco seleccionado del vector.
            compactarVector(vect, (int)charBuffer, nBarcosRestantes);

            nBarcosRestantes--;
            //Devuelve el id del barco
            return (int)charBuffer;
        }else 
            return 0;

    }
}

static void compactarVector(Vector_Barcos* vect, int barcoSeleccionado, int nBarcos)
{
    int barcosAMover = (nBarcos - 1) - barcoSeleccionado;
    //Se machaca el valor de i con el siguiente hasta el penúltimo elemento
    for(int i=barcoSeleccionado ; i < barcosAMover - 1 ; i++)
        vect[i] = vect[i+1];

    //Se reajusta el vector a un elemento menos, machacandose el último elemento
    vect = (Vector_Barcos*) realloc(vect, nBarcos-1);
}


void colocarAleatorio(Jugador* j, Vector_Barcos vect)
{
    srand(time(NULL));
    int x, xIni, yIni, y, orient;
    int i = 0;
    int flagErrorColocacion = false;
    int flagColocado = false;
    int nBarcos = vect.tam;
    int tamTableroMax = j->Tablero_flota->maxLado;

    //Mientras haya barcos, los coloca
    while(nBarcos){
        flagColocado = false;
        //Mientras no se coloque elige una nueva coordenada y prueba
        while(!flagColocado){
            xIni = x = 0 + rand() % tamTableroMax;
            yIni = y = 0 + rand() % tamTableroMax;
            orient = 0 + rand() % (G315 + 1); //Orientación entre 0 y 7
            
            flagErrorColocacion = false;
            //Mientras no se verifique entero, no haya error de colocación y x e y estén dentro del tablero
            
                if(!verificarEspacio(j->Tablero_flota, vect->Barcos[nBarcos-1], orient, x, y)) flagErrorColocacion = true;

            if(!flagErrorColocacion){
                i = 0;
                x = xIni; y = yIni;
                while(i != vect->Barco->Tam_Barco){
                    i++;
                    //Se coloca cómo casilla el tamaño del barco en carácter.
                    colocarCasilla(vect->Barco->Tam_Barco + 48, j, FLOTA, x, y);
                    switch(orient){
                        case G0:
                            x++;
                        break;

                        case G45:
                            x++; y++;
                        break;
                        
                        case G90:
                            y++;
                        break;

                        case G135:
                            x--; y++;
                        break;

                        case G180:
                            x--;
                        break;

                        case G225:
                            x--; y--;
                        break;

                        case G270:
                            y--;
                        break;

                        case G315:
                            x++; y--;
                        break;
                    }
                
                }
                nBarcos--;
                flagColocado = true;
            }
        }
    }

    mostrarFlota(j);
}

inline char devolverCasilla(Jugador* j, int tablero, int x, int y) {return (tablero)? j->oponente->casillas[x][y] : j->flota->casillas[x][y];}

inline void colocarCasilla(char c, Jugador* j, int tablero, int x, int y){
    if(tablero){
        j->oponente->casillas[x][y] = c;
    }else{
        j->flota->casillas[x][y] = c;
    }
}

