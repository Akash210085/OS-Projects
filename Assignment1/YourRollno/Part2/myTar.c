#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <dirent.h>
#include <sys/stat.h>
int main(int argc, char* argv[])
{
	
	if(strcmp(argv[1], "-c") == 0){
		// create tar file

		char *dirPath = malloc(strlen(argv[2]) + 1);
		char *tarName = malloc(strlen(argv[3]) + 1);
		strcpy(dirPath, argv[2]); 
		strcpy(tarName, argv[3]);
		// printf("dirPath:%s tarName:%s\n", dirPath,tarName);


		DIR *dir = opendir(dirPath);
		if (!dir) {
			perror("opendir");
			return 1;
		}

		struct dirent *entry;
		while ((entry = readdir(dir)) != NULL) {
			// Skip "." and ".."
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;

			// Build full path to the file
			char fullpath[1024];
			snprintf(fullpath, sizeof(fullpath), "%s/%s", dirPath, entry->d_name);

			struct stat st;
			if (stat(fullpath, &st) == -1) {
				perror("stat");
				continue;
			}

			printf("File: %s, Size: %lld bytes\n", entry->d_name, (long long)st.st_size);
		}

		closedir(dir);


	}else if (strcmp(argv[1], "-d") == 0)
	{
		// extract all tar files
	}else if (strcmp(argv[1], "-e") == 0)
	{
		// extract single file from tar file
	}else if (strcmp(argv[1], "-l") == 0)
	{
		// listing the content of tar file
	}
	return 0;
}
