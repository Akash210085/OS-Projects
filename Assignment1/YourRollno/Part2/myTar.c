#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <dirent.h>
#include <sys/stat.h>


#define MAX_FILES 30000
#define MAX_LINE_LEN 40
#define BUFFER_SIZE (MAX_FILES * MAX_LINE_LEN)

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

		/*
		typedef struct {
		int fd;              file descriptor
		char *buffer;        buffer containing directory entries
		int buf_pos;         current read position in buffer
		int buf_size;         number of bytes in buffer
		} DIR;


		struct dirent {
		ino_t          d_ino;       inode number
		off_t          d_off;       not used much; offset to next entry
		unsigned short d_reclen;    length of this record (entry)
		unsigned char  d_type;      type (file, dir, symlink, etc.)
		char           d_name[];    null-terminated filename
		};



		struct stat {
           dev_t      st_dev;      /* ID of device containing file 
           ino_t      st_ino;      /* Inode number 
           mode_t     st_mode;     /* File type and mode 
           nlink_t    st_nlink;    /* Number of hard links 
           uid_t      st_uid;      /* User ID of owner 
           gid_t      st_gid;      /* Group ID of owner 
           dev_t      st_rdev;     /* Device ID (if special file) 
           off_t      st_size;     /* Total size, in bytes 
           blksize_t  st_blksize;  /* Block size for filesystem I/O 
           blkcnt_t   st_blocks;   /* Number of 512 B blocks allocated 

           /* Since POSIX.1-2008, this structure supports nanosecond
              precision for the following timestamp fields.
              For the details before POSIX.1-2008, see VERSIONS. 

           struct timespec  st_atim;  /* Time of last access 
           struct timespec  st_mtim;  /* Time of last modification 
           struct timespec  st_ctim;  /* Time of last status change 

		#define st_atime  st_atim.tv_sec  /* Backward compatibility 
		#define st_mtime  st_mtim.tv_sec
		#define st_ctime  st_ctim.tv_sec
		};


		What does readdir() do?
		Each time you call:

		entry = readdir(dir);

		Internally:

		1. It looks at dir->buffer where the directory entries are stored.

		2. It reads the current entry (dir->buf_pos).

		3. It creates a struct dirent from that raw entry.

		4. It increments dir->buf_pos to the next entry.

		5. You don’t do it. The library does it.




		*/


		struct dirent *entry;
		struct stat file_stat;
		long long totalSize = 0;

		// Large buffer to hold all file info strings
		char *allFilesInfo = malloc(BUFFER_SIZE);
		if (!allFilesInfo) {
			perror("malloc");
			closedir(dir);
			return 1;
		}
		allFilesInfo[0] = '\0';  // Initialize empty string
		int offset = 0;

		while ((entry = readdir(dir)) != NULL) {
			// Skip "." and ".."
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
				continue;

			// Build full path to the file
			char fullpath[1024];
			sprintf(fullpath, "%s/%s", dirPath, entry->d_name);

			if (stat(fullpath, &file_stat) == -1) {
				perror("stat");
				continue;
			}

			// Append to buffer using sprintf
			offset += sprintf(allFilesInfo + offset,
							"file:%s,size:%ld,",
							entry->d_name,
							file_stat.st_size);

			
			totalSize+=(long long)file_stat.st_size;
			printf("File: %s, Size: %lld bytes\n", entry->d_name, (long long)file_stat.st_size);
		}
		closedir(dir);

		printf("totalSize: %lld, fileInformation: %s",totalSize,allFilesInfo);


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
