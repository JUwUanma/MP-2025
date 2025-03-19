#include <stdio.h>
#include <stdlib.h>
#include "Interfaz.h"
#include "Datos.h"

void MenuPrincipal() {
    int opcion;

    // Mensaje de bienvenida (se muestra solo al iniciar el juego)
    printf("\n========================================\n");
    printf("       ¡BIENVENIDO A HUNDIR LA FLOTA!\n");
    printf("========================================\n");

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Configuracion\n");
        printf("2. Jugar\n");
        printf("3. Salir\n\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                MenuConfiguracion();
                break;
            case 2:
                MenuJuego();
                break;
            case 3:
                printf("Saliendo del juego...\n");
                break;
            default:
                printf("Opción no valida. Intente de nuevo.\n");
        }
    } while (opcion != 3);
}

void MenuConfiguracion() {
    int opcion;
    ConfiguracionJuego config;

    do {
        printf("\n=== CONFIGURACION ===\n");
        printf("1. Introducir datos\n");
        printf("2. Mostrar\n");
        printf("3. Borrar\n");
        printf("4. Guardar\n");
        printf("5. Cargar\n");
        printf("6. Volver\n\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Funcion introducir datos.\n");
                modificar_config(&config);
                break;
            case 2:
                printf("Mostrando configuracion:\n");
                mostrar_configuracion(config);
                break;
            case 3:
                printf("Borrando configuracion...\n");
                free(config.Tipo_barcos);
                free(config.num_barcos);
                break;
            case 4:
                printf("Guardando configuracion...\n");
                guardar_config(config);
                break;
            case 5:
                printf("Cargando configuracion...\n");
                config = cargar_config();
                break;
            case 6:
                printf("Regresando al menu principal...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 6);
}

void MenuJuego() {
    int opcion;
    do {
        printf("\n=== JUGAR PARTIDA ===\n");
        printf("1. Jugar partida\n");
        printf("2. Reiniciar partida\n");
        printf("3. Resumen\n");
        printf("4. Volver\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Funcion Jugar partida.\n");
                break;
            case 2:
                printf("Funcion Reiniciar partida.\n");
                break;
            case 3:
                printf("Funcion Mostrar resumen.\n");
                break;
            case 4:
                printf("Regresando al menu principal...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 4);
}
