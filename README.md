# Sistema de Reservas de Turnos en C

Este es un sistema simple de reservas de turnos implementado en lenguaje C. Permite a los usuarios gestionar citas, reservar nuevos turnos, cancelarlos, y ver listados de turnos ocupados y disponibles. Los datos de los turnos se guardan persistentemente en un archivo binario.

## Características

* **Gestión de Turnos:** Permite reservar, cancelar y editar turnos.
* **Listado de Turnos:** Visualiza turnos ocupados y disponibles.
* **Persistencia de Datos:** Guarda y carga los turnos desde un archivo binario (`turns.dat`).
* **Estructuras Dinámicas:** Utiliza una **lista enlazada** para almacenar y gestionar los turnos de manera eficiente, permitiendo inserciones, eliminaciones, búsquedas, ediciones y recorridos.
* **Ordenación:** Implementa un algoritmo de ordenación (Bubble Sort) para organizar los turnos por fecha y hora.
* **Validación de Entrada:** Realiza validaciones básicas para fechas y horas al reservar o editar turnos.
* **Interfaz de Consola:** Interacción completa a través de la línea de comandos.

## Requisitos

* Un compilador de C (por ejemplo, GCC).

## Cómo Compilar y Ejecutar

1.  **Clonar el repositorio:**
    ```bash
    git clone [https://github.com/tu-usuario/nombre-del-repo.git](https://github.com/tu-usuario/nombre-del-repo.git)
    cd nombre-del-repo
    ```
    (Reemplaza `tu-usuario` y `nombre-del-repo` con los datos de tu repositorio real).

2.  **Compilar el código:**
    Abre una terminal en el directorio del proyecto y ejecuta:
    ```bash
    gcc -o sistema_turnos main.c -Wall
    ```
    (`main.c` es el nombre del archivo C principal. Si usas otro nombre, ajústalo).

3.  **Ejecutar el programa:**
    ```bash
    ./sistema_turnos
    ```

## Estructura del Código

El programa está organizado en las siguientes secciones lógicas y funciones:

* **`struct Turno`**: Define la estructura de datos para cada turno, incluyendo su ID, fecha, hora, nombre del cliente y estado de ocupación.
* **Variables Globales**: `lista_turnos` (puntero a la cabeza de la lista enlazada) y `next_turn_id` (para IDs únicos).
* **Funciones de Gestión de Archivos**:
    * `cargar_turnos_desde_archivo()`: Lee los turnos del archivo `turns.dat`.
    * `guardar_turnos_en_archivo()`: Escribe los turnos actuales en el archivo `turns.dat`.
* **Funciones de Gestión de la Lista Enlazada (Estructuras Dinámicas)**:
    * `insertar_turno()`: Agrega un nuevo turno a la lista.
    * `eliminar_turno_por_id()`: Remueve un turno por su ID.
    * `buscar_turno_por_id()`: Encuentra un turno específico.
    * `editar_turno_por_id()`: Modifica los datos de un turno existente.
    * `recorrer_lista_turnos()`: Imprime todos los turnos en la consola.
    * `liberar_memoria_turnos()`: Libera la memoria asignada dinámicamente.
* **Funciones de Interacción con el Usuario / Lógica Principal**:
    * `mostrar_menu()`: Presenta las opciones al usuario.
    * `reservar_turno()`: Guía al usuario para crear una nueva reserva.
    * `cancelar_turno()`: Permite liberar o eliminar un turno.
    * `mostrar_turnos_disponibles()`: Lista los turnos que no están ocupados.
    * `mostrar_turnos_ocupados()`: Lista los turnos que están reservados.
* **Algoritmos de Ordenación y Búsqueda**:
    * `ordenar_turnos_por_fecha_hora()`: Ordena la lista de turnos (por fecha y hora).
    * `intercambiar_turnos()`: Función auxiliar para el algoritmo de ordenación.
    * `buscar_turno_por_id()`: (Mencionado anteriormente, también es una función de búsqueda).
* **Funciones de Validación**:
    * `es_fecha_hora_valida()`: Valida que una fecha y hora ingresadas sean coherentes.

## Uso

Al iniciar el programa, se mostrará un menú principal:
--- Sistema de Reservas de Turnos ---

Reservar Turno
Cancelar Turno
Mostrar Turnos Disponibles
Mostrar Turnos Ocupados
Editar Turno
Ordenar Turnos por Fecha y Hora
Salir
Ingrese su opcion:


