#ifndef TURNOS_H
#define TURNOS_H

#include <time.h> // Necesario para time_t

// Constantes
#define MAX_CANCHAS 2
#define ARCHIVO_TURNOS "turnos.dat"
#define DIAS_MAX_FUTURO 7 // Límite para reserva de turnos futuros

// Estructura del Turno
typedef struct Turno {
    int cancha;
    char dia[11];
    char hora[6];
    char nombre[51];
    struct Turno *sig;
} Turno;

// Variable global (se declarará extern en .c donde se use)
extern Turno *listaTurnos;

// Prototipos de funciones de gestion de turnos
void cargarTurnosDesdeArchivo();
void guardarTurnosEnArchivo();
int turnoDisponible(int cancha, const char *dia, const char *hora);
void liberarListaTurnos(); // Nueva funcion para liberar memoria

#endif // TURNOS_H