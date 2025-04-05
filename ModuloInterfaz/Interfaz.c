#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Interfaz.h"

void limpiarPantalla() {
    system("cls");
}
//permite navegar por el men� al usuario utilizando las flechas del teclado
int navegarMenu(const char *opciones[], int numOpciones) {
    int seleccion = 0;
    int tecla;

    while (1) {
        limpiarPantalla();
        printf("\n=== MENU ===\n");

        for (int i = 0; i < numOpciones; i++) {
            if (i == seleccion) {
                printf("> %s <\n", opciones[i]);
            } else {
                printf("  %s\n", opciones[i]);
            }
        }

        tecla = getch();
        if (tecla == 224) {
            tecla = getch();
            if (tecla == 72 && seleccion > 0) { // Flecha arriba
                seleccion--;
            } else if (tecla == 80 && seleccion < numOpciones - 1) { // Flecha abajo
                seleccion++;
            }
        } else if (tecla == 13) { // ENTER
            return seleccion;
        }
    }
}

void MenuPrincipal() {
        // Mensaje de bienvenida (se muestra solo al iniciar el juego)

    printf("+==============================================================+\n");
    printf("|   ____ ___ _____ _   ___     _______ _   _ ___ ____   ___    |\n");
    printf("|  | __ )_ _| ____| \ | \ \   / / ____| \ | |_ _|  _ \ / _ \   |\n");
    printf("|  |  _ \| ||  _| |  \| |\ \ / /|  _| |  \| || || | | | | | |  |\n");
    printf("|  | |_) | || |___| |\  | \ V / | |___| |\  || || |_| | |_| |  |\n");
    printf("|  |____/___|_____|_| \_|  \_/  |_____|_| \_|___|____/ \___/   |\n");
    printf("|                           / \                                |\n");
    printf("|                          / _ \                               |\n");
    printf("|                         / ___ \                              |\n");
    printf("|       _   _ _   _ _   _/_/__ \_\ ____    _        _          |\n");
    printf("|      | | | | | | | \ | |  _ \_ _|  _ \  | |      / \         |\n");
    printf("|      | |_| | | | |  \| | | | | || |_) | | |     / _ \        |\n");
    printf("|      |  _  | |_| | |\  | |_| | ||  _ <  | |___ / ___ \       |\n");
    printf("|      |_| |_|\___/|_|_\_|____/___|_| \_\ |_____/_/   \_\      |\n");
    printf("|              |  ___| |   / _ \_   _|/ \                      |\n");
    printf("|              | |_  | |  | | | || | / _ \                     |\n");
    printf("|              |  _| | |__| |_| || |/ ___ \                    |\n");
    printf("|              |_|   |_____\___/ |_/_/   \_\                   |\n");
    printf("+==============================================================+\n");


    const char *opciones[] = {"Configuracion", "Jugar", "Salir"}; //vector de punteros a cadena de caracteres
    int seleccion;

    while (1) {
        seleccion = navegarMenu(opciones, 3);

        switch (seleccion) {
            case 0:
                MenuConfiguracion();
                break;
            case 1:
                MenuJuego();
                break;
            case 2:
                limpiarPantalla();
                printf("Saliendo del juego...\n");
                return;
        }
    }
}

void MenuConfiguracion() {
    const char *opciones[] = {"Introducir datos", "Mostrar", "Borrar", "Guardar", "Cargar", "Volver"};
    int seleccion;

    while (1) {
        seleccion = navegarMenu(opciones, 6);

        switch (seleccion) {
            case 0:
                printf("Funcion introducir datos.\n");
                break;
            case 1:
                printf("Mostrando configuracion.\n");
                break;
            case 2:
                printf("Borrando configuracion...\n");
                break;
            case 3:
                printf("Guardando configuracion...\n");
                break;
            case 4:
                printf("Cargando configuracion...\n");
                break;
            case 5:
                return;
        }
        system("pause");
    }
}

void MenuJuego() {
    const char *opciones[] = {"Jugar partida", "Reiniciar partida", "Resumen", "Volver"};
    int seleccion;

    while (1) {
        seleccion = navegarMenu(opciones, 4);

        switch (seleccion) {
            case 0:
                printf("Funcion Jugar partida.\n");
                break;
            case 1:
                printf("Funcion Reiniciar partida.\n");
                break;
            case 2:
                printf("Funcion Mostrar resumen.\n");
                break;
            case 3:
                return;
        }
        system("pause");
    }
}
