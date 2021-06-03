#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
   int arr[5];

   if(mkfifo("named_pipe", 0777) == -1){
      if(errno != EEXIST){
         printf("Could not create fifo file\n");
         return 1;
      }
   }

   int fd = open("named_pipe", O_RDONLY);
   if(fd == -1){
      return 1;
   }

   if(read(fd, arr, sizeof(int) * 5) == -1){
      return 2;
   }

//


//

   int i;
   for(i = 0; i < 5; i++){
      printf("Received %d\n", arr[i]);
   }

   close(fd);

   return 0;
}
