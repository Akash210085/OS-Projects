#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define ull unsigned long long


int main(int argc, char *argv[])
{
	// Case 1: Invalid Input
	if (argc < 2)
	{
		printf("UNABLE TO EXECUTE\n");
		return 0;
	}
	// Case 2: This is the last program (only value is given)
	else if (argc == 2)
	{
		ull x = atoll(argv[1]);
		ull result = 2 * x;
		printf("%llu\n", result);
		return 0;
	}

	// Case 3: There are more programs after this one

	ull x = atoll(argv[argc-1]);
	ull result = 2 * x;

	char **args = malloc(sizeof(char *) * (argc-1));
	

    char *newArg0 = malloc(strlen("./") + strlen(argv[1]) + 1);

    strcpy(newArg0, "./");

    strcat(newArg0, argv[1]);

	args[0]=newArg0;

	for(int i=1;i<argc-2;i++){
		args[i]=argv[i+1];
	}

	char buffer[20];
	sprintf(buffer,"%lld",result);
	args[argc-2]=buffer;

	args[argc-1]=NULL;

	pid_t pid = fork();

	if (pid == 0)
	{
		execvp(args[0], args);
		perror("UNABLE TO EXECUTE\n");
		exit(1);
	}
	return 0;
}
