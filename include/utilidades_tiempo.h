#ifndef UTILIDADES_TIEMPO_H
#define UTILIDADES_TIEMPO_H

#include <time.h> // Necesario para time_t

// Prototipos de funciones de tiempo
time_t convertirADatetime(const char *fecha, const char *hora);
void generarHorasDelDia(char horas[][6], int *cantidad);

#endif // UTILIDADES_TIEMPO_H