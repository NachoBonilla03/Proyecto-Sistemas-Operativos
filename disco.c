#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Cantidad de argumentos invalida, recuerde que es ./disco <-U/-L>\n");
        return EXIT_FAILURE; 
    }

    if(strcmp(argv[1], "-U")==0){  // strcmp() Para comparar cadenas en C. La función strcmp() devuelve 0 cuando las dos cadenas son iguales.
        execlp("/bin/sh", "sh", "-c", "df -BM | awk 'BEGIN {print \"FileSystem|Size|Used|Use%\"} NR!=1 {print $1\"|\" $2 \"|\" $3 \"|\" $5}'", NULL);

    }

    if(strcmp(argv[1], "-L")==0){   // strcmp() Para comparar cadenas en C. La función strcmp() devuelve 0 cuando las dos cadenas son iguales.
        execlp("/bin/sh", "sh", "-c", "df -BM | awk 'BEGIN {print \"Filesystem|Size|Used|Available%\"} NR!=1 {print $1 \"|\" $2 \"|\" $3 \"|\" 100 - substr($5, 1, length($5)-1) \"%\"}'", NULL);
        // toma una subcadena del campo $5, comenzando desde el primer carácter (1) hasta el penúltimo (length($5)-1). 
        //Esto se hace para eliminar el signo de porcentaje al final del valor, y por último restamos 100 a ese resultado.

    }

    printf("Opción no válida, recuerde que debe ser '-U' o '-L'\n");
    return EXIT_FAILURE;

    return 0;
}