# Define el compilador C
CC = gcc

# Define las banderas de compilacion
# -Iinclude: Incluye la carpeta 'include' para buscar archivos .h
# -Wall: Habilita todas las advertencias (buenas practicas)
# -Wextra: Habilita advertencias adicionales
# -std=c11: Usa el estandar C11
# -g: Incluye informacion de depuracion (para usar con depuradores como GDB)
CFLAGS = -Iinclude -Wall -Wextra -std=c11 -g

# Define el nombre del ejecutable
TARGET = sistema_reservas

# Define las carpetas de codigo fuente y de cabeceras
SRC_DIR = src
INCLUDE_DIR = include

# Lista todos los archivos .c en la carpeta src
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Genera los nombres de los archivos objeto (.o) correspondientes
# Por ejemplo, src/main.c se convierte en obj/main.o
OBJS = $(patsubst $(SRC_DIR)/%.c, obj/%.o, $(SRCS))

# Define la carpeta donde se guardaran los archivos objeto
OBJ_DIR = obj

.PHONY: all clean run

all: $(OBJ_DIR) $(TARGET)

# Regla para crear la carpeta de objetos si no existe
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Regla principal para enlazar el ejecutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@
# Regla para compilar cada archivo .c en .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar los archivos generados
clean:
	@rm -rf $(OBJ_DIR) $(TARGET) turnos.dat
	@echo "Archivos generados y turnos.dat eliminados."

# Regla para ejecutar el programa despues de compilar
run: all
	./$(TARGET)