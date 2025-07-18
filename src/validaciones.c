#include "validaciones.h"
#include <stdio.h>
#include <string.h> 
#include <time.h>   

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getValidatedIntInput(const char *prompt, int min, int max) {
    int value;
    int scanned_items;
    while (1) {
        printf("%s", prompt);
        scanned_items = scanf("%d", &value);
        clearInputBuffer(); 

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




int validarDiaDelMes(int dia, int mes, int anio) {
    struct tm tm = {0}; 
    tm.tm_year = anio - 1900;
    tm.tm_mon = mes - 1;
    tm.tm_mday = dia;
    tm.tm_isdst = -1; 

    time_t rawtime = mktime(&tm);

    if (rawtime == (time_t)-1) {
        return 0;
    }

    struct tm *validated_tm = localtime(&rawtime);
    if (validated_tm == NULL ||
        validated_tm->tm_year + 1900 != anio ||
        validated_tm->tm_mon + 1 != mes ||
        validated_tm->tm_mday != dia) {
        return 0;
    }

    return 1;
}


int validarHoraEntera(int hora) {
    return (hora >= 0 && hora <= 23);
}
