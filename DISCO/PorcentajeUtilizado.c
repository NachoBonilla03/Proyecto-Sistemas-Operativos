#include <stdio.h>
#include <sys/statvfs.h>

double obtener_porcentaje_utilizado(const char *path);

int main() {
    const char *path = "/";  // Puedes cambiar esto según la partición que quieras verificar

    double porcentaje_utilizado = obtener_porcentaje_utilizado(path);

    if (porcentaje_utilizado >= 0) {
        printf("Porcentaje utilizado de disco: %.2f%%\n", porcentaje_utilizado);
    }

    return 0;
}


double obtener_porcentaje_utilizado(const char *path) {
    struct statvfs stat;
    
    if (statvfs(path, &stat) != 0) {
        perror("Error al obtener el estado del sistema de archivos");
        return -1;
    }
    
    double porcentaje_utilizado = 100.0 - (((double)stat.f_bfree / (double)stat.f_blocks) * 100.0);
    
    return porcentaje_utilizado;
}
