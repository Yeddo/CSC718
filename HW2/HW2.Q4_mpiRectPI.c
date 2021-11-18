/*--------------------------------------------------------------------------------------------
 *   Name:		    Jason Bisnette
 *   Class:		    CSC 718
 *   Professor:	    Dr. Yong Wang
 *   Assignment:	#2
 *   Due Date:	    21 October 2021
 *   File Name: 	HW2.Q4_mpiRectPI.c
 *   Description:	
 *                  The value of the definite integral: int_0^1 \frac{ 4 }{ 1 + x^2 } dx = pi.  
 * 
 *                  We can use numerical integration to compute pi by approximating the
 *                  area under the curve.  A simple way to do this is called the rectangle rule.
 *                  We divide the interval [0, 1] into i sub intervals of equal id.  We find the
 *                  height of the curve at the midpoint of each of these subintervals.  With
 *                  these heights we can construct i rectangles.  The area of the rectangles
 *                  approximates the area under the curve.  As i increases the accuracy of the
 *                  estimate also increases.  Write a parallel program to compute pi using the
 *                  rectangle rule with 1,000,000 intervals.
 *-------------------------------------------------------------------------------------------*/

#include <mpi.h>
#include <stdio.h>

#define INTERVALS 1000000           // # intervals

int main(int argc, char *argv[]) {

    int id;                         // process id
    int proc;                       // # of process
    int i;                          // loop counter

    double xi;                      // midpoint of Interval. 1/2 rect. width (i.e. where fcn is evaluated)
    double ysum = 0.0;              // sum of process rect. areas
    double global_area;             // global sum of rectangle areas
    double elapsed_time;            // execution time
    double curr_time;	     // proc time
    
    MPI_Init(&argc, &argv);                 // Initialize the MPI environment
    MPI_Barrier(MPI_COMM_WORLD);            // Block/Process starting point
    elapsed_time = -MPI_Wtime();            // Start timer here
    MPI_Comm_size(MPI_COMM_WORLD, &id);     // Get the id of the processes
    MPI_Comm_rank(MPI_COMM_WORLD, &proc);   // Get the # of the process

    
    for (i = proc; i < INTERVALS; i += id) { // Evaluates every interval (per process) and adds the area to ysum.
        xi = ((1.0/INTERVALS)*(i+0.5));      // Midpoint of interval
	    ysum += 4.0/(1.0 + xi * xi);         // math
    }

    curr_time = elapsed_time + MPI_Wtime();       // get current proc time
    
    // Print results for each processor
    printf(" Processor: %d  finished at: %10.6f seconds\n"
           " Area: %13.11f\n\n" ,proc, curr_time, ysum/INTERVALS);
    fflush (stdout); 
    
    MPI_Reduce(&ysum, &global_area, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD); // Sum the unnormalized processes areas
    elapsed_time += MPI_Wtime();    // Turn off timer
    MPI_Finalize();                 // Finalize the MPI environment

    global_area /= INTERVALS; // area of the rectangles

    // Print results
    if (!proc) {
    	printf(" * The value from summing the rectagles is: %13.11f\n\n"
	       " ** Total elapsed time: %10.6f **\n\n", global_area, elapsed_time);
        fflush (stdout); 
    }
    
    return 0;

} // End main()
