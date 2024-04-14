#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
   FILE *fp;
  char line[1024];
  int pid;


if (argc> 3 || argc<2) {
        printf("Cantidad de argumentos invalida, la forma de uso es ./main -R <-MR/-MV> <pid>\n");
} 
 
if(strcmp(argv[1], "-MR")==0){
	
	  double mem;
	  // Execute the ps aux command and get its output 
	  fp = popen("ps aux --sort -%mem", "r");
	  if (fp == NULL) {
	    printf("Error: popen failed\n");
	    return 1;
	  }
	  
	  if(argc==2){
	  // Parse the output and extract the PID and %MEM columns
	  while (fgets(line, sizeof(line), fp) != NULL) {
	    if (sscanf(line, "%*s %d %*s %lf", &pid, &mem) == 2) {
	      printf("PID: %d, RAM Real: %.2f%%\n", pid, mem);
	    }
	  }
	  // Close the pipe
	  pclose(fp); 
	} 
	 
	if(argc==3){
	int arg_pid = atoi(argv[2]); 
	  // Parse the output and extract the PID and %MEM columns
	  while (fgets(line, sizeof(line), fp) != NULL) {
	    if (sscanf(line, "%*s %d %*s %lf", &pid, &mem) == 2) {
	    if(arg_pid ==pid){
	      printf("PID: %d, RAM Real: %.2f%%\n", pid, mem);
	      }
	    }
	  }
	  // Close the pipe
	  pclose(fp);
	}  
}

if(strcmp(argv[1], "-MV")==0){
  int mem;
  int memtot = 0;
  // Execute the ps aux command and get its output
  fp = popen("ps -e -o pid,vsize --sort -vsize", "r");
  if (fp == NULL) {
    printf("Error: popen failed\n");
    return 1;
  }
  // Parse the output and extract the PID and VSZ columns
  while (fgets(line, sizeof(line), fp) != NULL) {
    if (sscanf(line, "%*d %d", &mem) == 1) {
      memtot += mem;  // sumar el valor de mem a memtot
    }
  }
  printf("RAM virtual total: %d kilobytes\n", memtot);
  // Reset the file pointer to the beginning of the output
  pclose(fp);
  
  fp = popen("ps -e -o pid,vsize --sort -vsize", "r");
  if (fp == NULL) {
    printf("Error: popen failed\n");
    return 1;
  }
  
  if(argc==2){
  // Parse the output and extract the PID and VSZ columns
  while (fgets(line, sizeof(line), fp) != NULL) {
    if (sscanf(line, "%d %d", &pid, &mem) == 2) {
      double memaux = (mem * 100.0) / memtot;  // calcular el porcentaje de memoria virtual utilizado por cada proceso
      printf("PID: %d, RAM virtual: %.2f%%\n", pid, memaux);
    }
  }
  // Close the pipe
  pclose(fp);
  }
  
  if(argc==3){
  int arg_pid = atoi(argv[2]); 
  while (fgets(line, sizeof(line), fp) != NULL) {
    if (sscanf(line, "%d %d", &pid, &mem) == 2) {
    	if(pid==arg_pid){
      double memaux = (mem * 100.0) / memtot;  // calcular el porcentaje de memoria virtual utilizado por cada proceso
      printf("PID: %d, RAM virtual: %.2f%%\n", pid, memaux);
      }
    }
  }
  }

}
}