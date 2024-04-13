#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 256 
// se espera que esta longitud sea suficiente para manejar la mayoría 
// de las líneas de texto que se encuentran en estos archivos sin problemas de rendimiento o consumo excesivo de memoria.

void obtener_stat(int pid, unsigned long *utime, unsigned long *stime) {
    FILE *archivo;
    char ruta[MAX_LINE_LENGTH];
    char linea[MAX_LINE_LENGTH];
    unsigned long u, s;

    // Construir la ruta al archivo stat
    sprintf(ruta, "/proc/%d/stat", pid);
    //Utilizamos /stat porque contiene estadísticas del proceso, como el ID de proceso, estado, tiempo de CPU, entre otros.
    //sprintf Toma una cadena de destino como primer argumento, seguida de una cadena de formato y cero o más argumentos adicionales que se insertan en la cadena de formato, 
    //el resultado formateado se guarda en la cadena de destino.
    // Entonces "ruta" será algo como "/proc/<pid>/stat"

    // Abrir el archivo
    archivo = fopen(ruta, "r");  // acá se verá la utilidad del sprintf
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    // Leer la primera línea del archivo
    if (fgets(linea, MAX_LINE_LENGTH, archivo) == NULL) {
        perror("Error al leer el archivo");
        exit(EXIT_FAILURE);
    }

    // Cerrar el archivo
    fclose(archivo);

    // Analizar la línea para extraer los tiempos de CPU
    sscanf(linea, "%*d %*s %*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %lu %lu", &u, &s);

    // Asignar los tiempos de CPU a las variables correspondientes
    *utime = u;
    *stime = s;
}

int main() {
    int pid;
    unsigned long utime_start, stime_start, utime_end, stime_end;
    float cpu_percent;

    // Solicitar al usuario que ingrese el PID del proceso deseado
    printf("Ingrese el PID del proceso deseado: ");
    scanf("%d", &pid);

    // Inicializar variables para el promedio
    float total_cpu_percent = 0.0;

    // Realizar mediciones durante 5 minutos
    for (int i = 0; i < 5; ++i) {
        // Obtener los tiempos de CPU al inicio del intervalo de tiempo
        obtener_stat(pid, &utime_start, &stime_start);

        // Esperar 1 minuto
        sleep(60);

        // Obtener los tiempos de CPU al final del intervalo de tiempo
        obtener_stat(pid, &utime_end, &stime_end);

        // Calcular el tiempo total de CPU utilizado durante el intervalo de tiempo
        unsigned long total_time = utime_end + stime_end - utime_start - stime_start;

        // Calcular el tiempo transcurrido durante el intervalo de tiempo
        unsigned long elapsed_time = 60 * sysconf(_SC_CLK_TCK); // 60 segundos * unidades de tiempo del kernel
                                                                // sysconf(_SC_CLK_TCK): Esta función proporciona el número de unidades de tiempo del kernel por segundo. 
                                                                //En sistemas basados en Linux, _SC_CLK_TCK es una constante que se utiliza para obtener esta información.
                                                                //Representa la cantidad de unidades de tiempo del kernel en un segundo, es decir, la velocidad del reloj del kernel.
                                                                //Multiplicar esta velocidad del reloj del kernel por 60 da como resultado el número de unidades de tiempo del kernel en un minuto. 
                                                                //Entonces, elapsed_time almacena el tiempo total durante el cual se está midiendo el uso de la CPU en el intervalo de un minuto,
                                                                //en unidades de tiempo del kernel. 

        // Calcular el porcentaje de utilización de CPU durante el intervalo de tiempo
        cpu_percent = ((float)total_time / elapsed_time) * 100;  //Dividir total_time por elapsed_time da como resultado la fracción del tiempo del kernel que el proceso ha utilizado la CPU durante el intervalo de tiempo. 
                                                                 //Multiplicar esta fracción por 100 convierte la fracción en un porcentaje, lo que nos da el porcentaje de utilización de CPU durante ese intervalo de tiempo.

        // Acumular el porcentaje de utilización de CPU para calcular el promedio
        total_cpu_percent += cpu_percent;

        // Imprimir el porcentaje de utilización de CPU durante el intervalo de tiempo actual
        printf("Porcentaje de utilización de CPU en el minuto %d: %.2f%%\n", i+1, cpu_percent);
    }

    // Calcular el promedio del porcentaje de utilización de CPU durante los 5 minutos
    float promedio_cpu_percent = total_cpu_percent / 5.0;

    // Imprimir el promedio del porcentaje de utilización de CPU
    printf("Promedio de utilización de CPU en los últimos 5 minutos: %.2f%%\n", promedio_cpu_percent);

    return 0;
}




/*
opcion 2


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 256

void obtener_stat(int pid, unsigned long *utime, unsigned long *stime) {
    FILE *archivo;
    char ruta[MAX_LINE_LENGTH];
    char linea[MAX_LINE_LENGTH];
    unsigned long u, s;

    // Construir la ruta al archivo stat
    sprintf(ruta, "/proc/%d/stat", pid);

    // Abrir el archivo
    archivo = fopen(ruta, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    // Leer la primera línea del archivo
    if (fgets(linea, MAX_LINE_LENGTH, archivo) == NULL) {
        perror("Error al leer el archivo");
        exit(EXIT_FAILURE);
    }

    // Cerrar el archivo
    fclose(archivo);

    // Analizar la línea para extraer los tiempos de CPU
    sscanf(linea, "%*d %*s %*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %lu %lu", &u, &s);

    // Asignar los tiempos de CPU a las variables correspondientes
    *utime = u;
    *stime = s;
}

int main() {
    int pid;
    unsigned long utime_start, stime_start, utime_end, stime_end;
    float cpu_percent;

    // Solicitar al usuario que ingrese el PID del proceso deseado
    printf("Ingrese el PID del proceso deseado: ");
    scanf("%d", &pid);

    // Obtener los tiempos de CPU al inicio del intervalo de tiempo
    obtener_stat(pid, &utime_start, &stime_start);

    // Esperar 5 minutos
    sleep(300);

    // Obtener los tiempos de CPU al final del intervalo de tiempo
    obtener_stat(pid, &utime_end, &stime_end);

    // Calcular el tiempo total de CPU utilizado durante el intervalo de tiempo
    unsigned long total_time = utime_end + stime_end - utime_start - stime_start;

    // Calcular el tiempo transcurrido durante el intervalo de tiempo
    unsigned long elapsed_time = 300 * sysconf(_SC_CLK_TCK); // 300 segundos * unidades de tiempo del kernel

    // Calcular el porcentaje de utilización de CPU durante el intervalo de tiempo
    cpu_percent = ((float)total_time / elapsed_time) * 100;

    // Imprimir el PID, nombre del proceso y porcentaje de utilización de CPU
    printf("PID: %d\n", pid);
    printf("Porcentaje de utilización de CPU en los últimos 5 minutos: %.2f%%\n", cpu_percent);

    return 0;
}

/*

/*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_PATH_LENGTH 256
#define MAX_LINE_LENGTH 256


void obtener_status(int pid) {
    FILE *archivo;
    char ruta[MAX_PATH_LENGTH];
    char linea[MAX_LINE_LENGTH];

    // Construir la ruta al archivo status
    sprintf(ruta, "/proc/%d/status", pid);

    // Abrir el archivo
    archivo = fopen(ruta, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    // Leer y mostrar el contenido del archivo línea por línea
    printf("Contenido del archivo %s:\n", ruta);
    while (fgets(linea, MAX_LINE_LENGTH, archivo) != NULL) {
        printf("%s", linea);
    }

    // Cerrar el archivo
    fclose(archivo);
}

int main() {
    int pid;

    // Solicitar al usuario que ingrese el PID
    printf("Ingrese el PID del proceso deseado: ");
    scanf("%d", &pid);

    // Llamar a la función para obtener y mostrar el contenido de /proc/<pid>/status
    obtener_status(pid);

    return 0;
}

*/

//int main(int argc, char *argv[]) {
    // Verificamos que se haya pasado un argumento
  //  if (argc != 2) {
    //    printf("Uso: %s <PID>\n", argv[0]);
      //  return 1;
    //}

    // Convertimos el argumento (el PID) a un entero
    //int pid = atoi(argv[1]);

    // Imprimimos el mensaje solicitando el PID
    //printf("Ingrese el PID del proceso deseado: ");
    
    // Leemos el PID ingresado por el usuario
    // Suponemos que el usuario ingresa solo números
    //int pid_ingresado;
    //scanf("%d", &pid_ingresado);

    // Imprimimos el PID ingresado
    //printf("El PID ingresado es: %d\n", pid_ingresado);

    //return 0;
//}
