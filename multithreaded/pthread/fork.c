#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int status = EXIT_SUCCESS;
	pid_t pid = fork();

	switch (pid)
	{
		case -1:
			perror("fork");
			status = EXIT_FAILURE;
			break;
		case 0:
			printf("child\n");
			break;
		default:
			printf("parent\n");
			wait(&status);
	}
	return status;
}
