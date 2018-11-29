#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

/**
* This class implements a select subset of
* the ls command
*
* @author Allison Bolen
* @author Alec Allain
*/

/** Instanciate methods */


/** Global variables */


/** Main method */
int main (int argc, char** argv) {
	
	struct stat statBuf;
	struct dirent *entryPtr;
	DIR *dirPtr;
	int status;
	//int option;
	
	if (argv == NULL) {
		fprintf(stderr, "\nNo specific flags were given by the user");
		exit(1);
	} else if (argc < 2) {
		fprintf(stderr, "\nWrong number of arguments");
		exit(1);
	}
	
	if (stat(argv[2], &statBuf) < 0) {
		fprintf(stderr, "Cannot access file or directory");
		exit(1);
	}
	else {
		dirPtr = opendir(argv[2]);
		// gives user and groupID for each file/directory
		if (strchr(argv[1], 'n')) {
			while (entryPtr = readdir(dirPtr)) {
				stat(entryPtr->d_name, &statBuf);
				printf("File named %-20s user number is %lu and groupID is %lu\n", entryPtr->d_name, statBuf.st_uid, statBuf.st_gid);
			}
		}
		// gives the user the inode for each file/directory
		else if (strchr(argv[1], 'i')) {
			//dirPtr = opendir(".");
			while (entryPtr = readdir(dirPtr)) {
				stat(entryPtr->d_name, &statBuf);
				printf("File named %-20s's iNode number is %lu\n", entryPtr->d_name, statBuf.st_ino);
			}
		}
		closedir(dirPtr);
	}

	return 0;
}
