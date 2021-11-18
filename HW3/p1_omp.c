/*--------------------------------------------------------------------------------------------
 *   Name:		    Jason Bisnette
 *   Class:		    CSC 718
 *   Professor:	    Dr. Yong Wang
 *   Assignment:	#3
 *   Due Date:	    16 November 2021
 *   File Name: 	p1_omp.c
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

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define INTERVALS 100000000       // This can be changed

int main(int arc, char* argv[])
{
	double area = 0.0;                  // Will be the value of pi after calculating total area
    int threads = omp_get_num_procs();  // Get the # of processors available and set this to threads
    double ysum[threads];	            // Sum of rectangle heights. Variable to accumlulate thread results must be shared!
    double start;               // Start time
    double end;                 // End time
    double threadTime;          // Thread timer

    start = omp_get_wtime();    // Start the timer
    
    omp_set_num_threads(threads);   // Sets the number of threads used for parallel regions

    #pragma omp parallel                // Start parallelism
    {
      	double xi;	                    // Midpoint of interval
        int i;                          // Counter
        int id = omp_get_thread_num();  // Set id to current thread #
        
        for (i = id, ysum[id] = 0.0; i < INTERVALS; i += threads) // Assign loop iterations to threads
        {
            xi = ((1.0 / INTERVALS) *  (i + 0.5));  // Midpoint of interval
            ysum[id] += 4.0 / (1.0 + xi * xi);      // Update ysum for thread
        }

        threadTime = omp_get_wtime() - start;       // Get each threads finsh time

        printf("Thread %d finished in: %.4g seconds.\n", id, threadTime); // print thread time

    } // end parallelism

    for ( int i = 0; i < threads; i++) {    // Loop to get the total area for each thread
        area += ysum[i] * (1.0/INTERVALS);      // Calculate area/pi and sum each thread for total
    }
    
    end = omp_get_wtime() - start;              // End total timer and get results

	printf("\tpi is %13.11f calculated in %.4g seconds with %d threads.\n", area, end, threads); // Print results

	return 0;

} // End main()
