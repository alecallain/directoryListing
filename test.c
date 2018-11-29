#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char *argv[])
{
   DIR *dirPtr;
   struct dirent *entryPtr;
   struct stat statBuf;

   printf("this is what you requested: %s\n\n.", argv[1]);

   dirPtr = opendir (argv[1]);

   while ((entryPtr = readdir (dirPtr))){
  	stat (entryPtr->d_name, &statBuf);
  	printf("%-20s	%lld\n", entryPtr->d_name, statBuf.st_size);
   }
   closedir (dirPtr);
   return 0;
}
