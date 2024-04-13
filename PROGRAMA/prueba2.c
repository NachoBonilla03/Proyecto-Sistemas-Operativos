#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h> // Necesario para utilizar time_t

#define DURATION_SECONDS 180 // Duración mínima en segundos (3 minutos)
#define MAX_LOOP 100000000   // Número máximo de iteraciones para un uso menos intensivo de la CPU

void less_busy_cpu() {
    int i;
    double result = 0.0;

    // Repetir un cálculo sencillo para utilizar CPU, pero menos intensivo
    for (i = 0; i < MAX_LOOP; ++i) {
        result += (double)i / 2.0;
    }
}

int main() {
    int pid;
    time_t start_time, current_time;

    // Obtener el PID del proceso actual
    pid = getpid();

    // Imprimir el PID del proceso
    printf("PID del proceso actual: %d\n", pid);

    // Obtener el tiempo de inicio
    time(&start_time);

    // Ejecutar una carga de CPU menos intensiva durante al menos 3 minutos
    printf("Ejecutando carga de CPU menos intensiva durante al menos 3 minutos...\n");
    do {
        less_busy_cpu(); // Utilizar CPU de manera menos intensiva
        time(&current_time);
    } while (current_time - start_time < DURATION_SECONDS);

    // Imprimir un mensaje para indicar que hemos terminado de utilizar recursos
    printf("El proceso ha terminado de utilizar recursos durante al menos 3 minutos.\n");

    return 0;
}



/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void less_busy_cpu() {
    int i;
    double result = 0.0;

    // Repetir un cálculo sencillo para utilizar CPU, pero menos intensivo
    for (i = 0; i < 10000000; ++i) {
        result += (double)i / 2.0;
    }
}

#define DURATION_SECONDS 180 // Duración mínima en segundos (3 minutos)

int main() {
    int pid;

    // Obtener el PID del proceso actual
    pid = getpid();

    // Imprimir el PID del proceso
    printf("PID del proceso actual: %d\n", pid);

    // Esperar al menos 3 minutos
    printf("Esperando al menos 3 minutos...\n");
    sleep(DURATION_SECONDS);

    // Imprimir un mensaje para indicar que hemos terminado de esperar
    printf("El proceso ha esperado al menos 3 minutos.\n");

    return 0;
}

*/