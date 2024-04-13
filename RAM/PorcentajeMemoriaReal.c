
#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *fp;
  char line[1024];
  char pid[10], cmd[1024];
  int* user, pid_num; 

  // Execute the ps command and get its output
  fp = popen("ps aux", "r");
  if (fp == NULL) {
    printf("Error: popen failed\n");
    return 1;
  }

  // Parse the output and extract the PID and command columns
  while (fgets(line, sizeof(line), fp) != NULL) {
    // Extract the PID column
    sscanf(line, "%s %s", pid, cmd);
    printf("%s ", pid);

    // Extract the command column
   	sscanf(line, "%s %s %s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %d", pid, user, cmd);
	printf("%s %s %d\n", pid, user, pid_num);
  }

  // Close the pipe
  pclose(fp);

  return 0;
}

