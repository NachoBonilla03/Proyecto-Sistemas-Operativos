#include <stdio.h>
#include <sys/statvfs.h>

double obtener_porcentaje_libre(const char *path);

int main() {
    const char *path = "/";  // Puedes cambiar esto según la partición que quieras verificar

    double porcentaje_libre = obtener_porcentaje_libre(path);

    if (porcentaje_libre >= 0) {
        printf("Porcentaje libre de disco: %.2f%%\n", porcentaje_libre);
    }

    return 0;
}

double obtener_porcentaje_libre(const char *path) {
    struct statvfs stat;
    
    if (statvfs(path, &stat) != 0) {
        perror("Error al obtener el estado del sistema de archivos");
        return -1;
    }
    
    double porcentaje_libre = ((double)stat.f_bfree / (double)stat.f_blocks) * 100.0;
    
    return porcentaje_libre;
}