#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Datos.h"


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
    char *token;
    int i;

    // Abrir el archivo en modo lectura
    if ((archivo = fopen(ruta, "r")) == NULL) {
        printf("Error al abrir el archivo %s.\n", ruta);
        exit(1);
    }

	// Lectura de datos relacionados a los barcos que se van a usar
	if (fgets(linea, sizeof(linea), archivo) != NULL) {
        sscanf(linea, "%d-%d-%d", config.Tama_tablero, config.Tama_flota, config.Tama_tipos_barco);
        
        config.Tipo_barcos = (char *)malloc(config.Tama_tipos_barco  * sizeof(char));
        config.Num_barcos = (int *)malloc(config.Tama_tipos_barco * sizeof(int));
    }
    
    for (i = 0; i < config.Tama_tipos_barco; i++){
    	if (fgets(linea, sizeof(linea), archivo) != NULL) {
    		sscanf(linea, "%c-%d", config.Tipo_barcos[i], config.Num_barcos[i]);
		}
	}
	
	// Lectura de datos del jugador 1
    if (fgets(linea, sizeof(linea), archivo) != NULL) {
        sscanf(linea, "%d-%s-%d-%c-%d", config.Id_J1, config.Nomb_J1, config.Num_disparos_J1, config.Tipo_disparo_J1, config.Ganador_J1);
    }
	
	config.Tablero_flota1.casillas = (char**) malloc(sizeof(char*)*config.Tama_tablero);
	for (int i = 0; i < config.Tama_tablero; i++){
		config.Tablero_flota1.casillas[i] = (char*) malloc(sizeof(char)*config.Tama_tablero);
	}
	
	for (int i = 0; i < config.Tablero_flota1.maxLado; i++){
		for (int j = 0; j < config.Tama_tablero; j++){
			config.Tablero_flota1.casillas[i][j] = strtok("%c", " \n");
		}
	}
	
	config.Tablero_oponente1.casillas = (char**) malloc(sizeof(char*)*config.Tama_tablero);
	for (int i = 0; i < config.Tama_tablero; i++){
		config.Tablero_oponente1.casillas[i] = (char*) malloc(sizeof(char)*config.Tama_tablero);
	}
	
	for (int i = 0; i < config.Tama_tablero; i++){
		for (int j = 0; j < config.Tama_tablero; j++){
			config.Tablero_oponente1.casillas[i][j] = strtok("%c", " \n");
		}
	}
	
	//Lectura de datos del jugador 2
	if (fgets(linea, sizeof(linea), archivo) != NULL) {
        sscanf(linea, "%d-%s-%d-%c-%d", config.Id_J2, config.Nomb_J2, config.Num_disparos_J2, config.Tipo_disparo_J2, config.Ganador_J2);
    }
	
	config.Tablero_flota2.casillas = (char**) malloc(sizeof(char*)*config.Tama_tablero);
	for (int i = 0; i < config.Tama_tablero; i++){
		config.Tablero_flota2.casillas[i] = (char*) malloc(sizeof(char)*config.Tama_tablero);
	}
	
	for (int i = 0; i < config.Tablero_flota1.maxLado; i++){
		for (int j = 0; j < config.Tama_tablero; j++){
			config.Tablero_flota2.casillas[i][j] = strtok("%c", " \n");
		}
	}
	
	config.Tablero_oponente2.casillas = (char**) malloc(sizeof(char*)*config.Tama_tablero);
	for (int i = 0; i < config.Tama_tablero; i++){
		config.Tablero_oponente2.casillas[i] = (char*) malloc(sizeof(char)*config.Tama_tablero);
	}
	
	for (int i = 0; i < config.Tama_tablero; i++){
		for (int j = 0; j < config.Tama_tablero; j++){
			config.Tablero_oponente2.casillas[i][j] = strtok("%c", " \n");
		}
	}
	
    // Cerrar el archivo
    fclose(archivo);

    return config;
}


void guardar_config(ConfiguracionJuego config) {
    FILE *archivo;
	char ruta[] = "C:\\Users\\cauce\\Desktop\\MP-2025-Datos\\Modulo_Datos\\Juego.txt";
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
        printf("Nombre: %s: | Tamaño: %d\n", b.Barcos[i].Nomb_barco, b.Barcos[i].Tam_barco);
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
	
	printf("\n\nDatos de los tableros: \n\n");
	printf("Tamaño de los tableros: %dx%d\n", config.Tama_tablero, config.Tama_tablero);
	
	printf("Tablero de la flota del jugador 1: ");
	for (i = 0; i < config.Tama_tablero; i++){
		printf("\n")
		for (j = 0; j < config.Tama_tablero; j++){
			printf(" %d ", config.Tablero_flota1[i]);
		}
	}
	
	//Terminar resto de tableros y tipos de barcos
	
	
	
    // Mostrar tamaño del tablero
    printf("Tamaño del tablero: %d\n\n", config.Tama_tablero);

    // Mostrar tipos de barcos y cantidad
    printf("Tipos de barcos y cantidad:\n");
    for (int i = 0; i < config.Tama_flota; i++) {
        printf("  Tipo: %c, Cantidad: %d\n", config.Tipo_barcos[i], config.num_barcos[i]);
    }

    // Mostrar jugador inicial
    printf("\nJugador inicial: %s\n\n", config.Primer_Jugador);
}


void modificar_config(ConfiguracionJuego *config) {
    int opcion;
    char buffer[100];

    do {
        // Mostrar menú de opciones
        printf("\n--- Menú de modificación ---\n");
        printf("1. Cambiar nombre del Jugador 1\n");
        printf("2. Cambiar tipo de disparo del Jugador 1\n");
        printf("3. Cambiar nombre del Jugador 2\n");
        printf("4. Cambiar tipo de disparo del Jugador 2\n");
        printf("5. Cambiar tamaño del tablero\n");
        printf("6. Cambiar tipos de barcos\n");
        printf("7. Cambiar número de barcos\n");
        printf("8. Cambiar jugador inicial\n");
        printf("9. Salir\n");
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
                printf("Nuevo nombre para Jugador 2: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';  // Eliminar el salto de línea
                strcpy(config->Nomb_J2, buffer);
                break;

            case 4:
                printf("Nuevo tipo de disparo para Jugador 2 (M/A): ");
                scanf("%c", &config->Tipo_disparo_J2);
                getchar();  // Limpiar el buffer de entrada
                break;

            case 5:
                printf("Nuevo tamaño del tablero: ");
                scanf("%d", &config->Tama_tablero);
                getchar();  // Limpiar el buffer de entrada
                break;

            case 6: {
			    Vector_Barcos vb = cargar_barcos();
			    mostrar_barcos(vb);
			
			    printf("Nuevos tipos de barcos (separados por comas, sin espacios): ");
			    fgets(buffer, sizeof(buffer), stdin);
			    buffer[strcspn(buffer, "\n")] = '\0';  // Eliminar el salto de línea
			
			    // Liberar memoria anterior si es necesario
			    if (config->Tipo_barcos != NULL) {
			        free(config->Tipo_barcos);
			    }
			
			    // Contar el número de tipos de barcos
			    config->Tama_flota = 0;
			    char *token = strtok(buffer, ",");
			    while (token != NULL) {
			        config->Tama_flota++;
			        token = strtok(NULL, ",");
			    }
			
			    // Reservar memoria para los nuevos tipos de barcos
			    config->Tipo_barcos = (char *)malloc(config->Tama_flota * sizeof(char));
			    if (config->Tipo_barcos == NULL) {
			        printf("Error al reservar memoria para tipos de barcos.\n");
			        exit(1);
			    }
			
			    // Extraer los nuevos tipos de barcos
			    token = strtok(buffer, ",");
			    for (int i = 0; i < config->Tama_flota; i++) {
			        config->Tipo_barcos[i] = token[0];  // Tomar el primer carácter
			        token = strtok(NULL, ",");
			    }
			    free(vb.Barcos);
			    break;
			}


            case 7:
                printf("Nuevo número de barcos (separados por comas, sin espacios): ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';  // Eliminar el salto de línea

                // Liberar memoria anterior si es necesario
                if (config->num_barcos != NULL) {
                    free(config->num_barcos);
                }

                // Reservar memoria para los nuevos números de barcos
                config->num_barcos = (int *)malloc(config->Tama_flota * sizeof(int));
                if (config->num_barcos == NULL) {
                    printf("Error al reservar memoria para números de barcos.\n");
                    exit(1);
                }

                // Extraer los nuevos números de barcos
                char *token_num = strtok(buffer, ",");
                for (int i = 0; i < config->Tama_flota; i++) {
                    config->num_barcos[i] = atoi(token_num);
                    token_num = strtok(NULL, ",");
                }
                break;

            case 8:
                printf("Nuevo jugador inicial: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';  // Eliminar el salto de línea
                strcpy(config->Primer_Jugador, buffer);
                break;

            case 9:
                printf("Saliendo del menú de modificación...\n");
                break;

            default:
                printf("Opción no válida. Intente de nuevo.\n");
                break;
        }

        // Mostrar la configuración actualizada
        if (opcion != 9) {
            printf("\nConfiguración actualizada:\n");
            mostrar_configuracion(*config);
        }

    } while (opcion != 9);
}


void borrar_config(ConfiguracionJuego *config){
	strcpy(config->Nomb_J1, " ");
	config->Tipo_disparo_J1 = 'A';
	strcpy(config->Nomb_J2, " ");
	config->Tipo_disparo_J2 = 'A';
	config->Tama_tablero = 0;
	free(config->Tipo_barcos);
	free(config->num_barcos);
	config->Tama_flota = 0;
	strcpy(config->Primer_Jugador, " ");
	for (int i = 0; i < config->Tablero_flota1.maxLado; i++) free(config->Tablero_flota1.casillas[i]);
	free(config->Tablero_flota1.casillas);
	config->Tablero_flota1.maxLado = 0;
	for (int i = 0; i < config->Tablero_oponente1.maxLado; i++) free(config->Tablero_oponente1.casillas[i]);
	free(config->Tablero_oponente1.casillas);
	config->Tablero_oponente1.maxLado  = 0;
	for (int i = 0; i < config->Tablero_flota2.maxLado; i++) free(config->Tablero_flota2.casillas[i]);
	free(config->Tablero_flota2.casillas);
	config->Tablero_flota2.maxLado = 0;
	for (int i = 0; i < config->Tablero_oponente2.maxLado; i++) free(config->Tablero_oponente2.casillas[i]);
	free(config->Tablero_oponente2.casillas);
	config->Tablero_oponente2.maxLado  = 0;
}

