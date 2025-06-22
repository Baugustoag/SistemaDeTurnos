#include "interfaz.h"    
#include "turnos.h"      
#include "validaciones.h" 
#include <stdio.h>       

int main() {
    cargarTurnosDesdeArchivo();
    int opcion;
    do {
        mostrarMenu();
        opcion = getValidatedIntInput("Seleccione una opcion: ", 0, 4); 

        switch(opcion) {
            case 1: reservarTurno(); break;
            case 2: listarTurnos(); break;
            case 3: cancelarTurno(); break;
            case 4: reagendarTurno(); break;
            case 0: guardarTurnosEnArchivo(); printf("Saliendo...\n"); break;
          
        }
    } while(opcion != 0);

    liberarListaTurnos();
    return 0;
}
