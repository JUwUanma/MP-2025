#include <stdio.h>
#include "Datos.h"  // Asegúrate de incluir el archivo de cabecera correcto

int main() {
    // Cargar la configuración del juego
    ConfiguracionJuego config = cargar_config();

    // Mostrar la configuración cargada
    mostrar_configuracion(config);

    // Liberar memoria dinámica
    free(config.Tipo_barcos);
    free(config.num_barcos);

    return 0;
}