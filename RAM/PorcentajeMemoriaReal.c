
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
  double mem;

  // Execute the ps aux command and get its output
  fp = popen("ps aux --sort -%mem", "r");
  if (fp == NULL) {
    printf("Error: popen failed\n");
    return 1;
  }

  // Parse the output and extract the PID and %MEM columns
  while (fgets(line, sizeof(line), fp) != NULL) {
    if (sscanf(line, "%*s %d %*s %lf", &pid, &mem) == 2) {
      printf("PID: %d, MEM: %.2f%%\n", pid, mem);
    }
  }

  // Close the pipe
  pclose(fp);

  return 0;
}