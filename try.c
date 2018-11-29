#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <string.h>
int main(int argc, char *argv[]){
  DIR *dirPtr;
  struct dirent *entryPtr;
  struct stat statBuf;
  struct passwd *psswd;
  struct group *group;

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
    if(strchr(argv[1], 'n')) {

      // Print out owners name if found using getpwuid()
      if ((psswd = getpwuid(statBuf.st_uid)) != NULL)
        printf("%-8.8s ", psswd->pw_name);
      else
        printf("%-8d ", statBuf.st_uid);

      // group name in words if found using getgrgid() else just numbers
      if ((group = getgrgid(statBuf.st_gid)) != NULL)
        printf("%-8.8s ", group->gr_name);
      else
        printf("%-8d ", statBuf.st_gid);
    }

    // Include inode num on each file print, found in Inode man page stat.st_ino;.
    if(strchr(argv[1], 'i'))
      printf("%lu ", statBuf.st_ino);

    printf("%s \n", entryPtr->d_name);

    }

  closedir (dirPtr);
  return 0;

}
