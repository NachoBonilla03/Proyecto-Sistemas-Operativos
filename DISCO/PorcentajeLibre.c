#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <strings.h>

#define DISKSTATS_FILE "/proc/diskstats"

void obtener_porcentaje_libre_todos();

#include <unistd.h>

int main() {

    execlp("/bin/sh", "sh", "-c", "df -BM | awk 'BEGIN {print \"Filesystem|Size|Used|Available%\"} NR!=1 {print $1 \"|\" $2 \"|\" $3 \"|\" 100 - substr($5, 1, length($5)-1) \"%\"}'", NULL);
    // toma una subcadena del campo $5, comenzando desde el primer carácter (1) hasta el penúltimo (length($5)-1). 
    //Esto se hace para eliminar el signo de porcentaje al final del valor, y por último restamos 100 a ese resultado.
    return 0;
}


//void obtener_porcentaje_libre_todos() {
  //  FILE *diskStatsFile = fopen(DISKSTATS_FILE, "r");
    //if (diskStatsFile == NULL) {
      //  perror("Error al abrir el archivo de estadísticas del disco");
        //return;
    //}

    //unsigned long long totalSectors = 0;
    //unsigned long long freeSectors = 0;

  //  char line[256];
   // while (fgets(line, sizeof(line), diskStatsFile) != NULL) {
    //    char dev[32];
      //  unsigned long long reads, writes, sectorsRead, sectorsWritten;
       // sscanf(line, "%*d %*d %s %llu %*d %llu %llu", dev, &reads, &sectorsRead, &sectorsWritten);
       //
        // Ignoramos las líneas que no corresponden a dispositivos de disco
        //if (strstr(dev, "sd") != NULL || strstr(dev, "hd") != NULL || strstr(dev, "vd") != NULL) {
          //  totalSectors += sectorsRead + sectorsWritten;
        //    freeSectors += sectorsRead;  // Suponiendo que todas las lecturas provienen de espacio libre
       // }
   // }

    ///fclose(diskStatsFile);

   //if (totalSectors == 0) {
        //printf("No se encontraron dispositivos de disco en el sistema.\n");
       // return;
   // }

    //double porcentaje_libre = ((double)freeSectors / (double)totalSectors) * 100.0;
    ///printf("Porcentaje libre de disco en general: %.2f%%\n", porcentaje_libre);
//}

