/***************************************
 *File: fd_father.c
 ***************************************/

#include <stdio.h>     
#include <stdlib.h>     // exit
#include <unistd.h>     // fork
#include <sys/wait.h>   
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
  int pid, fd, j;
  char message[4], long_msg[24];

  fd = open("StExupery.txt", O_RDONLY);
  if ( fd == -1 ) {
    perror("!Error open:");
    exit(1);
  }
  printf("fd value at opening , %d.\n", fd);

  pid = fork();
  if (pid == 0) { // child code
    sprintf(long_msg, "%d", fd);
    execlp("/home/ivan/read-file","read-file", long_msg, NULL);
    perror("!error exec"); 
  }
  else {
    for (j = 0 ; j < 5; j++){
      read(fd, message, 4);
      printf(" Parent process, reading : %s \n", message);
    }
    wait(NULL);
    close(fd);
  }
}
