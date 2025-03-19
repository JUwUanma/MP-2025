#ifndef INTERFAZ_H_INCLUDED
#define INTERFAZ_H_INCLUDED

/*
   Precondición: N/A
   Postcondición: El usuario selecciona una opción y se dirige al menú correspondiente.
 */
void MenuPrincipal();

/*
   Precondición: N/A.
   Postcondición: Permite configurar los parámetros del juego o volver al menú principal.
 */
void MenuConfiguracion();

/*
   Precondición: La configuración debe estar completa para jugar.
   Postcondición: Permite iniciar, reiniciar o ver un resumen de la partida.
 */
void MenuJuego();

#endif // INTERFAZ_H_INCLUDED
