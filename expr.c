#include <stdio.h> 
#include <stdlib.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <errno.h>

int main(int argc, char *argv[]) 
{ 
   struct stat statBuf;

   if (argc < 2) { 
      printf ("Usage: filename required\n"); 
      exit(1); 
   }

   if (stat (argv[1], &statBuf) < 0) { 
      perror ("huh?  there is "); 
      exit(1); 
   }

   stat(argv[1], &statBuf);
   if (S_ISDIR(statBuf.st_mode)) {
	   printf("\nThe name you entered is the name of a directory");
   }
   else {
	   printf("\nThe name you entered is not the name of a directory");
   }

   printf ("\nvalue is: %u\n", statBuf.st_mode); 
   return 0; 
}
