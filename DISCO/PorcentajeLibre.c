#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DISKSTATS_FILE "/proc/diskstats"

void obtener_porcentaje_libre_todos();

int main() {
    obtener_porcentaje_libre_todos();

    return 0;
}

void obtener_porcentaje_libre_todos() {
    FILE *diskStatsFile = fopen(DISKSTATS_FILE, "r");
    if (diskStatsFile == NULL) {
        perror("Error al abrir el archivo de estadísticas del disco");
        return;
    }

    unsigned long long totalSectors = 0;
    unsigned long long freeSectors = 0;

    char line[256];
    while (fgets(line, sizeof(line), diskStatsFile) != NULL) {
        char dev[32];
        unsigned long long reads, writes, sectorsRead, sectorsWritten;
        sscanf(line, "%*d %*d %s %llu %*d %llu %llu", dev, &reads, &sectorsRead, &sectorsWritten);
        
        // Ignoramos las líneas que no corresponden a dispositivos de disco
        if (strstr(dev, "sd") != NULL || strstr(dev, "hd") != NULL || strstr(dev, "vd") != NULL) {
            totalSectors += sectorsRead + sectorsWritten;
            freeSectors += sectorsRead;  // Suponiendo que todas las lecturas provienen de espacio libre
        }
    }

    fclose(diskStatsFile);

    if (totalSectors == 0) {
        printf("No se encontraron dispositivos de disco en el sistema.\n");
        return;
    }

    double porcentaje_libre = ((double)freeSectors / (double)totalSectors) * 100.0;
    printf("Porcentaje libre de disco en general: %.2f%%\n", porcentaje_libre);
}

