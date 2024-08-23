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

#define NRA 620  // number of rows in matrix A
#define NCA 150  // number of columns in matrix A
#define NCB 70   // number of columns in matrix B

int main (int argc, char *argv[]) {
    int	tid;                            // Holds thread #
    int i;                              // Counter
    int j;                              // Nested counter
    int k;                              // Double nested counter
    int chunk = 10;                     // Set loop iteration chunk size
    int nthreads = omp_get_num_procs(); // Get the # of processors available
    double a[NRA][NCA];                 // Matrix A to be multiplied
    double b[NCA][NCB];                 // Matrix B to be multiplied
    double c[NRA][NCB];                 // Result matrix C
    double start;                       // Start time
    double end;                         // End time
    double threadTime;                  // Thread timer

    start = omp_get_wtime();    // Start the timer

    #pragma omp parallel shared(a,b,c,nthreads,chunk) private(tid,i,j,k) // parallel region w/scoping
    {    
        tid = omp_get_thread_num();
        
        #pragma omp for nowait // Initialize matrix
            for (i = 0; i < NRA; i++) {
                for (j = 0; j < NCA; j++) {
                    a[i][j]= i+j;
                }
            }

        #pragma omp for nowait // Initialize matrix
            for (i = 0; i < NCA; i++) {
                for (j = 0; j < NCB; j++) {
                    b[i][j]= i*j;
                }
            }

        #pragma omp for nowait // Initialize matrix
            for (i = 0; i < NRA; i++) {
                for (j = 0; j < NCB; j++) {
                    c[i][j]= 0;
                }
            }
      
        #pragma omp for schedule (static, chunk)
            for (i = 0; i < NRA; i++) {
                printf("Thread %d completed row %d\n", tid, i); // See rows each thread completed. 10 rows at a time (chunk size).
                for(j = 0; j < NCB; j++) {
                    for (k = 0; k < NCA; k++) {
                        c[i][j] += a[i][k] * b[k][j];
                    }
                }
            }
        threadTime = omp_get_wtime() - start;       // Get each threads finsh time
        printf("\nThread %d completed in %.9f seconds", tid, threadTime);

        if (tid == 0) {
            end = omp_get_wtime(); // stop timer
        }
    }// End parallelization

    /*** Print results ***/
    printf("\n\n******************************************************\n");
    printf("Result Matrix:\n");
    for (i=0; i<NRA; i++) {
        for (j=0; j<NCB; j++) {
            printf("%6.2f   ", c[i][j]);
        }
        printf("\n");

    }
    printf("******************************************************\n");
    printf ("Done.\n");
    printf("\tCalculation complete in %.9f seconds using %d threads.\n", end - start, nthreads);
}
