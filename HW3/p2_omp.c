/*--------------------------------------------------------------------------------------------
 *   Name:		    JB
 *   Class:		    CSC 718
 *   Professor:	    Dr. Yong Wang
 *   Assignment:	#3
 *   Due Date:	    16 November 2021
 *   File Name: 	p2_omp.c
 *   Description:	
 *              Programming Assignment 4: For the 4 sequential c programs, p1.c, p2.c, p3.c, 
 *              p4.c, using openmp to parallelize them as much as possible and do the following 
 *              profiling.
 *              •	Add timestamp functions to the code to count the running time of the 
 *                  sequential programs and your openmp programs and show the result in the 
 *                  following table.
 *              •	Copy your openmp program running outputs to a report file running.txt. 
 *                  You need to make sure openmp programs should generate the same results as 
 *                  the sequential codes.
 *
 *   Notes:		
 *-------------------------------------------------------------------------------------------*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 1000000

int main (int argc, char *argv[])
{
	int i;
    int id;
    int threads = omp_get_num_procs();  // Get the # of processors available
    int chunk = (N/threads);            // Set loop iteration
	float a[1000000];
    float b[1000000];
    float sum = 0.0;
    double start;               // Start time
    double end;                 // End time
    double threadTime;          // Thread timer

    start = omp_get_wtime();    // Start the timer
    
    omp_set_num_threads(threads);   // Sets the number of threads used for parallel regions

    #pragma omp parallel shared(a,b,sum) private(i, id)
    {
        #pragma omp for schedule(static, chunk)
        for (i = 0; i < N; i++) {
            a[i] = b[i] = i * 1.0; // initialize arrays
        }

        #pragma omp barrier

        #pragma omp for schedule(static,chunk) reduction(+:sum) 
            for (i = 0; i < N; i++) {
                sum += (a[i] * b[i]*b[i]*b[i]);
            }
        id = omp_get_thread_num();                  // Set id to current thread #
        threadTime = omp_get_wtime() - start;       // Get each threads finsh time
        printf("Thread %d finished in: %.4g seconds.\n", id, threadTime); // print thread time
    }
    end = omp_get_wtime() - start;              // End total timer and get results

	printf("\tSum = %f in %.4g seconds with %d threads.\n",sum, end, threads);

    return 0;
} // End main()
