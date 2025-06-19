#include "validaciones.h"
#include <stdio.h>
#include <string.h> // Para memset
#include <time.h>   // Para struct tm, time_t, mktime, localtime

// Implementacion de la funcion para limpiar el buffer de entrada
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Implementacion de la funcion para obtener entrada entera validada
int getValidatedIntInput(const char *prompt, int min, int max) {
    int value;
    int scanned_items;
    while (1) {
        printf("%s", prompt);
        scanned_items = scanf("%d", &value);
        clearInputBuffer(); // Siempre limpiar el buffer despues de scanf

        if (scanned_items == 1) {
            if (value >= min && value <= max) {
                return value;
            } else {
                printf("Entrada fuera de rango. Por favor, ingrese un numero entre %d y %d.\n", min, max);
            }
        } else {
            printf("Entrada invalida. Debe ingresar un numero.\n");
        }
    }
}

// Implementacion de la validacion de fecha
int validarFecha(const char *fecha) {
    int y, m, d;
    struct tm tm;

    if (sscanf(fecha, "%4d-%2d-%2d", &y, &m, &d) != 3) {
        return 0;
    }

    if (y < 1900 || m < 1 || m > 12 || d < 1 || d > 31) {
        return 0;
    }

    memset(&tm, 0, sizeof(struct tm));
    tm.tm_year = y - 1900;
    tm.tm_mon = m - 1;
    tm.tm_mday = d;
    tm.tm_isdst = -1;

    time_t rawtime = mktime(&tm);

    if (rawtime == (time_t)-1) {
        return 0;
    }

    struct tm *validated_tm = localtime(&rawtime);
    if (validated_tm == NULL ||
        validated_tm->tm_year + 1900 != y ||
        validated_tm->tm_mon + 1 != m ||
        validated_tm->tm_mday != d) {
        return 0;
    }

    return 1;
}

// Implementacion de la validacion de hora
int validarHora(const char *hora) {
    int h, m;
    if (sscanf(hora, "%2d:%2d", &h, &m) != 2) {
        return 0;
    }
    return (h >= 0 && h <= 23 && m == 0);
}