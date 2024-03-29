#include<stdio.h>
#include<stdlib.h> 
#include<unistd.h> 


int main(){
    //This file  have the information of the CPU statistics 
    struct _IO_FILE *fileCPU = fopen("/proc/stat", "r");
    long totalUser, totalSys, totalIDLE, total;   
    if(fileCPU==NULL){
        perror("Error al acceder al  arcchivo de informacion del CPU"); 
        return EXIT_FAILURE; 
    }

    //Reading the first line in the /proc/start and keep the information in the variables 
    fscanf(fileCPU, "cpu %ld %ld %ld %ld", &totalUser, &totalSys, &totalIDLE, &total); 

    flose(fileCPU); 

//Calculating the usage percentage of the CPU
    float CPUPercentage = (float) (totalUser+totalSys)/(float)total; 
    CPUPercentage *= 100; 

    
    // Print CPU usage
    printf("CPU usage: %.2f%%\n", CPUPercentage);

    return 0; 
}