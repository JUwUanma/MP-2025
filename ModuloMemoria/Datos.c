#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Datos.h"
#include "Interfaz.h"
#include "logica.h"
#include "Tablero.h"

//Implementación de las funciones:

Vector_Barcos cargar_barcos() {
    Vector_Barcos vect_barcos;
    FILE *Barcos;
    char ruta[] = "Barcos.txt";  // Ruta del fichero a leer
    char linea[LONG_MAX_BARCO];  // Línea actual del fichero
    int i = 0, m;

    // Abrir el archivo en modo lectura
    if ((Barcos = fopen(ruta, "r")) == NULL) {
        printf("\nError al abrir el fichero Barcos.txt. Creando uno nuevo...\n");
        // Crear un archivo por defecto si no existe
        Barcos = fopen(ruta, "w");
        if (Barcos == NULL) {
            printf("\nError al crear el fichero Barcos.txt.\n");
            exit(1);
        }
        fprintf(Barcos, "defaultbarco-F-0\n");  // Escribir un barco por defecto
        fclose(Barcos);
        Barcos = fopen(ruta, "r");  // Volver a abrir en modo lectura
    }

    // Contar el número de barcos en el archivo
    vect_barcos.tam = 0;
    while (fgets(linea, sizeof(linea), Barcos) != NULL) {
        vect_barcos.tam++;
    }
    rewind(Barcos);

    // Reservar memoria para el vector de barcos
    vect_barcos.Barcos = (Barco *)malloc(vect_barcos.tam * sizeof(Barco));
    if (vect_barcos.Barcos == NULL) {
        printf("\nError al reservar memoria.\n");
        fclose(Barcos);
        exit(1);
    }

    // Leer los datos del archivo
    while (fgets(linea, sizeof(linea), Barcos) != NULL) {
        if ((m = sscanf(linea, "%19[^-]-%c-%d", vect_barcos.Barcos[i].Nomb_barco, &vect_barcos.Barcos[i].Id_barco, &vect_barcos.Barcos[i].Tam_barco)) == 3) {
            i++;
        } else {
            printf("\nError leyendo datos del fichero Barcos.txt. Línea: %d\n", i);
            fclose(Barcos);
            free(vect_barcos.Barcos);  // Liberar memoria antes de salir
            exit(1);
        }
    }

    fclose(Barcos);
    return vect_barcos;
}


ConfiguracionJuego cargar_config() {
    ConfiguracionJuego config;
    FILE *archivo;
    char ruta[] = "Juego.txt";
    char linea[100];
    int i, j;

    // Abrir el archivo en modo lectura
    archivo = fopen(ruta, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s.\n", ruta);
        exit(1);
    }

    // Lectura de datos relacionados a los barcos que se van a usar
    if (fgets(linea, sizeof(linea), archivo) != NULL) {
        sscanf(linea, "%d-%d-%d", &config.Tama_tablero, &config.Tama_flota, &config.Tama_tipos_barco);
        
        // Asignación dinámica para los tipos de barco y número de barcos
        config.Tipo_barcos = (char *)malloc(config.Tama_tipos_barco * sizeof(char));
        config.Num_barcos = (int *)malloc(config.Tama_tipos_barco * sizeof(int));
    }

    // Lectura de los tipos de barcos y número de barcos
    for (i = 0; i < config.Tama_tipos_barco; i++) {
        if (fgets(linea, sizeof(linea), archivo) != NULL) {
            sscanf(linea, "%c-%d", &config.Tipo_barcos[i], &config.Num_barcos[i]);
        }
    }

    // Lectura de datos del jugador 1
    if (fgets(linea, sizeof(linea), archivo) != NULL) {
        sscanf(linea, "%d-%s-%d-%c-%d", &config.Id_J1, config.Nomb_J1, &config.Num_disparos_J1, &config.Tipo_disparo_J1, &config.Ganador_J1);
    }

    // Asignación dinámica para los tableros
    config.Tablero_flota1.casillas = (char **)malloc(sizeof(char*) * config.Tama_tablero);
    config.Tablero_oponente1.casillas = (char **)malloc(sizeof(char*) * config.Tama_tablero);
    for (i = 0; i < config.Tama_tablero; i++) {
        config.Tablero_flota1.casillas[i] = (char *)malloc(sizeof(char) * config.Tama_tablero);
        config.Tablero_oponente1.casillas[i] = (char *)malloc(sizeof(char) * config.Tama_tablero);
    }

    // Llenado de los tableros con caracteres, asumiendo que los caracteres se leen de alguna parte
    for (i = 0; i < config.Tama_tablero; i++) {
        for (j = 0; j < config.Tama_tablero; j++) {
            // Aquí, supongamos que en cada línea se coloca un carácter para llenar el tablero
            if (fgets(linea, sizeof(linea), archivo) != NULL) {
                sscanf(linea, "%c", &config.Tablero_flota1.casillas[i][j]);
                sscanf(linea, "%c", &config.Tablero_oponente1.casillas[i][j]);
            }
        }
    }

    // Lectura de datos del jugador 2
    if (fgets(linea, sizeof(linea), archivo) != NULL) {
        sscanf(linea, "%d-%s-%d-%c-%d", &config.Id_J2, config.Nomb_J2, &config.Num_disparos_J2, &config.Tipo_disparo_J2, &config.Ganador_J2);
    }

    // Asignación dinámica para los tableros del jugador 2
    config.Tablero_flota2.casillas = (char **)malloc(sizeof(char*) * config.Tama_tablero);
    config.Tablero_oponente2.casillas = (char **)malloc(sizeof(char*) * config.Tama_tablero);
    for (i = 0; i < config.Tama_tablero; i++) {
        config.Tablero_flota2.casillas[i] = (char *)malloc(sizeof(char) * config.Tama_tablero);
        config.Tablero_oponente2.casillas[i] = (char *)malloc(sizeof(char) * config.Tama_tablero);
    }

    // Llenado de los tableros del jugador 2
    for (i = 0; i < config.Tama_tablero; i++) {
        for (j = 0; j < config.Tama_tablero; j++) {
            if (fgets(linea, sizeof(linea), archivo) != NULL) {
                sscanf(linea, "%c", &config.Tablero_flota2.casillas[i][j]);
                sscanf(linea, "%c", &config.Tablero_oponente2.casillas[i][j]);
            }
        }
    }

    // Cerrar el archivo
    fclose(archivo);

    return config;
}



void guardar_config(ConfiguracionJuego config) {
    FILE *archivo;
	char ruta[] = "Juego.txt";
	int i = 0;
	
    // Abrir el archivo en modo escritura (sobrescribe el contenido)
    if ((archivo = fopen(ruta, "w")) == NULL) {
        printf("Error al abrir el archivo %s para escritura.\n", ruta);
        exit(1);
    }


	// Guardamos datos relacionados con los barcos que se van a usar
	fprintf(archivo, "%d-%d-%d\n", config.Tama_tablero, config.Tama_flota, config.Tama_tipos_barco);
	
	for (i = 0; i < config.Tama_tipos_barco; i++){
		fprintf(archivo, "%c-%d\n", config.Tipo_barcos[i], config.Num_barcos[i]);
	}

	//Guardamos informacion relacionada con el jugador 1
	fprintf(archivo, "%d-%s-%d-%c-%d\n", config.Id_J1, config.Nomb_J1, config.Num_disparos_J1, config.Tipo_disparo_J1, config.Ganador_J1);
	
	for (int i = 0; i < config.Tama_tablero; i++){
    	fprintf(archivo, "\n");
    	for (int j = 0; j < config.Tama_tablero; j++){
    		fprintf(archivo, "%c ", config.Tablero_flota1.casillas[i][j]);
		}
	}
	
	for (int i = 0; i < config.Tama_tablero; i++){
    	fprintf(archivo, "\n");
    	for (int j = 0; j < config.Tama_tablero; j++){
    		fprintf(archivo, "%c ", config.Tablero_oponente1.casillas[i][j]);
		}
	}
	
	//Guardamos informacion relacionada con el jugador 2
	fprintf(archivo, "%d-%s-%d-%c-%d\n", config.Id_J2, config.Nomb_J2, config.Num_disparos_J2, config.Tipo_disparo_J2, config.Ganador_J2);
	
	for (int i = 0; i < config.Tama_tablero; i++){
    	fprintf(archivo, "\n");
    	for (int j = 0; j < config.Tama_tablero; j++){
    		fprintf(archivo, "%c ", config.Tablero_flota2.casillas[i][j]);
		}
	}
	
	for (int i = 0; i < config.Tama_tablero; i++){
    	fprintf(archivo, "\n");
    	for (int j = 0; j < config.Tama_tablero; j++){
    		fprintf(archivo, "%c ", config.Tablero_oponente2.casillas[i][j]);
		}
	}
	
	
    // Cerrar el archivo
    fclose(archivo);

    printf("Configuración guardada correctamente en %s.\n", ruta);
}


void mostrar_barcos(Vector_Barcos b){
	int i = 0;
		
    // Imprimir los nombres de los barcos
    for (i; i < b.tam; i++) {
        printf("Nombre: %s: - Tamaño: %d - (%c)\n", b.Barcos[i].Nomb_barco, b.Barcos[i].Tam_barco, b.Barcos[i].Nomb_barco[0]);
    }

    // Liberar la memoria asignada
    free(b.Barcos);
}


void mostrar_configuracion(ConfiguracionJuego config) {
	int i, j;
    // Mostrar información de los jugadores
    printf("Datos de los jugadores: \n\n");

    printf("Jugador 1:\n");
    printf("  - Identificador: %d\n", config.Id_J1);
    printf("  - Nombre: %s\n", config.Nomb_J1);
    printf("  - Tipo de disparo: %c\n", config.Tipo_disparo_J1);
    printf("  - Numero de disparos: %c\n", config.Num_disparos_J1);
    if (config.Ganador_J1 == 0){
    	printf("  - Ganador: NO\n");
	}else{
		printf("  - Ganador: SI\n");
	}
	
    printf("Jugador 2:\n");
    printf("  - Identificador: %d\n", config.Id_J2);
    printf("  - Nombre: %s\n", config.Nomb_J2);
    printf("  - Tipo de disparo: %c\n\n", config.Tipo_disparo_J2);
    printf("  - Numero de disparos: %c\n", config.Num_disparos_J2);
    if (config.Ganador_J2 == 0){
    	printf("  - Ganador: NO\n");
	}else{
		printf("  - Ganador: SI\n");
	}

	// Mostrar datos de los barcos
	printf("\n\nDatos de los barcos:\n\n");
	printf("Numero de barcos totales en la flota: %d\n", config.Tama_flota);
	printf("Numero de barcos diferentes: %d\n", config.Tama_tipos_barco);
	printf("Barcos que se van a usar: \n");
	for(i = 0; i < config.Tama_flota-1; i++){
		printf("%d. %c - %d\n", i, config.Tipo_barcos[i], config.Num_barcos[i]);
	}
	
	printf("\n");
	
	printf("\n\nDatos de los tableros: \n\n");
	printf("Tamaño de los tableros: %dx%d\n", config.Tama_tablero, config.Tama_tablero);
	
	printf("Tablero de la flota del jugador 1: ");
	for (i = 0; i < config.Tama_tablero; i++){
		printf("\n");
		for (j = 0; j < config.Tama_tablero; j++){
			printf(" %c ", config.Tablero_flota1.casillas[i][j]);
		}
	}
	printf("\n");
	
	printf("Tablero oponente del jugador 1: ");
	for (i = 0; i < config.Tama_tablero; i++){
		printf("\n");
		for (j = 0; j < config.Tama_tablero; j++){
			printf(" %c ", config.Tablero_oponente1.casillas[i][j]);
		}
	}
	printf("\n");
	
	printf("Tablero de la flota del jugador 2: ");
	for (i = 0; i < config.Tama_tablero; i++){
		printf("\n");
		for (j = 0; j < config.Tama_tablero; j++){
			printf(" %c ", config.Tablero_flota2.casillas[i][j]);
		}
	}
	printf("\n");
	
	printf("Tablero oponente del jugador 2: ");
	for (i = 0; i < config.Tama_tablero; i++){
		printf("\n");
		for (j = 0; j < config.Tama_tablero; j++){
			printf(" %c ", config.Tablero_oponente2.casillas[i][j]);
		}
	}
}


void modificar_config(ConfiguracionJuego *config) {
    int opcion;
    char buffer[100];

    do {
        // Mostrar menú de opciones
        printf("\n--- Menú de modificación ---\n");
        printf("1. Cambiar nombre del Jugador 1\n");
        printf("2. Cambiar tipo de disparo del Jugador 1\n");
        printf("3. Cambiar numero de disparos del Jugador 1\n");
        printf("4. Declarar a Jugador 1 como ganador\n");
        printf("5. Cambiar nombre del Jugador 2\n");
        printf("6. Cambiar tipo de disparo del Jugador 2\n");
        printf("7. Cambiar numero de disparo del Jugador 1\n");
        printf("8. Declarar a Jugador 1 como ganador\n");
        printf("9. Cambiar barcos\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar();  // Limpiar el buffer de entrada

        switch (opcion) {
            case 1:
                printf("Nuevo nombre para Jugador 1: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';  // Eliminar el salto de línea
                strcpy(config->Nomb_J1, buffer);
                break;

            case 2:
                printf("Nuevo tipo de disparo para Jugador 1 (M/A): ");
                scanf("%c", &config->Tipo_disparo_J1);
                getchar();  // Limpiar el buffer de entrada
                break;
            
            case 3:
            	printf("Número de disparos de Jugador 1: ");
            	scanf("%d", &config->Num_disparos_J1);
            	break;
            	
            case 4:
            	printf("Jugador 1 declarado ganador.");
            	config->Ganador_J1 = 1;
            	break;

            case 5:
                printf("Nuevo nombre para Jugador 2: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';  // Eliminar el salto de línea
                strcpy(config->Nomb_J2, buffer);
                break;

            case 6:
                printf("Nuevo tipo de disparo para Jugador 2 (M/A): ");
                scanf("%c", &config->Tipo_disparo_J2);
                getchar();  // Limpiar el buffer de entrada
                break;
                
            case 7:
            	printf("Número de disparos de Jugador 2: ");
            	scanf("%d", &config->Num_disparos_J2);
            	break;
            
            case 8:
            	printf("Jugador 2 declarado ganador.");
            	config->Ganador_J2 = 1;
            	break;
            
            case 9:
            	modificar_barcos(config);


        // Mostrar la configuración actualizada
        if (opcion != 0) {
            printf("\nConfiguración actualizada:\n");
            mostrar_configuracion(*config);
        }

    }
	}while (opcion != 0);
}


void modificar_barcos(ConfiguracionJuego *config){
    Vector_Barcos vb = cargar_barcos();
    int i = 0, j = 0, contador = 0, encontrado = 0, numero_barcos;
    char placeholder;

    printf(" ---Modificar Barcos--- \n");
    printf("¿Cuántos barcos quiere usar?\n");

    scanf("%d", &config->Tama_flota);

    config->Tipo_barcos = (char *) realloc(config->Tipo_barcos, config->Tama_flota * sizeof(char));
    config->Num_barcos = (int *) realloc(config->Num_barcos, config->Tama_flota * sizeof(int));

    i = 0;
    while (i < config->Tama_flota) {
        mostrar_barcos(vb);
        printf("Indique el barco que quiere utilizar (letra):\n");
        scanf(" %c", &placeholder);  // espacio antes del %c para ignorar el '\n'

        encontrado = 0;

        for (j = 0; j < vb.tam; j++) {
            if (placeholder == vb.Barcos[j].Nomb_barco[0]) {
                encontrado = 1;
                config->Tipo_barcos[i] = placeholder;

                printf("¿Cuántos barcos con identificador %c desea?:\n", placeholder);
                scanf("%d", &numero_barcos);

                if (contador + numero_barcos <= config->Tama_flota) {
                    config->Num_barcos[i] = numero_barcos;
                    contador += numero_barcos;
                    i++;
                } else {
                    printf("Supera el límite de barcos permitidos. Intente de nuevo.\n");
                }
                break;
            }
        }

        if (!encontrado) {
            printf("Barco no válido. Intente de nuevo.\n");
        }
    }
}

void liberar_tablero(Tablero *T) {
    if (T->casillas != NULL) {
        for (int i = 0; i < T->maxLado; i++) {
            if (T->casillas[i] != NULL) {
                free(T->casillas[i]);
                T->casillas[i] = NULL;
            }
        }
        free(T->casillas);
        T->casillas = NULL;
    }
    T->maxLado = 0;
}


void borrar_config(ConfiguracionJuego *config){
    config->Id_J1 = 0;
    strcpy(config->Nomb_J1, "");
    config->Tipo_disparo_J1 = 'A';
    config->Num_disparos_J1 = 0;
    config->Ganador_J1 = 0;

    config->Id_J2 = 0;
    strcpy(config->Nomb_J2, "");
    config->Tipo_disparo_J2 = 'A';
    config->Num_disparos_J2 = 0;
    config->Ganador_J2 = 0;

    config->Tama_tablero = 0;
    config->Tama_flota = 0;
    config->Tama_tipos_barco = 0;

    if (config->Tipo_barcos != NULL) {
        free(config->Tipo_barcos);
        config->Tipo_barcos = NULL;
    }
    if (config->Num_barcos != NULL) {
        free(config->Num_barcos);
        config->Num_barcos = NULL;
    }

    liberar_tablero(&config->Tablero_flota1);
    liberar_tablero(&config->Tablero_oponente1);
    liberar_tablero(&config->Tablero_flota2);
    liberar_tablero(&config->Tablero_oponente2);
}
