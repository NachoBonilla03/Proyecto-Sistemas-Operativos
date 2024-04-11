
lude <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char buf[4096];
    ssize_t n;
    long size;
    long total_mem;

    // Open /proc/meminfo
    fd = open("/proc/meminfo", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Read the contents of /proc/meminfo
    n = read(fd, buf, sizeof(buf));
    if (n == -1) {
        perror("read");
        exit(1);
    }

    close(fd);

    // Parse the MemTotal line
    if (sscanf(buf, "MemTotal: %ld kB", &total_mem)!= 1) {
        fprintf(stderr, "Invalid format\n");
        exit(1);
    }

    // Print the size of the RAM
    printf("Size of the RAM: %ld KB\n", total_mem);

    for (int i = 1; i < 65536; i++) {
        snprintf(buf, sizeof(buf), "/proc/%d/statm", i);
        fd = open(buf, O_RDONLY);
        if (fd == -1) {
            continue;
        }

        n = read(fd, buf, sizeof(buf));
        if (n == -1) {
            perror("read");
            exit(1);
        }

        close(fd);

        if (sscanf(buf, "%ld ", &size)!= 1) {
            fprintf(stderr, "Invalid format\n");
            exit(1);
        }

        // Calculate the memory usage in KB
        long mem_usage_kb = size * 4;

        // Calculate the percentage of memory usage
        double mem_usage_percent = (mem_usage_kb * 100.0) / total_mem;

        printf("Memory usage of process %d: %ld pages, which is %ld KB, which is %.2f%% of the total memory\n", i, size, mem_usage_kb, mem_usage_percent);
    }

    return 0;
}