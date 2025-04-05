#ifndef INTERFAZ_H_INCLUDED
#define INTERFAZ_H_INCLUDED
/*
   Precodici�n: N/A
   Postcondici�n: Se limpia la pantalla
*/
void limpiarPantalla();
/*
   Precondici�n: N/A
   Postcondici�n: El usuario selecciona una opci�n y se dirige al men� correspondiente.
 */
void MenuPrincipal();

/*
   Precondici�n: N/A.
   Postcondici�n: Permite configurar los par�metros del juego o volver al men� principal.
 */
void MenuConfiguracion();

/*
   Precondici�n: La configuraci�n debe estar completa para jugar.
   Postcondici�n: Permite iniciar, reiniciar o ver un resumen de la partida.
 */
void MenuJuego();

#endif // INTERFAZ_H_INCLUDED
