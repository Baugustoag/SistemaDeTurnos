#include "turnos.h"
#include <stdio.h>
#include <stdlib.h> // Para malloc y free
#include <string.h> // Para strcmp

// La variable global listaTurnos se inicializa aqui
Turno *listaTurnos = NULL;

// Implementacion de la funcion para cargar turnos desde archivo
void cargarTurnosDesdeArchivo() {
    FILE *f = fopen(ARCHIVO_TURNOS, "rb");
    if (!f) {
        //printf("Advertencia: No se pudo abrir el archivo de turnos (%s). Se creara uno nuevo si se guardan datos.\n", ARCHIVO_TURNOS);
        return;
    }
    Turno t;
    size_t read_bytes;
    while ((read_bytes = fread(&t, sizeof(Turno) - sizeof(Turno *), 1, f)) == 1) {
        Turno *nuevo = malloc(sizeof(Turno));
        if (nuevo == NULL) {
            printf("Error critico: Fallo al asignar memoria al cargar turnos. Datos incompletos.\n");
            break;
        }
        *nuevo = t;
        nuevo->sig = listaTurnos;
        listaTurnos = nuevo;
    }
    if (ferror(f)) {
        printf("Error de lectura al cargar turnos desde el archivo %s.\n", ARCHIVO_TURNOS);
    }
    fclose(f);
}

// Implementacion de la funcion para guardar turnos en archivo
void guardarTurnosEnArchivo() {
    FILE *f = fopen(ARCHIVO_TURNOS, "wb");
    if (!f) {
        printf("Error: No se pudo abrir el archivo de turnos (%s) para guardar. Los cambios no seran persistidos.\n", ARCHIVO_TURNOS);
        return;
    }
    Turno *aux = listaTurnos;
    while (aux) {
        if (fwrite(aux, sizeof(Turno) - sizeof(Turno *), 1, f) != 1) {
            printf("Error de escritura al guardar un turno en el archivo %s. El archivo podria estar corrupto.\n", ARCHIVO_TURNOS);
            break;
        }
        aux = aux->sig;
    }
    if (ferror(f)) {
        printf("Error final de escritura al guardar turnos en el archivo %s.\n", ARCHIVO_TURNOS);
    }
    fclose(f);
}

// Implementacion de la funcion para verificar si un turno esta disponible
int turnoDisponible(int cancha, const char *dia, const char *hora) {
    Turno *aux = listaTurnos;
    while (aux) {
        if (aux->cancha == cancha && strcmp(aux->dia, dia) == 0 && strcmp(aux->hora, hora) == 0) {
            return 0; // Turno ocupado
        }
        aux = aux->sig;
    }
    return 1; // Turno disponible
}

// Implementacion de la funcion para liberar toda la memoria de la lista
void liberarListaTurnos() {
    Turno *current = listaTurnos;
    Turno *next;
    while (current != NULL) {
        next = current->sig;
        free(current);
        current = next;
    }
    listaTurnos = NULL; // Asegurar que la lista este vacia
}