/********************************/
// File: filestat.c
// print inode data

#include <stdio.h>		/* printf */
#include <unistd.h>		/* fork */
#include <sys/stat.h>		/* stat*/
#include <sys/types.h>          /* struct stat*/
#include <fcntl.h>              /* open, write */
#include <dirent.h>             /* struc dirent */
#include <stdlib.h>
#include <time.h>
#include <pwd.h>

int main(void)
{
  char dir_name[20];
  struct dirent *my_dir;   // directory entry 3 fields
  DIR *dir_fd;             // type DIR din <dirent.h> open directory descripor
  struct stat sb;

  struct passwd *pws;
  struct tm *tm;
  char buffer[96];

  getcwd(dir_name, 100);
  //printf ("My current directory is %s \n", dir_name);

  dir_fd = opendir(dir_name);
  my_dir= readdir(dir_fd);

  while (my_dir != NULL){
    stat(my_dir->d_name, &sb);

    printf((S_ISDIR(sb.st_mode)) ? "d" : "-");
    printf((sb.st_mode & S_IRUSR) ? "r" : "-");
    printf((sb.st_mode & S_IWUSR) ? "w" : "-");
    printf((sb.st_mode & S_IXUSR) ? "x" : "-");
    printf((sb.st_mode & S_IRGRP) ? "r" : "-");
    printf((sb.st_mode & S_IWGRP) ? "w" : "-");
    printf((sb.st_mode & S_IXGRP) ? "x" : "-");
    printf((sb.st_mode & S_IROTH) ? "r" : "-");
    printf((sb.st_mode & S_IWOTH) ? "w" : "-");
    printf((sb.st_mode & S_IXOTH) ? "x" : "-");
    printf(" ");

    tm = localtime(&sb.st_mtime);
    strftime(buffer,96,"%a %d %H:%M", tm);

    pws = getpwuid(sb.st_uid);
    printf("%ld %s %lld %s %s\n", (long) sb.st_nlink, pws->pw_name, (long long) sb.st_size, buffer, my_dir->d_name);
    my_dir=readdir(dir_fd);
  }
  closedir(dir_fd);
}
