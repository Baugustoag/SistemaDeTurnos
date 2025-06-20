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


## ⚙️ Compilación y Ejecución

### ✅ Requisitos

- Tener instalado un compilador de C:
  - En **Windows**: [TDM-GCC](https://jmeubank.github.io/tdm-gcc/) o [MinGW](http://www.mingw.org/)
  - En **Linux**: el compilador `gcc` (ya viene instalado en la mayoría de las distribuciones)

- Un editor de texto o IDE como [Code::Blocks](http://www.codeblocks.org/), [VS Code](https://code.visualstudio.com/) o simplemente Notepad++.

### 💻 Instrucciones para Compilar

#### 🔹 En Windows (usando terminal CMD o PowerShell):

1. Abrí la terminal en la carpeta donde está el archivo `.c`
2. Ejecutá:

## Uso

Al iniciar el programa, se mostrará un menú principal:
==== SISTEMA DE RESERVAS ====
1. Reservar turno
2. Listar turnos
3. Cancelar turno
4. Reagendar turno
0. Salir

