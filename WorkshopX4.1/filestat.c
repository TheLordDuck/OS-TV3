/********************************/
// File: filestat.c
// print inode data

#include <stdio.h>		/* printf */
#include <unistd.h>		/* fork */
#include <sys/stat.h>		/* stat*/
#include <sys/types.h>          /* struct stat*/
#include <fcntl.h>              /* open, write */

int main(void)
{

  struct student {
    char name[10];
    int  grade;
  };

  int fd, my_return; int i = 0;
  struct student my_student;

  fd = open("/home/ivan/my_grades.txt", O_RDWR | O_CREAT, S_IRUSR |S_IWUSR);
  printf("my_fd %d",fd);
  if (fd == -1)
    perror("!error open :");

  // stat file
  struct stat finfo;
  
  fstat(fd, &finfo);
  printf( "File stat. \n");
  printf( "Logical disk. %d \n", (int) finfo.st_dev);
  printf( "i-node. %d \n", (int)finfo.st_ino);
  printf( "Filetype and access rigths. %d \n", (int) finfo.st_mode);
  printf( "Nber of links. %d \n", (int) finfo.st_nlink);
  printf( "File owner. %d \n", (int) finfo.st_uid);
  printf( "File Size. %d \n",(int) finfo.st_size);
  printf( "Last access date. %d \n",(int) finfo.st_atime);
  printf( "Last modification date. %d \n", (int) finfo.st_mtime);
  printf( "Last node modification. %d \n",(int) finfo.st_ctime);
  printf( "Block size. %d \n", (int) finfo.st_blksize);
  printf( "Blocks allocated to file. %d \n\n", (int) finfo.st_blocks);

  if (S_ISBLK(finfo.st_mode)) printf ("block file\n");
  if (S_ISCHR(finfo.st_mode))  printf ("Char file\n");
  if (S_ISDIR(finfo.st_mode))  printf ("Directory file\n");
  if (S_ISFIFO(finfo.st_mode))  printf ("Pipe file\n");
  if (S_ISREG(finfo.st_mode))  printf ("Regular file\n");
 
  
  while (i < 4) {
    printf("Enter a student name: \n");
    scanf ("%s", my_student.name);
    printf("Enter a student grade: \n");
    scanf ("%d", &my_student.grade);
    write (fd, &my_student, sizeof(my_student));
    i++;
  }

  // repositions in filedescriptor
  my_return = lseek (fd, sizeof(my_student), SEEK_SET);
  if (my_return == -1)
    perror("!error lseek");
  printf(" new position is %d\n", my_return);

  i = 0;
  while ( i < 4) {
    read (fd, &my_student, sizeof(my_student));
    printf ("name and grade %s, %d \n", my_student.name, my_student.grade);
    i++;
  }
  close(fd);
}
		  
 
