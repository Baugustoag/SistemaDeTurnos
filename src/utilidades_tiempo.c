#include "utilidades_tiempo.h"
#include <stdio.h>  
#include <string.h> 


time_t convertirADatetime(const char *fecha, const char *hora) {
    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));
    sscanf(fecha, "%4d-%2d-%2d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday);
    sscanf(hora, "%2d:%2d", &tm.tm_hour, &tm.tm_min);

    tm.tm_year -= 1900;
    tm.tm_mon -= 1;
    tm.tm_sec = 0;

    tm.tm_isdst = -1;

    return mktime(&tm);
}


void generarHorasDelDia(char horas[][6], int *cantidad) {
    *cantidad = 0;
    for (int i = 0; i < 24; i++) {
        sprintf(horas[*cantidad], "%02d:00", i);
        (*cantidad)++;
    }
}
