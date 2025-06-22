#ifndef TURNOS_H
#define TURNOS_H

#include <time.h> 

// Constantes
#define MAX_CANCHAS 3
#define ARCHIVO_TURNOS "turnos.dat"
#define DIAS_MAX_FUTURO 7 

typedef struct Turno {
    int cancha;
    char dia[11];
    char hora[6];
    char nombre[51];
    struct Turno *sig;
} Turno;

extern Turno *listaTurnos;


void cargarTurnosDesdeArchivo();
void guardarTurnosEnArchivo();
int turnoDisponible(int cancha, const char *dia, const char *hora);
void liberarListaTurnos(); 

#endif 
