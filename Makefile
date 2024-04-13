# Ignacio Bonilla Rojas
# Marcos Vásquez Díaz

# Nombre del programa
TARGET = monitor_recursos

# Compilador a utilizar
CC = gcc

# Opciones del compilador
CFLAGS = -Wall -Werror#-Wextra

# Archivos fuente
SOURCES = main.c cpu_stats.c mem_stats.c disk_stats.c 

# Archivos objeto generados
OBJECTS = $(SOURCES:.c=.o)

# Regla principal
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Regla para construir archivos objeto
#%.o: 
%.c:
	$(CC) $(CFLAGS) -c $<

# Regla para limpiar archivos generados
clean:
	rm -f $(OBJECTS) $(TARGET)
