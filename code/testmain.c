#include <stdio.h>
#include <string.h>
#include "Datos.h"  // Asegúrate de incluir el archivo de cabecera correcto

int main() {
    // Cargar la configuración del juego
    ConfiguracionJuego config = cargar_config();

    // Mostrar la configuración cargada
    mostrar_configuracion(config);

	modificar_config(&config);

    mostrar_configuracion(config);
    
    // Guardar la configuración en el archivo
    guardar_config(config);

    // Liberar memoria dinámica
    free(config.Tipo_barcos);
    free(config.num_barcos);

    return 0;
}