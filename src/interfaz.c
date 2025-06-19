#include "interfaz.h"
#include "turnos.h"          // Para Turno, listaTurnos, MAX_CANCHAS, DIAS_MAX_FUTURO, turnoDisponible
#include "validaciones.h"    // Para validarFecha, validarHora, getValidatedIntInput, clearInputBuffer
#include "utilidades_tiempo.h" // Para convertirADatetime, generarHorasDelDia

#include <stdio.h>   // Para printf, scanf, fgets
#include <stdlib.h>  // Para malloc, free
#include <string.h>  // Para strcmp, strcpy, strncpy, strcspn
#include <time.h>    // Para time, difftime

// Implementacion de la funcion para mostrar el menu
void mostrarMenu() {
    printf("\n==== SISTEMA DE RESERVAS ====\n");
    printf("1. Reservar turno\n");
    printf("2. Listar turnos\n");
    printf("3. Cancelar turno\n");
    printf("4. Reagendar turno\n");
    printf("0. Salir\n");
}

// Implementacion de la funcion para reservar un turno
void reservarTurno() {
    Turno *nuevo = malloc(sizeof(Turno));
    if (nuevo == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo turno. Por favor, intente mas tarde.\n");
        return;
    }

    printf("Ingrese dia (YYYY-MM-DD): ");
    scanf("%10s", nuevo->dia);
    clearInputBuffer();
    if (!validarFecha(nuevo->dia)) {
        printf("Error: Fecha invalida o en formato incorrecto. Por favor, use YYYY-MM-DD y asegure que sea una fecha real.\n");
        free(nuevo);
        return;
    }

    printf("Ingrese hora de inicio (HH:MM - solo horas en punto): ");
    scanf("%5s", nuevo->hora);
    clearInputBuffer();
    if (!validarHora(nuevo->hora)) {
        printf("Error: Hora invalida o en formato incorrecto. Por favor, use HH:MM y solo horas en punto.\n");
        free(nuevo);
        return;
    }

    nuevo->cancha = getValidatedIntInput("Ingrese numero de cancha (1 o 2): ", 1, MAX_CANCHAS);

    printf("Ingrese su nombre: ");
    fgets(nuevo->nombre, sizeof(nuevo->nombre), stdin);
    nuevo->nombre[strcspn(nuevo->nombre, "\n")] = '\0';

    time_t turnoTime = convertirADatetime(nuevo->dia, nuevo->hora);
    time_t ahora = time(NULL);
    time_t limiteFuturo = ahora + (DIAS_MAX_FUTURO * 24 * 60 * 60);

    if (difftime(turnoTime, ahora) < 60) {
        printf("Error: No se puede reservar un turno en el pasado o con menos de 1 minuto de anticipacion.\n");
        free(nuevo);
        return;
    }

    if (difftime(turnoTime, limiteFuturo) > 0) {
        printf("Error: Solo se pueden reservar turnos con hasta %d dias de anticipacion. Su fecha excede este limite.\n", DIAS_MAX_FUTURO);
        free(nuevo);
        return;
    }

    if (!turnoDisponible(nuevo->cancha, nuevo->dia, nuevo->hora)) {
        printf("Error: Turno ya reservado para esa fecha, hora y cancha. Por favor, elija otro.\n");
        free(nuevo);
        return;
    }

    nuevo->sig = listaTurnos;
    listaTurnos = nuevo;
    printf("Turno reservado con exito.\n");
}

// Implementacion de la funcion para listar turnos
void listarTurnos() {
    char dia[11];
    int cancha;

    printf("Ingrese dia a consultar (YYYY-MM-DD): ");
    scanf("%10s", dia);
    clearInputBuffer();
    if (!validarFecha(dia)) {
        printf("Error: Fecha invalida o en formato incorrecto.\n");
        return;
    }

    cancha = getValidatedIntInput("Ingrese numero de cancha (1 o 2): ", 1, MAX_CANCHAS);

    char horas[24][6];
    int cantidad;
    generarHorasDelDia(horas, &cantidad);

    printf("\n--- Turnos del dia %s en cancha %d ---\n", dia, cancha);
    int found_any_turn = 0;
    for (int i = 0; i < cantidad; i++) {
        Turno *aux = listaTurnos;
        int ocupado = 0;
        char nombre_reserva[51] = "N/A";
        while (aux) {
            if (aux->cancha == cancha && strcmp(aux->dia, dia) == 0 && strcmp(aux->hora, horas[i]) == 0) {
                ocupado = 1;
                strncpy(nombre_reserva, aux->nombre, sizeof(nombre_reserva) - 1);
                nombre_reserva[sizeof(nombre_reserva) - 1] = '\0';
                found_any_turn = 1;
                break;
            }
            aux = aux->sig;
        }

        if (ocupado) {
            printf("%s - OCUPADO por: %s\n", horas[i], nombre_reserva);
        } else {
            printf("%s - LIBRE\n", horas[i]);
        }
    }
    if (!found_any_turn) {
        printf("No hay turnos registrados para el dia %s en la cancha %d. Todos los horarios estan LIBRES.\n", dia, cancha);
    }
}

// Implementacion de la funcion para cancelar un turno
void cancelarTurno() {
    char dia[11], hora[6], nombre[51];
    int cancha;

    printf("--- Cancelar Turno ---\n");
    printf("Ingrese dia (YYYY-MM-DD) del turno a cancelar: ");
    scanf("%10s", dia);
    clearInputBuffer();
    if (!validarFecha(dia)) {
        printf("Error: Fecha invalida o en formato incorrecto.\n");
        return;
    }

    printf("Ingrese hora (HH:MM) del turno a cancelar: ");
    scanf("%5s", hora);
    clearInputBuffer();
    if (!validarHora(hora)) {
        printf("Error: Hora invalida o en formato incorrecto.\n");
        return;
    }

    cancha = getValidatedIntInput("Ingrese cancha del turno a cancelar (1 o 2): ", 1, MAX_CANCHAS);

    printf("Ingrese su nombre para confirmar la cancelacion: ");
    fgets(nombre, sizeof(nombre), stdin);
    nombre[strcspn(nombre, "\n")] = '\0';

    time_t turnoTime = convertirADatetime(dia, hora);
    time_t ahora = time(NULL);

    if (difftime(turnoTime, ahora) < 0) {
        printf("Error: No se puede cancelar un turno que ya ha pasado.\n");
        return;
    }
    // 7200 segundos = 2 horas
    if (difftime(turnoTime, ahora) < 7200) {
        printf("Error: No se puede cancelar el turno con menos de 2 horas de anticipacion.\n");
        return;
    }

    Turno **aux = &listaTurnos;
    while (*aux) {
        if ((*aux)->cancha == cancha && strcmp((*aux)->dia, dia) == 0 &&
            strcmp((*aux)->hora, hora) == 0 && strcmp((*aux)->nombre, nombre) == 0) {
            Turno *temp = *aux;
            *aux = (*aux)->sig;
            free(temp);
            printf("Turno cancelado con exito.\n");
            return;
        }
        aux = &(*aux)->sig;
    }
    printf("Error: No se encontro el turno con los datos proporcionados (fecha, hora, cancha y/o nombre no coinciden).\n");
}

// Implementacion de la funcion para reagendar un turno
void reagendarTurno() {
    char diaAntiguo[11], horaAntigua[6], nombreAntiguo[51];
    int canchaAntigua;

    printf("--- Reagendar Turno ---\n");
    printf("Primero, ingrese los datos del turno que desea reagendar:\n");
    printf("Dia (YYYY-MM-DD): ");
    scanf("%10s", diaAntiguo);
    clearInputBuffer();
    if (!validarFecha(diaAntiguo)) {
        printf("Error: Fecha invalida para el turno actual.\n");
        return;
    }

    printf("Hora (HH:MM): ");
    scanf("%5s", horaAntigua);
    clearInputBuffer();
    if (!validarHora(horaAntigua)) {
        printf("Error: Hora invalida para el turno actual.\n");
        return;
    }

    canchaAntigua = getValidatedIntInput("Cancha del turno actual (1 o 2): ", 1, MAX_CANCHAS);

    printf("Su nombre: ");
    fgets(nombreAntiguo, sizeof(nombreAntiguo), stdin);
    nombreAntiguo[strcspn(nombreAntiguo, "\n")] = '\0';

    Turno **aux = &listaTurnos;
    Turno *turnoAEncontrar = NULL;

    while (*aux) {
        if ((*aux)->cancha == canchaAntigua &&
            strcmp((*aux)->dia, diaAntiguo) == 0 &&
            strcmp((*aux)->hora, horaAntigua) == 0 &&
            strcmp((*aux)->nombre, nombreAntiguo) == 0) {
            turnoAEncontrar = *aux;
            break;
        }
        aux = &(*aux)->sig;
    }

    if (turnoAEncontrar == NULL) {
        printf("Error: No se encontro el turno con esos datos o el nombre no coincide.\n");
        return;
    }

    time_t turnoTime = convertirADatetime(diaAntiguo, horaAntigua);
    time_t ahora = time(NULL);
    if (difftime(turnoTime, ahora) < 0) {
        printf("Error: No se puede reagendar un turno que ya ha pasado.\n");
        return;
    }

    printf("\nAhora, ingrese los NUEVOS datos para el turno:\n");
    char nuevoDia[11], nuevaHora[6];
    int nuevaCancha;

    printf("Nuevo dia (YYYY-MM-DD): ");
    scanf("%10s", nuevoDia);
    clearInputBuffer();
    if (!validarFecha(nuevoDia)) {
        printf("Error: Nueva fecha invalida.\n");
        return;
    }

    printf("Nueva hora de inicio (HH:MM - solo horas en punto): ");
    scanf("%5s", nuevaHora);
    clearInputBuffer();
    if (!validarHora(nuevaHora)) {
        printf("Error: Nueva hora invalida.\n");
        return;
    }

    nuevaCancha = getValidatedIntInput("Nueva cancha (1 o 2): ", 1, MAX_CANCHAS);

    time_t nuevoTurnoTime = convertirADatetime(nuevoDia, nuevaHora);
    time_t limiteFuturo = ahora + (DIAS_MAX_FUTURO * 24 * 60 * 60);

    if (difftime(nuevoTurnoTime, ahora) < 60) {
        printf("Error: El nuevo turno no puede ser en el pasado o con menos de 1 minuto de anticipacion.\n");
        return;
    }

    if (difftime(nuevoTurnoTime, limiteFuturo) > 0) {
        printf("Error: Solo se pueden reservar turnos con hasta %d dias de anticipacion. Su nueva fecha excede este limite.\n", DIAS_MAX_FUTURO);
        return;
    }

    Turno *temp_aux = listaTurnos;
    while(temp_aux != NULL) {
        if (temp_aux != turnoAEncontrar &&
            temp_aux->cancha == nuevaCancha &&
            strcmp(temp_aux->dia, nuevoDia) == 0 &&
            strcmp(temp_aux->hora, nuevaHora) == 0) {
            printf("Error: El nuevo horario ya esta reservado por otro turno. No se puede reagendar.\n");
            return;
        }
        temp_aux = temp_aux->sig;
    }

    strcpy(turnoAEncontrar->dia, nuevoDia);
    strcpy(turnoAEncontrar->hora, nuevaHora);
    turnoAEncontrar->cancha = nuevaCancha;

    printf("Turno reagendado con exito.\n");
}