#ifndef VALIDACIONES_H
#define VALIDACIONES_H

// Prototipos de funciones de validacion y manejo de entrada
void clearInputBuffer();
int getValidatedIntInput(const char *prompt, int min, int max);
// int validarFecha(const char *fecha); // ¡ELIMINADA!
// int validarHora(const char *hora);   // ¡ELIMINADA!

int validarDiaDelMes(int dia, int mes, int anio); // Se mantiene
int validarHoraEntera(int hora); // ¡NUEVA FUNCIÓN!

#endif // VALIDACIONES_H