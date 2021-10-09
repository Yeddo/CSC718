/*
 *  barrier1.c
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

pthread_barrier_t   barrier; // barrier synchronization object

void *
thread1 (void *not_used)
{
    time_t  now;

    time (&now);

    printf ("thread1 starting at %s", ctime (&now));
fflush(stdout);

    // do the computation
    // let's just do a sleep here...
    sleep (20);
    pthread_barrier_wait (&barrier);
    // after this point, all three threads have completed.
    time (&now);
    printf ("barrier in thread1() done at %s", ctime (&now));
}

void *
thread2 (void *not_used)
{
    time_t  now;

    time (&now);
    printf ("thread2 starting at %s", ctime (&now));
fflush(stdout);

    // do the computation
    // let's just do a sleep here...
    sleep (40);
    pthread_barrier_wait (&barrier);
    // after this point, all three threads have completed.
    time (&now);
    printf ("barrier in thread2() done at %s", ctime (&now));
}

int main () // ignore arguments
{
    time_t  now;

    printf("begin");
    fflush(stdout);

    // create a barrier object with a count of 3
    pthread_barrier_init (&barrier, NULL, 3);

    // start up two threads, thread1 and thread2
    pthread_t tid1, tid2;
    if (pthread_create(&tid1, NULL, thread1, NULL) != 0)
    {
	perror("error creating child");
	return EXIT_FAILURE;	
    }

   if (pthread_create(&tid2, NULL, thread2, NULL) != 0)
    {
	perror("error creating child");
	return EXIT_FAILURE;	
    } 

    // at this point, thread1 and thread2 are running

    // now wait for completion
    time (&now);
    printf ("main() waiting for barrier at %s", ctime (&now));
    pthread_barrier_wait (&barrier);

    // after this point, all three threads have completed.
    time (&now);
    printf ("barrier in main() done at %s", ctime (&now));
    pthread_exit( NULL );
    return (EXIT_SUCCESS);
}
