#include "interfaz.h"    // Para mostrarMenu, reservarTurno, listarTurnos, cancelarTurno, reagendarTurno
#include "turnos.h"      // Para cargarTurnosDesdeArchivo, guardarTurnosEnArchivo, liberarListaTurnos
#include "validaciones.h" // Para getValidatedIntInput (usado en main)
#include <stdio.h>       // Para printf

int main() {
    cargarTurnosDesdeArchivo();
    int opcion;
    do {
        mostrarMenu();
        opcion = getValidatedIntInput("Seleccione una opcion: ", 0, 4); // El rango es de 0 a 4

        switch(opcion) {
            case 1: reservarTurno(); break;
            case 2: listarTurnos(); break;
            case 3: cancelarTurno(); break;
            case 4: reagendarTurno(); break;
            case 0: guardarTurnosEnArchivo(); printf("Saliendo...\n"); break;
            // No necesitamos un default para "Opcion invalida" aqui porque getValidatedIntInput ya lo maneja
        }
    } while(opcion != 0);

    liberarListaTurnos(); // Asegurarse de liberar la memoria antes de salir
    return 0;
}