# Ignacio Bonilla Rojas
# Marcos Vásquez Díaz

# Nombre del programa
TARGET = mmmm

# Compilador a utilizar
CC = gcc

# Opciones del compilador
# CFLAGS = -Wall -Werror

# Archivos fuente
SOURCES = prueba.c disco.c RAM.c cpu.c main.c

# Archivos objeto generados
OBJECTS = $(SOURCES:.c=)

# Regla principal  
all: $(TARGET)

# $(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
$(TARGET): $(OBJECTS)
	$(CC) $(TARGET) -o $(OBJECTS)

# Regla para construir archivos objeto $(CC) $(CFLAGS) -c $< -o $@
%.o: %.c
	$(CC) $< -o $@

# Regla para limpiar archivos generados
clean:
	rm -f $(OBJECTS) $(TARGET)

