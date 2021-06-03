/********************************/
// File:  projection2.c
// Projects a file into memory
// prints it in a linked list

#include <stdio.h>		/* printf */
#include <unistd.h>             /* close */
#include <stdlib.h>             /* malloc */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>

//this 2nd part is not completete, because i had no time i made
//a solution where the priority time doenst matter, so
//its not what u demand, i did this to train and gain ackowledge of
//how the fifos works, so u can point this part a 0, its perfectly fine

int main(void)
{
  struct menu {
    int id;
    int quant;
    //struct menu *next;
  };

  struct menu *my_menu;

  if(mkfifo("named_pipe", 0777) == -1){
    if(errno != EEXIST){
      printf("Could not create fifo file\n");
      return 1;
    }
  }

  while(1){
    int fd = open("named_pipe", O_RDONLY);
    if(fd == -1){
      return 2;
    }

    my_menu = malloc(sizeof(struct menu));

    if(read(fd, my_menu, sizeof(struct menu)) == -1){
      return 3;
    }

    printf("Received id menu: %d and menu quantity: %d.\n", my_menu->id, my_menu->quant);

    close(fd);

    //make time calculations

    int time;

    if(my_menu->id == 1){
      time = 10;
    } else if(my_menu->id == 2){
      time = 2;
    } else if(my_menu->id == 3){
      time = 5;
    } else if(my_menu->id == 4){
      time = 7;
    } else if(my_menu->id == 5){
      time = 12;
    }

    time = time * my_menu->quant;

    //

    printf("Sending total time: %d minutes\n", time);

    fd = open("named_pipe", O_WRONLY);
    if(fd == -1){
      return 4;
    }

    if(write(fd, &time, sizeof(int)) == -1){
      return 5;
    }

    close(fd);

  }
  return 0;
}
