#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

void parse(char* strInput, char** parsedInput);


int main(int argc, char *argv[])
{
  DIR *dirPtr;
  struct dirent *entryPtr;
  struct stat statBuf;

  // while(strcmp(parsedInput[0], "exit") != 0){
  printf("0: %s \n", argv[1]);
    // path exists check
    if (argc < 2) {
    		printf ("Wrong number of arguments\n");
    		exit(1);
    }
    if (stat (argv[1], &statBuf) < 0) {
    		perror ("huh?  there is ");
    		exit(1);
    }

    dirPtr = opendir (argc[1]);

    while ((entryPtr = readdir (dirPtr))){
      stat (entryPtr->d_name, &statBuf);
      printf("%-20s	%ld\n", entryPtr->d_name, statBuf.st_size);
    }

    closedir (dirPtr);
    return 0;
    // }
}

void parse(char * strInput, char** parsedInput)
{
	char *pos;
	if((pos=strchr(strInput, '\n')) != NULL){
		*pos = '\0';
	}
	char * pch;
	pch = strtok(strInput," ");
	int count = 0;
  	while (pch != NULL)
 	{
    	//	printf ("*%s*\n",pch);
    		parsedInput[count] = pch;
    		pch = strtok (NULL, " ");
    		count++;
  	}
	parsedInput[count]=NULL;
}
