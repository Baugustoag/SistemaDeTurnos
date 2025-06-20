#include "interfaz.h"
#include "turnos.h"
#include "validaciones.h"
#include "utilidades_tiempo.h" // Se sigue usando para convertirADatetime y generarHorasDelDia

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>    // Para time, difftime, localtime, sprintf

// Implementacion de la funcion para mostrar el menu
void mostrarMenu() {
    printf("\n==== SISTEMA DE RESERVAS ====\n");
    printf("1. Reservar turno\n");
    printf("2. Listar turnos\n");
    printf("3. Cancelar turno\n");
    printf("4. Reagendar turno\n");
    printf("0. Salir\n");
}

// Función auxiliar para obtener el año, mes y día actuales del sistema
void obtenerFechaActual(int *anio, int *mes, int *dia) {
    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);
    *anio = local_time->tm_year + 1900;
    *mes = local_time->tm_mon + 1;
    *dia = local_time->tm_mday; // Este no lo usaremos directamente, pero es útil tenerlo
}

// Implementacion de la funcion para reservar un turno
void reservarTurno() {
    Turno *nuevo = malloc(sizeof(Turno));
    if (nuevo == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo turno. Por favor, intente mas tarde.\n");
        return;
    }

    int dia_reserva, hora_reserva_entera;
    int anio_actual, mes_actual, dia_actual; // Variables para la fecha actual

    obtenerFechaActual(&anio_actual, &mes_actual, &dia_actual); // Obtener la fecha del sistema

    printf("\n--- Reservar Turno ---\n");
    printf("El turno se reservara para el mes actual (%02d/%d).\n", mes_actual, anio_actual);

    // Pedir solo el numero de dia
    while (1) {
        dia_reserva = getValidatedIntInput("Ingrese el numero de dia para la reserva: ", 1, 31);
        if (validarDiaDelMes(dia_reserva, mes_actual, anio_actual)) {
            break;
        } else {
            printf("Error: El dia %d no es valido para el mes %02d.\n", dia_reserva, mes_actual);
        }
    }
    // Construir la cadena de fecha completa (YYYY-MM-DD)
    sprintf(nuevo->dia, "%04d-%02d-%02d", anio_actual, mes_actual, dia_reserva);

    // Pedir solo la hora entera
    while (1) {
        hora_reserva_entera = getValidatedIntInput("Ingrese la hora de inicio (0-23, solo horas en punto): ", 0, 23);
        if (validarHoraEntera(hora_reserva_entera)) {
            break;
        } else {
            printf("Error: Hora invalida. Ingrese un numero entre 0 y 23.\n");
        }
    }
    // Construir la cadena de hora (HH:MM)
    sprintf(nuevo->hora, "%02d:00", hora_reserva_entera);

    nuevo->cancha = getValidatedIntInput("Ingrese numero de cancha (1 o 2): ", 1, MAX_CANCHAS);

    printf("Ingrese su nombre: ");
    fgets(nuevo->nombre, sizeof(nuevo->nombre), stdin);
    nuevo->nombre[strcspn(nuevo->nombre, "\n")] = '\0';

    time_t turnoTime = convertirADatetime(nuevo->dia, nuevo->hora);
    time_t ahora = time(NULL);
    time_t limiteFuturo = ahora + (DIAS_MAX_FUTURO * 24 * 60 * 60);

    // Revalidar el turnoTime contra el tiempo actual y limite futuro
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
    printf("Turno reservado con exito para el %s a las %s en la cancha %d.\n", nuevo->dia, nuevo->hora, nuevo->cancha);
}

// Implementacion de la funcion para listar turnos
#include "interfaz.h"
#include "turnos.h"
#include "validaciones.h"
#include "utilidades_tiempo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ... (Las funciones mostrarMenu(), obtenerFechaActual(), reservarTurno() van aquí, sin cambios)

// Implementacion de la funcion para listar turnos
void listarTurnos() {
    int dia_consulta, cancha_consulta;
    char dia_str[11];
    int anio_actual, mes_actual, dia_actual;

    obtenerFechaActual(&anio_actual, &mes_actual, &dia_actual);

    printf("\n--- Consultar Disponibilidad ---\n");
    printf("Consultara para el mes actual (%02d/%d).\n", mes_actual, anio_actual);

    // Pedir solo el numero de dia para la consulta
    while (1) {
        dia_consulta = getValidatedIntInput("Ingrese el numero de dia a consultar: ", 1, 31);
        if (validarDiaDelMes(dia_consulta, mes_actual, anio_actual)) {
            break;
        } else {
            printf("Error: El dia %d no es valido para el mes %02d.\n", dia_consulta, mes_actual);
        }
    }
    // Construir la cadena de fecha completa (YYYY-MM-DD)
    sprintf(dia_str, "%04d-%02d-%02d", anio_actual, mes_actual, dia_consulta);

    cancha_consulta = getValidatedIntInput("Ingrese numero de cancha (1 o 2): ", 1, MAX_CANCHAS);

    char horas[24][6];
    int cantidad;
    generarHorasDelDia(horas, &cantidad); // Esta función ya genera "HH:00"

    printf("\n--- Disponibilidad para el dia %s en cancha %d ---\n", dia_str, cancha_consulta);
    int found_any_turn = 0;
    for (int i = 0; i < cantidad; i++) {
        Turno *aux = listaTurnos;
        int ocupado = 0;
        // char nombre_reserva[51] = "N/A"; // Esta línea ya no es necesaria
        while (aux) {
            if (aux->cancha == cancha_consulta && strcmp(aux->dia, dia_str) == 0 && strcmp(aux->hora, horas[i]) == 0) {
                ocupado = 1;
                // strncpy(nombre_reserva, aux->nombre, sizeof(nombre_reserva) - 1); // ¡ELIMINADA!
                // nombre_reserva[sizeof(nombre_reserva) - 1] = '\0'; // ¡ELIMINADA!
                found_any_turn = 1;
                break;
            }
            aux = aux->sig;
        }

        if (ocupado) {
            printf("%s - OCUPADO\n", horas[i]); // ¡MODIFICADA! Solo imprime OCUPADO
        } else {
            printf("%s - LIBRE\n", horas[i]);
        }
    }
    if (!found_any_turn) {
        printf("No hay turnos registrados para el dia %s en la cancha %d. Todos los horarios estan LIBRES.\n", dia_str, cancha_consulta);
    } else {
        printf("La tabla muestra la disponibilidad para los horarios del dia %s en la cancha %d.\n", dia_str, cancha_consulta);
    }
}

// Implementacion de la funcion para cancelar un turno
void cancelarTurno() {
    int dia_cancelar, hora_cancelar_entera;
    char dia_str[11], hora_str[6], nombre[51];
    int cancha_cancelar;
    int anio_actual, mes_actual, dia_actual;

    obtenerFechaActual(&anio_actual, &mes_actual, &dia_actual);

    printf("--- Cancelar Turno ---\n");
    printf("El turno a cancelar se buscara para el mes actual (%02d/%d).\n", mes_actual, anio_actual);

    // Pedir solo el numero de dia para la cancelacion
    while (1) {
        dia_cancelar = getValidatedIntInput("Ingrese el numero de dia del turno a cancelar: ", 1, 31);
        if (validarDiaDelMes(dia_cancelar, mes_actual, anio_actual)) {
            break;
        } else {
            printf("Error: El dia %d no es valido para el mes %02d.\n", dia_cancelar, mes_actual);
        }
    }
    sprintf(dia_str, "%04d-%02d-%02d", anio_actual, mes_actual, dia_cancelar);

    // Pedir solo la hora entera para la cancelacion
    while (1) {
        hora_cancelar_entera = getValidatedIntInput("Ingrese la hora del turno a cancelar (0-23): ", 0, 23);
        if (validarHoraEntera(hora_cancelar_entera)) {
            break;
        } else {
            printf("Error: Hora invalida. Ingrese un numero entre 0 y 23.\n");
        }
    }
    sprintf(hora_str, "%02d:00", hora_cancelar_entera);

    cancha_cancelar = getValidatedIntInput("Ingrese cancha del turno a cancelar (1 o 2): ", 1, MAX_CANCHAS);

    printf("Ingrese su nombre para confirmar la cancelacion: ");
    fgets(nombre, sizeof(nombre), stdin);
    nombre[strcspn(nombre, "\n")] = '\0';

    time_t turnoTime = convertirADatetime(dia_str, hora_str);
    time_t ahora = time(NULL);

    if (difftime(turnoTime, ahora) < 0) {
        printf("Error: No se puede cancelar un turno que ya ha pasado.\n");
        return;
    }
    if (difftime(turnoTime, ahora) < 7200) { // 7200 segundos = 2 horas
        printf("Error: No se puede cancelar el turno con menos de 2 horas de anticipacion.\n");
        return;
    }

    Turno **aux = &listaTurnos;
    while (*aux) {
        if ((*aux)->cancha == cancha_cancelar && strcmp((*aux)->dia, dia_str) == 0 &&
            strcmp((*aux)->hora, hora_str) == 0 && strcmp((*aux)->nombre, nombre) == 0) {
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
    int dia_antiguo_int, hora_antigua_int;
    char diaAntiguo[11], horaAntigua[6], nombreAntiguo[51];
    int canchaAntigua;
    int anio_actual, mes_actual, dia_actual;

    obtenerFechaActual(&anio_actual, &mes_actual, &dia_actual);

    printf("--- Reagendar Turno ---\n");
    printf("Primero, ingrese los datos del turno que desea reagendar (para el mes actual %02d/%d):\n", mes_actual, anio_actual);

    // Pedir solo el numero de dia del turno antiguo
    while (1) {
        dia_antiguo_int = getValidatedIntInput("Dia: ", 1, 31);
        if (validarDiaDelMes(dia_antiguo_int, mes_actual, anio_actual)) {
            break;
        } else {
            printf("Error: El dia %d no es valido para el mes %02d.\n", dia_antiguo_int, mes_actual);
        }
    }
    sprintf(diaAntiguo, "%04d-%02d-%02d", anio_actual, mes_actual, dia_antiguo_int);

    // Pedir solo la hora entera del turno antiguo
    while (1) {
        hora_antigua_int = getValidatedIntInput("Hora (0-23): ", 0, 23);
        if (validarHoraEntera(hora_antigua_int)) {
            break;
        } else {
            printf("Error: Hora invalida. Ingrese un numero entre 0 y 23.\n");
        }
    }
    sprintf(horaAntigua, "%02d:00", hora_antigua_int);

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

    printf("\nAhora, ingrese los NUEVOS datos para el turno (para el mes actual %02d/%d):\n", mes_actual, anio_actual);
    int nuevoDia_int, nuevaHora_int;
    char nuevoDia_str[11], nuevaHora_str[6];
    int nuevaCancha;

    // Pedir solo el numero de dia del nuevo turno
    while (1) {
        nuevoDia_int = getValidatedIntInput("Nuevo dia: ", 1, 31);
        if (validarDiaDelMes(nuevoDia_int, mes_actual, anio_actual)) {
            break;
        } else {
            printf("Error: El nuevo dia %d no es valido para el mes %02d.\n", nuevoDia_int, mes_actual);
        }
    }
    sprintf(nuevoDia_str, "%04d-%02d-%02d", anio_actual, mes_actual, nuevoDia_int);

    // Pedir solo la hora entera del nuevo turno
    while (1) {
        nuevaHora_int = getValidatedIntInput("Nueva hora (0-23): ", 0, 23);
        if (validarHoraEntera(nuevaHora_int)) {
            break;
        } else {
            printf("Error: Nueva hora invalida. Ingrese un numero entre 0 y 23.\n");
        }
    }
    sprintf(nuevaHora_str, "%02d:00", nuevaHora_int);

    nuevaCancha = getValidatedIntInput("Nueva cancha (1 o 2): ", 1, MAX_CANCHAS);

    time_t nuevoTurnoTime = convertirADatetime(nuevoDia_str, nuevaHora_str);
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
            strcmp(temp_aux->dia, nuevoDia_str) == 0 &&
            strcmp(temp_aux->hora, nuevaHora_str) == 0) {
            printf("Error: El nuevo horario ya esta reservado por otro turno. No se puede reagendar.\n");
            return;
        }
        temp_aux = temp_aux->sig;
    }

    strcpy(turnoAEncontrar->dia, nuevoDia_str);
    strcpy(turnoAEncontrar->hora, nuevaHora_str);
    turnoAEncontrar->cancha = nuevaCancha;

    printf("Turno reagendado con exito.\n");
}