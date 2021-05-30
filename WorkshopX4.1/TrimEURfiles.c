/***************************************
 *File: fd_copyfile.c
 ***************************************/

#include <stdio.h>
#include <stdlib.h>     // exit
#include <unistd.h>     // fork
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define BUF_SIZE  4096

int main( int argc, char *argv[]){
  int in_fd, out_fd, write_count, read_count;
  char my_buffer[BUF_SIZE];

  if (argc != 3) perror("!! wrong arguments");

  in_fd = open(argv[1], O_RDONLY); //open source file
  if ( in_fd < 0 ) perror("!! in_fd");

  out_fd = open(strcat(argv[1], ".usd"), O_CREAT|O_WRONLY, S_IRUSR | S_IWUSR); // create target file
  if ( out_fd < 0 ) perror("!! out_fd");

  while(1) { // Copying
    read_count = read(in_fd, my_buffer, BUF_SIZE); //read a data block
    if (read_count <=0) break;

    //change € to $ in the buffer read
    int i = 0;
    while(i<sizeof(my_buffer)){
        if((my_buffer[i] == 0xffffffe2) && (my_buffer[i+1] == 0xffffff82) && (my_buffer[i+2] == 0xffffffac)){
           my_buffer[i] = 36;
	   my_buffer[i+1] = 32;
           my_buffer[i+2] = 32;
	   i=i+2;
        }
	i++;
    }

    printf("my buffer: %s",my_buffer);
    //write changed buffer to new created file

    write_count = write(out_fd, my_buffer, read_count);
    printf("write count: %d\n", write_count);
    if (write_count <=0) perror("writing error");
  }

  close(in_fd);
  close(out_fd);
  if (read_count == 0) exit(0); // no error on last read
  else perror("!! last read");  // error on last read
}

