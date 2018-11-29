#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main()
{
   DIR *dirPtr;
   struct dirent *entryPtr;
   struct stat statBuf;

   dirPtr = opendir ("/home/bolena");

   while ((entryPtr = readdir (dirPtr))){
  	stat (entryPtr->d_name, &statBuf);
  	printf("%-20s	%ld\n", entryPtr->d_name, statBuf.st_size);
   }
   closedir (dirPtr);
   return 0;
}
