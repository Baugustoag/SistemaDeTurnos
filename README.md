# Sistema de Reserva de Turnos para Cancha de Fútbol ⚽

## 📌 Descripción del Proyecto

Este proyecto consiste en un programa en lenguaje **C** que permite gestionar reservas de turnos para una cancha de fútbol. Está pensado para ser utilizado por encargados de canchas que necesiten llevar un registro de las reservas de manera digital, sencilla y liviana.

Las funcionalidades principales son:

- Reservar un turno indicando día y hora.
- Listar turnos disponibles y ocupados.
- Cancelar una reserva.
- Guardar y cargar automáticamente las reservas en un archivo para no perder la información entre ejecuciones.
- Uso de **estructuras** y **listas dinámicas** para administrar los turnos en memoria.

El código es totalmente funcional tanto en **Windows** como en **Linux** y puede compilarse fácilmente desde la terminal.

---

## 👥 Integrantes y Roles

| Nombre               | Rol                            |
|----------------------|---------------------------------|
| Aguirre, Augusto      | Programador principal |
| Soto, Diogo           | Programador principal |
| Pintos, Leandro       |  Programador principal |

Para compilar y ejecutar:

🔹 En Linux

Tener GCC instalado:
sudo apt update

sudo apt install build-essential

Desde la terminal, moverse a la carpeta:

cd ~/Ruta/Del/Proyecto

Compilar:

gcc -o sistema_reservas sistema_reservas.c

Ejecucion:

./sistema_reservas

🔹 En Windows

Ejecuccion:
sistema_reservas.exe

## Uso

Al iniciar el programa, se mostrará un menú principal:

==== SISTEMA DE RESERVAS ====

1. Reservar turno
2. Listar turnos
3. Cancelar turno
4. Reagendar turno
0. Salir

Al elegir la opcion 1, apareceran los campos para hacer la reserva, definiendo lo siguiente: Dia, mes, hora, cancha y nombre de quien realiza la reserva.
La opcion 2 nos muestra la lista de turnos que hay, tanto libres como ocupados, para poder tener una mejor visualizacion de la disponibilidad de horarios y cancha.
Para cancelar el turno, seleccionamos la opcion 3, donde nos tenemos que responder con el nombre y cancha. Consideramos tambien la opcion para no cancelar, sino reagendar el turno, es decir modificar el dia y la hora.
