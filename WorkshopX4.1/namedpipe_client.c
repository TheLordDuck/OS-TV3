#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <sys/mman.h>

int main(int argc, char* argv[]){
   struct menu {
     int id;
     int quant;
   };

   struct menu *my_menu;

   my_menu = malloc(sizeof(struct menu));

   my_menu->id = atoi(argv[1]);
   my_menu->quant = atoi(argv[2]);

   int fd = open("named_pipe", O_WRONLY);
   if(fd == -1){
      return 1;
   }

   if(write(fd, my_menu, sizeof(struct menu)) == -1){
      return 2;
   }

   close(fd);

   int time;

   fd = open("named_pipe", O_RDONLY);
   if(fd == -1){
     return 3;
   }

   if(read(fd, &time, sizeof(int)) == -1){
     return 4;
   }

   printf("Time to make the delivery %d minutes\n", time);

   return 0;
}
