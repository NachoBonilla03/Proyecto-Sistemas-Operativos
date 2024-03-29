#include<stdio.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/sysinfo.h>

int main(){
    /*File *fp = fopen("/proc/stat", "r"); 
    if(fp==null){
        perror("Error al acceder al  arcchivo de informacion del CPU"); 
        return EXIT_FAILURE; 
    }*/

    //Trying option 2 
    struct sysinfo infoCPU; 

    //Access to the system info and load it to the infoCPU variable
    if (sysinfo(&infoCPU) != 0) {
        perror("sysinfo failed");
        exit(EXIT_FAILURE);
    }

    // Calculating the  CPU usage 
    //CPU usage
    long total = info.loads[0] + info.loads[1] + info.loads[2] + info.loads[3];

    //CPU IDLE 
    long idle = info.loads[4];

    //Total usage - CPU  without usage / total time * 100 to get the percentage  of use
    double cpu_usage = ((double)total - (double)idle) / (double)total * 100.0;

    // Print CPU usage
    printf("CPU usage: %.2f%%\n", cpu_usage);

    return EXIT_SUCCESS;


    return 0; 
}