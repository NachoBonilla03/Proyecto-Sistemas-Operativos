#include<stdio.h>
#include<stdlib.h> 
#include<unistd.h> 

int main(){
    File *fp = fopen("/proc/stat", "r"); 
    if(fp==null){
        perror("Error al acceder al  arcchivo de informacion del CPU"); 
        return EXIT_FAILURE; 
    }

    return 0; 
}