/*--------------------------------------------------------------------------------------------
 *   Name:		    JB
 *   Class:		    CSC 718
 *   Professor:	    Dr. Yong Wang
 *   Assignment:	#3
 *   Due Date:	    16 November 2021
 *   File Name: 	p3_omp.c
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

#define VECLEN 100000000

float a[VECLEN];
float b[VECLEN];
float sum;
double threadTime;          // Thread timer
double start;               // Start time

float dotprod () {
    int i;
    int tid;
    tid = omp_get_thread_num();

    #pragma omp for reduction(+:sum) // all copies will be combined at the end in a shared copy (sum)
        for (i = 0; i < VECLEN; i++) {
            sum += (a[i]*b[i]);
        }
        threadTime = omp_get_wtime() - start;                       // Get each threads finsh time
        printf("Thread %d finished in %.9g\n", tid, threadTime);    // Print thread time
    return 0;
}

int main (int argc, char *argv[]) {
    int threads = omp_get_num_procs();  // Get the # of processors available
    int i;                              // Counter
    double end;                         // End time

    omp_set_num_threads(threads);       // Sets the number of threads used for parallel regions
    start = omp_get_wtime();            // Start the timer

    for (i = 0; i < VECLEN; i++) {
        a[i] = b[i] = 1.0 * i;
    }
    sum = 0.0;

    #pragma omp parallel
        dotprod();

    end = omp_get_wtime() - start;              // End total timer and get results

    printf("\tSum = %f calculated in %.9g seconds with %d threads.\n",sum, end, threads); // Print results
	return 0;

} // End main()

