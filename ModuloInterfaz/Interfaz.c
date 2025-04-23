#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Interfaz.h"
#include "Datos.h"
#include "logica.h"

int navegarMenu(const char *opciones[], int numOpciones) {
    int seleccion = 0;
    int tecla;

    while (1) {
        system("cls");
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

void MenuPrincipal(ConfiguracionJuego config, ControlPartida ControlP, Registro_Maquina reg_maq) {
        // Mensaje de bienvenida (se muestra solo al iniciar el juego)

    // printf("+==============================================================+\n");
    // printf("|   ____ ___ _____ _   ___     _______ _   _ ___ ____   ___    |\n");
    // printf("|  | __ )_ _| ____| \ | \ \   / / ____| \ | |_ _|  _ \ / _ \   |\n");
    // printf("|  |  _ \| ||  _| |  \| |\ \ / /|  _| |  \| || || | | | | | |  |\n");
    // printf("|  | |_) | || |___| |\  | \ V / | |___| |\  || || |_| | |_| |  |\n");
    // printf("|  |____/___|_____|_| \_|  \_/  |_____|_| \_|___|____/ \___/   |\n");
    // printf("|                           / \                                |\n");
    // printf("|                          / _ \                               |\n");
    // printf("|                         / ___ \                              |\n");
    // printf("|       _   _ _   _ _   _/_/__ \_\ ____    _        _          |\n");
    // printf("|      | | | | | | | \ | |  _ \_ _|  _ \  | |      / \         |\n");
    // printf("|      | |_| | | | |  \| | | | | || |_) | | |     / _ \        |\n");
    // printf("|      |  _  | |_| | |\  | |_| | ||  _ <  | |___ / ___ \       |\n");
    // printf("|      |_| |_|\___/|_|_\_|____/___|_| \_\ |_____/_/   \_\      |\n");
    // printf("|              |  ___| |   / _ \_   _|/ \                      |\n");
    // printf("|              | |_  | |  | | | || | / _ \                     |\n");
    // printf("|              |  _| | |__| |_| || |/ ___ \                    |\n");
    // printf("|              |_|   |_____\___/ |_/_/   \_\                   |\n");
    // printf("+==============================================================+\n");


    const char *opciones[] = {"Configuracion", "Jugar", "Salir"}; //vector de punteros a cadena de caracteres
    int seleccion;

    while (1) {
        seleccion = navegarMenu(opciones, 3);

        switch (seleccion) {
            case 0:
                MenuConfiguracion(config);
                break;
            case 1:
                MenuJuego(config,ControlP,reg_maq);
                break;
            case 2:
                system("cls");
                printf("Saliendo del juego...\n");
                return;
        }
    }
}

void MenuConfiguracion(ConfiguracionJuego config) {
    const char *opciones[] = {"Introducir datos", "Mostrar", "Borrar", "Guardar", "Cargar", "Volver"};
    int seleccion;

    while (1) {
        seleccion = navegarMenu(opciones, 6);

        switch (seleccion) {
            case 0:
                modificar_config(&config);
                break;
            case 1:
                mostrar_configuracion(config);
                break;
            case 2:
                borrar_config(&config);
                break;
            case 3:
                guardar_config(config);
                break;
            case 4:
                config=cargar_config();
                break;
            case 5:
                return;
        }
        system("pause");
    }
}

void MenuJuego(ConfiguracionJuego config, ControlPartida ControlP, Registro_Maquina reg_maq) {
    const char *opciones[] = {"Jugar partida", "Reiniciar partida", "Resumen", "Volver"};
    int seleccion;

    while (1) {
        seleccion = navegarMenu(opciones, 4);

        switch (seleccion) {
            case 0:
                flujoPartida(&config, &reg_maq, &ControlP);
                break;
            case 1:
                reiniciarPartida(config,ControlP,reg_maq);
                break;
            case 2:
                resumen_partida(config, ControlP);
                break;
            case 3:
                return;
        }
        system("pause");
    }
}
