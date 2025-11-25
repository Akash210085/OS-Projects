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
	}
	// Case 2: This is the last program (only value is given)
	else if (argc == 2)
	{
		ull x = atoll(argv[1]);
		ull result = x*x;
		printf("%llu", result);
		exit(result % 256);
	}

	// Case 3: There are more programs after this one

	pid_t pid = fork();

	if (pid == 0)
	{
		char **args = malloc(sizeof(char *) * argc);

		for (int i = 1; i < argc; i++)
			args[i - 1] = argv[i];

		args[argc - 1] = NULL;

		char *path = malloc(strlen(args[0]) + 3);
		strcpy(path, "./");
		strcat(path, args[0]);

		// Redirect child's stdout to /dev/null to suppress output
        freopen("/dev/null", "w", stdout);
		execvp(path, args);
		perror("UNABLE TO EXECUTE\n");
		exit(1);
	}

	int status;
	wait(&status);

	ull value = WEXITSTATUS(status);
	ull result = value*value;
	printf("%llu", result);
	exit(result % 256);

	return 0;
}
