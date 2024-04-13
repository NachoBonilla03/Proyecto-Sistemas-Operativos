#include <stdio.h>
#include <unistd.h>
#include <time.h>

void carga_cpu_baja(unsigned int segundos) {
    time_t start_time = time(NULL);

    while ((time(NULL) - start_time) < segundos) {
        // Realizar una tarea simple pero que requiera CPU
        int a = 1234, b = 5678;
        int resultado = a * b;
        // Intencionalmente no hacer nada con el resultado para evitar que el compilador lo optimice
        (void)resultado;
    }
}

int main() {
    printf("El PID del programa es: %d\n", getpid());
    printf("El programa utilizará la CPU durante 5 minutos con baja carga.\n");
    carga_cpu_baja(5 * 60); // 5 minutos en segundos
    printf("El programa ha completado la carga de CPU.\n");

    return 0;
}
