#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pid = getpid(); // Obtener el PID del proceso actual

    printf("PID del proceso actual: %d\n", pid);

    // Ejecutar un bucle ligero durante 5 minutos
    for (int i = 0; i < 300; ++i) { // 300 segundos = 5 minutos
        // Realizar alguna operación ligera para simular carga baja en la CPU
        // Por ejemplo, dormir durante un breve período de tiempo
        usleep(1000000); // Dormir durante 10 milisegundos (0.01 segundos)

        // Imprimir un mensaje cada minuto
        if ((i + 1) % 60 == 0) {
            printf("Minuto %d: Proceso en ejecución...\n", (i + 1) / 60);
        }
    }

    printf("Proceso finalizado.\n");

    return 0;
}
