#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *child(void *arg)
{
	printf("%s\n", arg);
	return (void*)"okay";
}

int main(int argc, char *argv[])
{
	pthread_t tid;
	void *arg = (void*)"child";
	void *status;

	if (pthread_create(&tid, NULL, child, arg) != 0)
	{
		perror("error creating child");
		return EXIT_FAILURE;	
	}

	printf("parent\n");
	pthread_join(tid, &status);
	printf("child said: %s\n", status);

	return EXIT_SUCCESS;
}

