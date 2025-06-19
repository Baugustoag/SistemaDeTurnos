#ifndef VALIDACIONES_H
#define VALIDACIONES_H

// Prototipos de funciones de validacion y manejo de entrada
void clearInputBuffer();
int getValidatedIntInput(const char *prompt, int min, int max);
int validarFecha(const char *fecha);
int validarHora(const char *hora);

#endif // VALIDACIONES_H