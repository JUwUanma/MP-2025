#include <stdio.h>
#include <stdlib.h>
#include "Interfaz.h"
#include "Datos.h"
#include "logica.h"
#include "Tablero.h"

int main() {
    

    ConfiguracionJuego config=cargar_config();
    ConfiguracionJuego *Pconfig = &config;
    ControlPartida ControlP = cargar_controlPartida(config);
    Registro_Maquina reg_maq;
    


    MenuPrincipal(config, ControlP, reg_maq);
    return 0;
}
