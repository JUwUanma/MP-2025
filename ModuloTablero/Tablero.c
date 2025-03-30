#include "Tablero.h"

static void mostrarTablero(Tablero* t);
static int barcoSeleccionado(Vector_Barcos* vect, int* nBarcosRestantes);
static void compactarVector(Vector_Barcos* vect, int barcoSeleccionado, int nBarcos);
static int colocacionBarco(Barco* B, Jugador* j);
static int colocarBarco(Tablero* T, Barco* B, int x, int y, int orient);

inline static void jump(int j){for(int i=0; i<j; i++) printf("\n");}
//Devuelve 1 si se ha respondido N o n, y 0 sino.
inline static int exit(char c){if(c == 'N' || c == 'n') return 1; else return 0;}
//Devuelve 1 si se ha pulsado charToCompare EN MAYÚSUCULA o en minúscula, y 0 sino.
inline static int hasPressed(char c, char charToCompare){if(c == charToCompare || c == charToCompare - 48) return 1; else return 0;}

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

    reiniciarTablero(t); //Inicializa a ' ' el tablero
    return t;

}

void reiniciarTablero(Tablero* T)
{
    for(int i = 0 ; i < T->maxLado ; ++i)
        for(int j = 0 ; j < T->maxLado ; ++j)
            T->casillas[i][j] = ' ';
}

void mostrarFlota(Jugador* j)
{
    printf("\n\nFLOTA DEL JUGADOR %d: %s\n\n---------------------", j->Nomb_jugador, j->Id_jugador);
    //Método Privado para mostrar el tablero
    mostrarTablero(&j->Tablero_flota);
}

void mostrarOponente(Jugador* j)
{
    printf("\n\nTABLERO OPONENTE DEL JUGADOR %d: %s\n\n---------------------", j->Nomb_jugador, j->Id_jugador);
    //Método Privado para mostrar el tablero
    mostrarTablero(&j->Tablero_oponente);
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

//P: Barco VERIFICADO
static int colocarBarco(Tablero* T, Barco* B, int x, int y, int orient)
{
    int tamBarco = B->Tam_barco;
    int flagValidPosition;

    //Se coloca cada casilla hasta completar el barco
    for(int i = 0; i < tamBarco; i++){
        colocarCasilla('X', T, x, y); //Se coloca X en [x,y]
        colocarAdyacentes(T, x, y, 'X', '0'); //Coloca los adyacentes '0'
        moverAOrientacion(orient, x, y); //Se mueve a la siguiente casilla
    }
}

void colocarAdyacentes(Tablero* T, int x, int y, char charToIgnore, char charToPlace)
{
    int xIni = x; int yIni= y;

    for(int i = G0; i < G315 + 1; i++){
        moverAOrientacion(i, x, y);

        //Si está dentro del tablero
        if(x >= 0 && x < T->maxLado && y >=0 && y < T->maxLado){ 
            //Si no es el caracter a ignorar se coloca
            if(!devolverCasilla(T, x, y) == charToIgnore){
                colocarCasilla(charToPlace, T, x, y);
            }
        }
        rotar(i, G45, IZQUIERDA); //Sentido antihorario
        x = xIni; y = yIni;
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

void colocarManual(Jugador* j, Vector_Barcos vect)
{
    char charBuffer;
    int nBarcosRestantes = vect.tam;
    int barcoSelect;
    int flagColocado = true;
    
    printf("\n\nCOLOCA TU FLOTA %s\n------------------------\n\n", j->Nomb_jugador);
    printf("Modo de colocacion: \n\nEn primer lugar elige el barco a colocar de los ya preestablecidos con 'Y' y pasa al siguiente con 'N'\n\n");
    printf("Una vez seleccionado, se te mostrara el tablero.\n");
    printf("Este icono: '%c' es la casilla en la que te ubicas actualmente.\n Este icono: '%c' son las casillas que ocupará tu barco.\n\n", 178, 176);
    printf("Pulsa las siguientes teclas para moverte por el tablero y cambiar la dirección del barco:\n\n");
    printf("A: Moverte una casilla a la izq\nW: Moverte una casilla hacia arriba\nS: Moverte una casilla a la derecha\nD: Moverte una casilla hacia abajo\n\n");
    printf("J: Girar 90 g. a la izquierda\nL: Girar 90 g. a la derecha\nI: Girar 45 g. a la izquierda\nK: Girar 45 g. a la derecha\n\n");
    printf("Pulse [Y] para ir al menú de selección de barco. Pulse [N] para salir.");
    
    //Recoje la tecla pulsada
    scanf("%c", &charBuffer);
    if(!respuesta(charBuffer)) {
        printf("\nSaliendo del programa...\n\n");
        return;
    } //Si se responde N se sale;

    while((barcoSelect = barcoSeleccionado(&vect, &nBarcosRestantes)) != -1 && flagColocado){
        flagColocado = colocacionBarco(&vect.Barcos[barcoSelect], j);
    }

    //Guardar tablero?

}

//Devuelve la id del vector de barcos seleccionado y elimina el barco del vector, --nBarcosRestantes
//Si no hay barcos restantes, o el caracter introducido no es válido devuelve -1, 
static int barcoSeleccionado(Vector_Barcos* vect, int* nBarcosRestantes)
{
    char charBuffer;

    //Si no quedan barcos, devuelve 0
    if(!nBarcosRestantes)
        return -1;
    //Si aún quedan entra en la selección
    else{
        printf("\nSelección de Barco, quedan %d por elegir.\n\nPulse la tecla indicada para seleccionar el barco. [N] para salir.\n\n", nBarcosRestantes);
        //Listado de los barcos restantes en el vector
        for(int i=0; i<nBarcosRestantes; i++)
            printf("[%d]: %s\n", i, vect->Barcos[i].Nomb_barco);    
        
        //Se registra la tecla. Si es N/n termina la selección.
        scanf("%c", &charBuffer);
        if(charBuffer == 'N' || charBuffer == 'n'){
            printf("\nSaliendo de la selección...\n\n");
            return -1;
        }

        //Si la tecla está entre los valores validos, se selecciona.
        if((int)charBuffer >= 0 && (int)charBuffer < nBarcosRestantes){
            printf("\nSe ha seleccionado %c: %s", charBuffer, vect->Barcos[(int)charBuffer].Nomb_barco);

            //Se quita el barco seleccionado del vector.
            compactarVector(vect, (int)charBuffer, nBarcosRestantes);

            nBarcosRestantes--;
            //Devuelve el id del barco
            return (int)charBuffer;
        }else 
            printf("\nTecla NO válida\n\n");
            return barcoSeleccionado(vect, nBarcosRestantes);

    }
}

//Devuelve 1 si se ha colocado el barco B, devuelve 0 si se ha salido del menú o se han acabado los intentos.
static int colocacionBarco(Barco* B, Jugador* j)
{
    srand(time(NULL));
    int contStress;
    int x, xIni, y, yIni, orient, orientIni;
    
    //Buffer para colocar los caracteres en el tablero.
    char charInBuffer;
    //Caracteres que recibimos del tablero para guardarlos.
    char charOutBuffer;
    //Buffer de entrada del usuario
    char charBuffer;
    //Flag para reiniciar la posición hacia una aleatoria.
    int flagRestart;
    //Flag para comprobar que se ha colocado el barco.
    int flagPlaced;

        //Mientras no escoja reiniciar posición
        do{ //while(flagRestart)
            flagRestart = false;
            contStress = 0;
            //Escoge una posición aleatoria y la verifica para el barco B, si no es válida se repite.
            do{ //while (!verificarEspacio())
                xIni = x = 0 + rand() % j->Tablero_flota.maxLado;
                yIni = y = 0 + rand() % j->Tablero_flota.maxLado;
                orientIni = orient = 0 + rand() % G315 + 1;
                contStress++;

            }while(!verificarEspacio(&j->Tablero_flota, &B, orient, x, y) && contStress < MAX_RANDOM_TRIES);

            if(contStress >= MAX_RANDOM_TRIES){
                printf("\n\n\nERROR | POSICIÓN VALIDA NO ENCONTRADA\n\n\n", stderr);
                return 0;
            }
            //Mientras no se coloque CORRECTAMENTE
            do{ //while(!flagPlaced)
                    flagPlaced = false;

                //Mensaje previo al tablero
                jump(30);
                printf("Pulsa las siguientes teclas para moverte por el tablero y cambiar la dirección del barco: [ENTER] para colocar, [R] para reiniciar posición, [N] para salir:\n\n");
                printf("A: Moverte una casilla a la izq\nW: Moverte una casilla hacia arriba\nS: Moverte una casilla a la derecha\nD: Moverte una casilla hacia abajo\n\n");
                printf("J: Girar 90 g. a la izquierda\nL: Girar 90 g. a la derecha\nI: Girar 45 g. a la izquierda\nK: Girar 45 g. a la derecha\n\n");

                //Coloca las casillas de vista previa SÓLO SI SON CASILLAS COMPLETAMENTE VACÍAS
                rellenarCasillas(&j->Tablero_flota, 176, B->Tam_barco , orient, x, y);
                colocarCasilla(178, &j->Tablero_flota, x, y);

                //MUESTRA LA FLOTA CON LA VISTA PREVIA YA COLOCADA
                mostrarFlota(j);

                //Recoge una tecla
                printf("\n\nPulse: ");
                scanf("%c", &charBuffer);

                //Casos especiales
                if(exit(charBuffer)){
                    printf("\n\n\nSaliendo del menú de colocación de barco...\n\n\n");
                    return 0;
                } //Si es N o n sale del menú.
                if(hasPressed(charBuffer, 'R')){flagRestart = true; flagPlaced = true; break;} //Si es R o r sale de todos excepto del while(!flagRestart)

                //Casos según tecla pulsada
                switch(charBuffer)
                {
                    //Si es enter, se coloca
                    case '\n':
                        flagPlaced = true;
                        colocarBarco(&j->Tablero_flota, B, x, y, orient);
                    break;

                    case 'A':
                        moverAOrientacion(G180, &x, &y);
                    break;

                    case 'W':
                        moverAOrientacion(G90, &x, &y);
                    break;

                    case 'S':
                        moverAOrientacion(G270, &x, &y);
                    break;
                    
                    case 'D':
                        moverAOrientacion(G0, &x, &y);
                    break;

                    case 'J':
                        rotar(&orient, G90, IZQUIERDA);
                    break;

                    case 'L':
                        rotar(&orient, G90, DERECHA);
                    break;

                    case 'I':
                        rotar(&orient, G45, IZQUIERDA);
                    break;

                    case 'K':
                        rotar(&orient, G45, DERECHA);
                    break;

                    default:
                        charBuffer = '0'; //Caracter invalido
                    break;
                }

                //Si se ha colocado no necesita verificarse, si es caracter inválido, nueva iteración del bucle
                if(!flagPlaced || charBuffer != '0'){
                //Verifica la nueva posición, si es correcta se va a ella y se ejecuta de nuevo el bucle hasta que se pulse ENTER
                    if(!verificarEspacio(&j->Tablero_flota, &B, orient, x, y)){
                        printf("\n\nPOSICIÓN NO VALIDA. Elija otra. [R] para reiniciar posicion. [N] para salir\n\n");
                        x = xIni; y = yIni; orient = orientIni;
                    }else{
                        vaciarCasillas(&j->Tablero_flota, B->Tam_barco, orientIni, xIni, yIni);
                    }
    
                }

            }while(!flagPlaced);

        }while(flagRestart);

    //Si ha llegado hasta aquí, se ha colocado el barco, devuelve 1.
    return 1;
}

void vaciarCasillas(Tablero* T, int nCasillas, int orient, int x, int y)
{
    rellenarCasillas(T, ' ', nCasillas, orient, x, y);
}

void rellenarCasillas(Tablero* T, char c, int nCasillas, int orient, int x, int y)
{
    while(nCasillas){
        T->casillas[x][y] = c;
        moverAOrientacion(orient, x, y);
        nCasillas--;
    }
}

inline int verificarCasilla(Tablero* T, int x, int y) 
{return (T->casillas[x][y] == ' ') && (x < 0 || x >= T->maxLado) && (y < 0 || y >= T->maxLado); }


int verificarEspacio(Tablero* T, Barco* B, int orientacion, int x, int y)
{
    int tamBarco = B->Tam_barco;
    int flagValid = true;

    while(tamBarco != 0 && flagValid){
        if(!verificarCasilla(T, x, y)) flagValid = false;
        moverAOrientacion(orientacion, &x, &y);
        tamBarco--;
    }
    return flagValid;
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

static void compactarVector(Vector_Barcos* vect, int barcoSeleccionado, int nBarcos)
{
    int barcosAMover = (nBarcos - 1) - barcoSeleccionado;
    //Se machaca el valor de i con el siguiente hasta el penúltimo elemento
    for(int i=barcoSeleccionado ; i < barcosAMover - 1 ; i++)
        vect[i] = vect[i+1];

    //Se reajusta el vector a un elemento menos, machacandose el último elemento
    vect = (Vector_Barcos*) realloc(vect, nBarcos-1);
}


int colocarAleatorio(Jugador* j, Vector_Barcos* vect)
{
    srand(time(NULL));
    int x, xIni, yIni, y, orient;
    int flagColocado = false;
    int nBarcos = vect->tam;
    int tamTableroMax = j->Tablero_flota.maxLado;
    int contStress = 0; //Contador Anti-bloqueo

    //Mientras haya barcos, los coloca
    while(nBarcos){
        flagColocado = false;
        //Mientras no se coloque elige una nueva coordenada y prueba
        do{
            xIni = x = 0 + rand() % tamTableroMax;
            yIni = y = 0 + rand() % tamTableroMax;
            orient = 0 + rand() % (G315 + 1); //Orientación entre 0 y 7
            contStress++; 

            //Se verifica, si cabe se coloca, sino, se sigue ejecutando hasta que se coloque -> flagColocado = true;
            if(verificarEspacio(&j->Tablero_flota, &vect->Barcos[nBarcos-1], orient, x, y)){
                x = xIni; y = yIni;
                colocarBarco(&j->Tablero_flota, &vect->Barcos[nBarcos-1], x, y, orient);
                nBarcos--;
                flagColocado = true;

            }elif(contStress > MAX_RANDOM_TRIES);{//Si se han hecho demasiados intentos para O REINICIA el programa.
                reiniciarTablero(&j->Tablero_flota);
                printf("\nError de colocación. Demasiados intentos. Reiniciando tablero...\n", stderr);
                return colocarAleatorio(j, vect);
            }
            
        }while(!flagColocado);
    }

    mostrarFlota(j);
    return 1; //Colocado correctamente
}

void moverAOrientacion(int orientacion, int* x, int* y)
{
    switch(orientacion){
        case G0:
            *x++;
        break;

        case G45:
            *x++; *y++;
        break;
        
        case G90:
            *y++;
        break;

        case G135:
            *x--; *y++;
        break;

        case G180:
            *x--;
        break;

        case G225:
            *x--; *y--;
        break;

        case G270:
            *y--;
        break;

        case G315:
            *x++; *y--;
        break;
    }

}

void rotar(int* orientBase, int grados, int direccion)
{
    if(direccion)
        orientBase += grados;
    else
        orientBase -= grados;

    //Da la vuelta a un valor válido.
    if(orientBase < 0 ) orientBase += 8;
    if(orientBase > 7) orientBase -= 8;

    return orientBase;
    
}

inline char devolverCasilla(Tablero* T, int x, int y) { T->casillas[x][y];}

inline void colocarCasilla(char c, Tablero* T, int x, int y){T->casillas[x][y] = c;}

