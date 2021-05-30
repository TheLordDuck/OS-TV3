/********************************/
// File: filestat.c
// print inode data

#include <stdio.h>		/* printf */
#include <unistd.h>		/* fork */
#include <sys/stat.h>		/* stat*/
#include <sys/types.h>          /* struct stat*/
#include <fcntl.h>              /* open, write */
#include <dirent.h>             /* struc dirent */

int main(void)
{
  char dir_name[20];
  struct dirent *my_dir;   // directory entry 3 fields
  DIR *dir_fd;             // type DIR din <dirent.h> open directory descripor

  getcwd(dir_name, 20);
  printf ("My current directory is %s \n", dir_name);
  
  dir_fd = opendir(dir_name);
  my_dir= readdir(dir_fd);

  while (my_dir != NULL){
    printf(" Directory entry %s, i-node %d, size %d \n",
	   my_dir->d_name, (int)my_dir->d_ino, my_dir->d_reclen);
    my_dir=readdir(dir_fd);
  }
  closedir(dir_fd);
}
		  
 
