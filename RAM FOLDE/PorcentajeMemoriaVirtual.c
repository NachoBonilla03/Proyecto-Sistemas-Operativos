/*
comando ps aux 
%MEM: El porcentaje de memoria física que el proceso está utilizando.
Las columnas que retorna el comando ps aux en un sistema operativo Linux contienen información detallada sobre cada proceso en ejecución. A continuación, se describe el significado de cada columna:

USER: El usuario propietario del proceso.

PID: El identificador único del proceso (Process ID).

%CPU: El porcentaje de tiempo de CPU que el proceso ha estado utilizando desde su inicio.

%MEM: El porcentaje de memoria física que el proceso está utilizando.

VSZ: El tamaño de la memoria virtual del proceso, medida en kilobytes (KiB). Esta columna muestra la cantidad total de memoria virtual que el proceso ha asignado, incluyendo tanto la memoria residente como la memoria swapeada.

RSS: El tamaño de la memoria residente del proceso, medida en kilobytes (KiB). Esta columna muestra la cantidad de memoria física que el proceso está utilizando actualmente.
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *fp;
  char line[1024];
  int pid;
  int mem;
  int memtot = 0;

  // Execute the ps aux command and get its output
  fp = popen("ps -e -o pid,vsize --sort -vsize", "r");
  if (fp == NULL) {
    printf("Error: popen failed\n");
    return 1;
  }

  // Parse the output and extract the PID and VSZ columns
  while (fgets(line, sizeof(line), fp) != NULL) {
    if (sscanf(line, "%*d %d", &mem) == 1) {
      memtot += mem;  // sumar el valor de mem a memtot
    }
  }

  printf("Total VSZ: %d\n", memtot);

  // Reset the file pointer to the beginning of the output
  pclose(fp);
  fp = popen("ps -e -o pid,vsize --sort -vsize", "r");
  if (fp == NULL) {
    printf("Error: popen failed\n");
    return 1;
  }
  // Parse the output and extract the PID and VSZ columns
  while (fgets(line, sizeof(line), fp) != NULL) {
    if (sscanf(line, "%d %d", &pid, &mem) == 2) {
      double memaux = (mem * 100.0) / memtot;  // calcular el porcentaje de memoria virtual utilizado por cada proceso
      printf("PID: %d, MEM virtual: %.2f%%\n", pid, memaux);
    }
    else
    printf("Error en proceso\n");
  }

  // Close the pipe
  pclose(fp);

  return 0;
}