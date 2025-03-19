#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Datos.h"


//Implementaci�n de las funciones:

Vector_Barcos cargar_barcos() {
    Vector_Barcos vect_barcos;
    FILE *Barcos;
    char ruta[] = "Barcos.txt";  // Ruta del fichero a leer
    char linea[LONG_MAX_BARCO];  // L�nea actual del fichero
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

    // Contar el n�mero de barcos en el archivo
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
            printf("\nError leyendo datos del fichero Barcos.txt. L�nea: %d\n", i);
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

    // Leer la informaci�n de los jugadores
    if (fgets(linea, sizeof(linea), archivo) != NULL) {
        sscanf(linea, "Jugador1-%19[^-]-%c", config.Nomb_J1, &config.Tipo_disparo_J1);
    }
    if (fgets(linea, sizeof(linea), archivo) != NULL) {
        sscanf(linea, "Jugador2-%19[^-]-%c", config.Nomb_J2, &config.Tipo_disparo_J2);
    }

    // Leer el tama�o del tablero
    if (fgets(linea, sizeof(linea), archivo) != NULL) {
        sscanf(linea, "%d", &config.Tama_tablero);
    }

    // Leer los tipos de barcos
    if (fgets(linea, sizeof(linea), archivo) != NULL) {
        // Contar el n�mero de tipos de barcos
        config.Tama_flota = 0;
        token = strtok(linea, ",");
        while (token != NULL) {
            config.Tama_flota++;
            token = strtok(NULL, ",");
        }

        // Reservar memoria para los tipos de barcos
        config.Tipo_barcos = (char *)malloc(config.Tama_flota * sizeof(char));
        if (config.Tipo_barcos == NULL) {
            printf("Error al reservar memoria para Tipo_barcos.\n");
            fclose(archivo);
            exit(1);
        }

        // Volver a leer la l�nea para extraer los tipos de barcos
        rewind(archivo);
        fgets(linea, sizeof(linea), archivo);  // Jugador 1
        fgets(linea, sizeof(linea), archivo);  // Jugador 2
        fgets(linea, sizeof(linea), archivo);  // Tama�o del tablero
        fgets(linea, sizeof(linea), archivo);  // Tipos de barcos

        // Extraer los tipos de barcos
        i = 0;
        token = strtok(linea, ",");
        while (token != NULL) {
            config.Tipo_barcos[i] = token[0];  // Tomar el primer car�cter del tipo de barco
            i++;
            token = strtok(NULL, ",");
        }
    }

    // Leer el n�mero de barcos de cada tipo
    if (fgets(linea, sizeof(linea), archivo) != NULL) {
        // Reservar memoria para num_barcos
        config.num_barcos = (int *)malloc(config.Tama_flota * sizeof(int));
        if (config.num_barcos == NULL) {
            printf("Error al reservar memoria para num_barcos.\n");
            free(config.Tipo_barcos);  // Liberar memoria previamente reservada
            fclose(archivo);
            exit(1);
        }

        // Extraer el n�mero de barcos de cada tipo
        i = 0;
        token = strtok(linea, ",");
        while (token != NULL) {
            config.num_barcos[i] = atoi(token);
            i++;
            token = strtok(NULL, ",");
        }
    }

    // Leer el jugador inicial
    if (fgets(linea, sizeof(linea), archivo) != NULL) {
        sscanf(linea, "%19s", config.Primer_Jugador);
    }

    // Cerrar el archivo
    fclose(archivo);

    return config;
}

/*
void guardar_barcos(Vector_Barcos b){
	FILE *Barcos;																							// Puntero al fichero a leer.
	char ruta[] = "Barco.txt";																		// Ruta del fichero a leer.
	char linea[LONG_MAX_BARCO];																				// L�nea actual del fichero. Longitud m�xima de una l�nea 86 caracteres.
	char aux[23];

	Barcos = fopen(ruta, "w");

	for(int i = 0; i < b.tam; i++)
		fprintf(Barcos, "%s-%c-%d\n", b.Barcos[i].Nomb_barco, b.Barcos[i].Id_barco, b.Barcos[i].Tam_barco);
	fclose(Barcos);
}
*/

void guardar_config(ConfiguracionJuego config) {
    FILE *archivo;
	char ruta[] = "Juego.txt";

    // Abrir el archivo en modo escritura (sobrescribe el contenido)
    if ((archivo = fopen(ruta, "w")) == NULL) {
        printf("Error al abrir el archivo %s para escritura.\n", ruta);
        exit(1);
    }

    // Escribir la informaci�n de los jugadores
    fprintf(archivo, "Jugador1-%s-%c\n", config.Nomb_J1, config.Tipo_disparo_J1);
    fprintf(archivo, "Jugador2-%s-%c\n", config.Nomb_J2, config.Tipo_disparo_J2);

    // Escribir el tama�o del tablero
    fprintf(archivo, "%d\n", config.Tama_tablero);

    // Escribir los tipos de barcos
    for (int i = 0; i < config.Tama_flota; i++) {
        fprintf(archivo, "%c", config.Tipo_barcos[i]);
        if (i < config.Tama_flota - 1) {
            fprintf(archivo, ",");  // Separar los tipos de barcos con comas
        }
    }
    fprintf(archivo, "\n");

    // Escribir el n�mero de barcos de cada tipo
    for (int i = 0; i < config.Tama_flota; i++) {
        fprintf(archivo, "%d", config.num_barcos[i]);
        if (i < config.Tama_flota - 1) {
            fprintf(archivo, ",");  // Separar los n�meros de barcos con comas
        }
    }
    fprintf(archivo, "\n");

    // Escribir el jugador inicial
    fprintf(archivo, "%s\n", config.Primer_Jugador);

    // Cerrar el archivo
    fclose(archivo);

    printf("Configuraci�n guardada correctamente en %s.\n", ruta);
}


void mostrar_barcos(Vector_Barcos b){
	int i = 0;

    // Imprimir los nombres de los barcos
    for (i; i < b.tam; i++) {
        printf("Nombre: %s: | Tama�o: %d\n", b.Barcos[i].Nomb_barco, b.Barcos[i].Tam_barco);
    }

    // Liberar la memoria asignada
    free(b.Barcos);
}


void mostrar_configuracion(ConfiguracionJuego config) {
    // Mostrar informaci�n de los jugadores
    printf("Jugador 1:\n");
    printf("  - Nombre: %s\n", config.Nomb_J1);
    printf("  - Tipo de disparo: %c\n", config.Tipo_disparo_J1);
    printf("Jugador 2:\n");
    printf("  - Nombre: %s\n", config.Nomb_J2);
    printf("  - Tipo de disparo: %c\n\n", config.Tipo_disparo_J2);

    // Mostrar tama�o del tablero
    printf("Tama�o del tablero: %d\n\n", config.Tama_tablero);

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
        // Mostrar men� de opciones
        printf("\n--- Men� de modificaci�n ---\n");
        printf("1. Cambiar nombre del Jugador 1\n");
        printf("2. Cambiar tipo de disparo del Jugador 1\n");
        printf("3. Cambiar nombre del Jugador 2\n");
        printf("4. Cambiar tipo de disparo del Jugador 2\n");
        printf("5. Cambiar tama�o del tablero\n");
        printf("6. Cambiar tipos de barcos\n");
        printf("7. Cambiar n�mero de barcos\n");
        printf("8. Cambiar jugador inicial\n");
        printf("9. Salir\n");
        printf("Seleccione una opci�n: ");
        scanf("%d", &opcion);
        getchar();  // Limpiar el buffer de entrada

        switch (opcion) {
            case 1:
                printf("Nuevo nombre para Jugador 1: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';  // Eliminar el salto de l�nea
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
                buffer[strcspn(buffer, "\n")] = '\0';  // Eliminar el salto de l�nea
                strcpy(config->Nomb_J2, buffer);
                break;

            case 4:
                printf("Nuevo tipo de disparo para Jugador 2 (M/A): ");
                scanf("%c", &config->Tipo_disparo_J2);
                getchar();  // Limpiar el buffer de entrada
                break;

            case 5:
                printf("Nuevo tama�o del tablero: ");
                scanf("%d", &config->Tama_tablero);
                getchar();  // Limpiar el buffer de entrada
                break;

            case 6: {
			    Vector_Barcos vb = cargar_barcos();
			    mostrar_barcos(vb);

			    printf("Nuevos tipos de barcos (separados por comas, sin espacios): ");
			    fgets(buffer, sizeof(buffer), stdin);
			    buffer[strcspn(buffer, "\n")] = '\0';  // Eliminar el salto de l�nea

			    // Liberar memoria anterior si es necesario
			    if (config->Tipo_barcos != NULL) {
			        free(config->Tipo_barcos);
			    }

			    // Contar el n�mero de tipos de barcos
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
			        config->Tipo_barcos[i] = token[0];  // Tomar el primer car�cter
			        token = strtok(NULL, ",");
			    }
			    free(vb.Barcos);
			    break;
			}


            case 7:
                printf("Nuevo n�mero de barcos (separados por comas, sin espacios): ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';  // Eliminar el salto de l�nea

                // Liberar memoria anterior si es necesario
                if (config->num_barcos != NULL) {
                    free(config->num_barcos);
                }

                // Reservar memoria para los nuevos n�meros de barcos
                config->num_barcos = (int *)malloc(config->Tama_flota * sizeof(int));
                if (config->num_barcos == NULL) {
                    printf("Error al reservar memoria para n�meros de barcos.\n");
                    exit(1);
                }

                // Extraer los nuevos n�meros de barcos
                char *token_num = strtok(buffer, ",");
                for (int i = 0; i < config->Tama_flota; i++) {
                    config->num_barcos[i] = atoi(token_num);
                    token_num = strtok(NULL, ",");
                }
                break;

            case 8:
                printf("Nuevo jugador inicial: ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';  // Eliminar el salto de l�nea
                strcpy(config->Primer_Jugador, buffer);
                break;

            case 9:
                printf("Saliendo del men� de modificaci�n...\n");
                break;

            default:
                printf("Opci�n no v�lida. Intente de nuevo.\n");
                break;
        }

        // Mostrar la configuraci�n actualizada
        if (opcion != 9) {
            printf("\nConfiguraci�n actualizada:\n");
            mostrar_configuracion(*config);
        }

    } while (opcion != 9);
}
