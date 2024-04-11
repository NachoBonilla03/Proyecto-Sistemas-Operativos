
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    // This file has the information of the total available memory
    struct _IO_FILE *fileMemInfo = fopen("/proc/meminfo", "r");
    unsigned long totalMem;
    if (fileMemInfo == NULL) {
        perror("Error al acceder al archivo de informacion de la memoria");
        return EXIT_FAILURE;
    }

    // Read the total available memory
    fscanf(fileMemInfo, "MemTotal: %lu kB\n", &totalMem);
    fclose(fileMemInfo);

    // Open the /proc folder
    DIR *procDir = opendir("/proc");
    if (procDir == NULL) {
        perror("Error al abrir el directorio /proc");
        return EXIT_FAILURE;
    }

    // Iterate through all the processes
    struct dirent *entry;
    while ((entry = readdir(procDir)) != NULL) {
        // Skip non-process entries
        if (entry->d_type != DT_DIR || strchr("0123456789", entry->d_name[0]) == NULL) {
            continue;
        }

        // Read the process status
        char path[256];
        snprintf(path, sizeof(path), "/proc/%s/status", entry->d_name);
        struct _IO_FILE *fileStatus = fopen(path, "r");
        if (fileStatus == NULL) {
            perror("Error al acceder al archivo de informacion del proceso");
            continue;
        }

        unsigned long vsize;
        unsigned long rss;
        char state;
        fscanf(fileStatus, "VmSize: %lu kB\nRss: %lu kB\nState: %c", &vsize, &rss, &state);
        fclose(fileStatus);

        // Calculate the process real RAM usage
        double processRAM = (double)rss / (double)totalMem * 100;

        // Print the process PID and RAM usage
        printf("PID: %s, RAM Usage: %.2f%%\n", entry->d_name, processRAM);
    }

    closedir(procDir);
    return 0;
}