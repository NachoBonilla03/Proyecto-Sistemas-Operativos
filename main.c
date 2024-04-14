#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int pipefd[2];
  char buffer[9000];
  int bytesLeidos;
  pipe(pipefd);
  pid_t pid = fork();
  
  if(strcmp(argv[1], "-R")==0){
	  if (pid == 0) {
	    // Proceso hijo
	    close(pipefd[0]); // Cerrar extremo de lectura
	    execl("./RAM","RAM",  argv[2],argv[3]);
	    exit(1);
	   } 
	  else {
	    close(pipefd[1]); // Cerrar extremo de escritura
	    while ((bytesLeidos = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
	      write(1, buffer, bytesLeidos); // Imprimir la salida en la consola
	    }
	    close(pipefd[0]); // Cerrar extremo de lectura
	    wait(NULL);
	  }
   }	

   if(strcmp(argv[1], "-C")==0){
	  if (pid == 0) {
	    // Proceso hijo
	    close(pipefd[0]); // Cerrar extremo de lectura
	    execl("./cpu","cpu",  argv[2], argv[3]);
	    exit(1);
	   } 
	  else {
	    close(pipefd[1]); // Cerrar extremo de escritura
	    while ((bytesLeidos = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
	      write(1, buffer, bytesLeidos); // Imprimir la salida en la consola
	    }
	    close(pipefd[0]); // Cerrar extremo de lectura
	    wait(NULL);
	  }
   }
   
    if(strcmp(argv[1], "-D")==0){
	  if (pid == 0) {
	    // Proceso hijo
	    close(pipefd[0]); // Cerrar extremo de lectura
	    execl("./disco","disco",  argv[2],argv[3]);
	    exit(1);
	   } 
	  else {
	    close(pipefd[1]); // Cerrar extremo de escritura
	    while ((bytesLeidos = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
	      write(1, buffer, bytesLeidos); // Imprimir la salida en la consola
	    }
	    close(pipefd[0]); // Cerrar extremo de lectura
	    wait(NULL);
	  }
   }

  return 0;
}