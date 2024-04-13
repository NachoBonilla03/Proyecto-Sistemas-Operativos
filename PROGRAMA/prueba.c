#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LOOP 1000000000
#define DURATION_SECONDS 300

void busy_cpu() {
    int i;
    double result = 0.0;

    // Repetimos la carga de CPU durante un período más largo
    for (int j = 0; j < DURATION_SECONDS; ++j) {
        for (i = 0; i < MAX_LOOP; ++i) {
            result += (double)i;
        }
        // Esperamos un segundo antes de iniciar el próximo ciclo
        sleep(1);
    }
}

int main() {
    int pid;

    // Obtenemos el PID del proceso actual
    pid = getpid();

    // Imprimimos el PID del proceso
    printf("PID del proceso actual: %d\n", pid);

    // Ejecutamos una carga de CPU durante un tiempo determinado
    printf("Ejecutando carga de CPU durante %d segundos...\n", DURATION_SECONDS);
    busy_cpu();

    // Imprimimos un mensaje para indicar que hemos terminado de utilizar recursos
    printf("El proceso ha terminado de utilizar recursos.\n");

    return 0;
}
