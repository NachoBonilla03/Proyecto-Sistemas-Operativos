#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DISKSTATS_FILE "/proc/diskstats"

double obtener_porcentaje_libre(const char *device);

int main() {
    const char *device = "sda";  // Puedes cambiar esto según el dispositivo que quieras verificar

    double porcentaje_libre = obtener_porcentaje_libre(device);

    if (porcentaje_libre >= 0) {
        printf("Porcentaje libre de disco para %s: %.2f%%\n", device, porcentaje_libre);
    }

    return 0;
}

double obtener_porcentaje_libre(const char *device) {
    FILE *diskStatsFile = fopen(DISKSTATS_FILE, "r");
    if (diskStatsFile == NULL) {
        perror("Error al abrir el archivo de estadísticas del disco");
        return -1;
    }

    char line[256];
    while (fgets(line, sizeof(line), diskStatsFile) != NULL) {
        char dev[32];
        unsigned long long reads, writes, sectorsRead, sectorsWritten;
        sscanf(line, "%*d %*d %s %llu %*d %llu %llu", dev, &reads, &sectorsRead, &sectorsWritten);
        if (strcmp(dev, device) == 0) {
            double totalSectors = sectorsRead + sectorsWritten;
            double freeSectors = totalSectors - sectorsWritten;  // Assuming all writes are to free space
            double porcentaje_libre = (freeSectors / totalSectors) * 100.0;
            fclose(diskStatsFile);
            return porcentaje_libre;
        }
    }

    fclose(diskStatsFile);
    return -1;
}
