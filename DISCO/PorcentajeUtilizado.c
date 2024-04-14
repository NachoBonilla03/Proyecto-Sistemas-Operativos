#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DISKSTATS_FILE "/proc/diskstats"

//double obtener_porcentaje_ocupado(const char *device);

int main() {
    execlp("/bin/sh", "sh", "-c", "df -BM | awk 'BEGIN {print \"FileSystem|Size|Used|Use%\"} NR!=1 {print $1 \"|\" $2 \"|\" $3 \"|\" $5}'", NULL);


    return 0;
}




/*
int main() {
    const char *device = "sda";  // Puedes cambiar esto según el dispositivo que quieras verificar

    double porcentaje_ocupado = obtener_porcentaje_ocupado(device);

    if (porcentaje_ocupado >= 0) {
        printf("Porcentaje ocupado de disco para %s: %.2f%%\n", device, porcentaje_ocupado);
    }

    return 0;
}

double obtener_porcentaje_ocupado(const char *device) {
    FILE *pipe = popen("cat " DISKSTATS_FILE, "r");
    if (pipe == NULL) {
        perror("Error al abrir el pipe");
        return -1;
    }

    char line[256];
    while (fgets(line, sizeof(line), pipe) != NULL) {
        char dev[32];
        unsigned long long reads, writes, sectorsRead, sectorsWritten;
        sscanf(line, "%*d %*d %s %llu %*d %llu %llu", dev, &reads, &sectorsRead, &sectorsWritten);
        if (strcmp(dev, device) == 0) {
            double totalSectors = sectorsRead + sectorsWritten;
            double usedSectors = sectorsWritten;  // Cantidad de sectores escritos
            double porcentaje_ocupado = (usedSectors / totalSectors) * 100.0;
            pclose(pipe);
            return porcentaje_ocupado;
        }
    }

    pclose(pipe);
    return -1;
}
*/ 