#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <string.h>
#include <time.h>

void premissions(struct stat statBuf);
void modTime(struct stat statBuf);

int main(int argc, char *argv[]){
  DIR *dirPtr;
  struct dirent *entryPtr;
  struct stat statBuf;

  // path exists check
  if (argc < 2) {
    printf ("Wrong number of arguments\n");
    exit(1);
  }
  if (stat (argv[2], &statBuf) < 0) {
    perror ("huh?  there is ");
    exit(1);
  }

  // Open directory.
  if ((dirPtr = opendir(argv[2])) == NULL) {
    printf("%s is NOT a directory.\n", argv[1]);
    exit(1);
  }

  // while there are things to read from the dir
  while ((entryPtr = readdir (dirPtr))){
    stat (entryPtr->d_name, &statBuf);
    if (!S_ISDIR(statBuf.st_mode)) {
      if(strchr(argv[1], 'n')) {

        // printf("%o ", statBuf.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
        // a user friendly print https://stackoverflow.com/questions/10323060/printing-file-permissions-like-ls-l-using-stat2-in-c
        premissions(statBuf);

        printf("%ld ", statBuf.st_nlink);

        // else
        printf("%-6d ", statBuf.st_uid);

        // else
        printf("%-6d ", statBuf.st_gid);

        //stat.st_size
        printf("%-8ld ", statBuf.st_size);

        //stat.st_atime;
        // user friendly output https://stackoverflow.com/questions/13542345/how-to-convert-st-mtime-which-get-from-stat-function-to-string-or-char
        // printf("%ld ",statBuf.st_atime);
        modTime(statBuf);
      }

      // Include inode num on each file print, found in Inode man page stat.st_ino;.
      if(strchr(argv[1], 'i'))
        printf("%lu ", statBuf.st_ino);

      printf("%s \n", entryPtr->d_name);
      }
  }

  closedir (dirPtr);
  return 0;

}

void modTime(struct stat statBuf){
  time_t t = statBuf.st_mtime;
  struct tm lt;
  localtime_r(&t, &lt);
  char timbuf[80];
  strftime(timbuf, sizeof(timbuf), "%c", &lt);
  printf("%s ", timbuf);
}

void premissions(struct stat statBuf){
    printf( (S_ISDIR(statBuf.st_mode)) ? "d" : "-");
    printf( (statBuf.st_mode & S_IRUSR) ? "r" : "-");
    printf( (statBuf.st_mode & S_IWUSR) ? "w" : "-");
    printf( (statBuf.st_mode & S_IXUSR) ? "x" : "-");
    printf( (statBuf.st_mode & S_IRGRP) ? "r" : "-");
    printf( (statBuf.st_mode & S_IWGRP) ? "w" : "-");
    printf( (statBuf.st_mode & S_IXGRP) ? "x" : "-");
    printf( (statBuf.st_mode & S_IROTH) ? "r" : "-");
    printf( (statBuf.st_mode & S_IWOTH) ? "w" : "-");
    printf( (statBuf.st_mode & S_IXOTH) ? "x" : "-");
    printf(" ");
}
