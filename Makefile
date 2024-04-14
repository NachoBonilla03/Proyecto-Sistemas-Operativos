# Ignacio Bonilla Rojas
# Marcos Vásquez Díaz

# Nombre del programa
TARGET = monitor_recursos

# Compilador a utilizar
CC = gcc

# Opciones del compilador
# CFLAGS = -Wall -Werror

# Archivos fuente
SOURCES = programa.c disco.c PorcentajeEnUso.c PorcentajeMemoriaReal.c PorcentajeMemoriaVirtual.c

# Archivos objeto generados
OBJECTS = $(SOURCES:.c=.o)

# Regla principal  
all: $(TARGET)

# $(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
$(TARGET): $(OBJECTS)
	$(CC) $(TARGET) $(OBJECTS)

# Regla para construir archivos objeto $(CC) $(CFLAGS) -c $< -o $@
%.o: %.c
	$(CC) $< -o $@

# Regla para limpiar archivos generados
clean:
	rm -f $(OBJECTS) $(TARGET)
