/***************************************
 *File: read_file.c
 ***************************************/

#include <stdio.h>     
#include <stdlib.h>     // exit
#include <unistd.h>     // fork
#include <sys/wait.h>   
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char * argv[]){
  int fd, i;
  char message[4];

  fd = atoi(argv[1]);
  printf("fd child value, %d.\n", fd);

  i=0;
  while ( i < 5 ) {
    printf("%d", i);
    read(fd, message, 4);
    printf(" Parent process, reading : %s \n", message);
    i++;
  }
  close(fd);
  exit(0);
}
  
 
