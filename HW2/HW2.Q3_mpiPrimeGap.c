/*--------------------------------------------------------------------------------------------
 *   Name:		    Jason Bisnette
 *   Class:		    CSC 718
 *   Professor:	    Dr. Yong Wang
 *   Assignment:	#2
 *   Due Date:	    21 October 2021
 *   File Name: 	HW2.Q3_mpiPrimeGap.c
 *   Description:	
 *                  The gap between consecutive prime numbers 2 and 3 is only 1, while the gap
 *                  between consecutive primes 7 and 11 is 4.  Write a parallel program to
 *                  determine, for all integers less than 1,000,000, the largest gap between a
 *                  pair of consecutive prime numbers.
 *-------------------------------------------------------------------------------------------*/

#include <mpi.h>
#include <stdio.h>
#include "primeCheck.h"     // prime number utility
#include "splitNums.h"      // utility to split data evenly among processes

#define LIMIT 1000000           // # of integers to check

int main(int argc, char *argv[]) {

    int id;                     // process id
    int proc;                   // # of process
    int first_num;              // 1st number in group
    int last_num;               // last number in group
    int last_prime = 0;         // the most recent prime found in group
    int primeGap;               // the length between the most recent and prev. prime
    int i;                      // loop counter
    int local_primeGap = 0;     // local gap of primes
    int global_primeGap = 0;    // global/total gap of primes

    double elapsed_time;        // execution time
    double curr_time;           // proc time

    MPI_Init(&argc, &argv);                 // Initialize the MPI environment
    MPI_Barrier(MPI_COMM_WORLD);            // Block/Process starting point
    elapsed_time = -MPI_Wtime();            // Start timer here
    MPI_Comm_size(MPI_COMM_WORLD, &id);     // Get the id of the processes
    MPI_Comm_rank(MPI_COMM_WORLD, &proc);   // Get the # of the process
    
    /* Globally split the numbers from 1 to LIMIT into evenly sized groups depending on #processes. 
     * Locally set first_num and last_num to be the smallest and largest values of the group. */
    splitNums(proc, id, LIMIT, &first_num, &last_num);

    /* Each iteration checks an odd number to see if it is prime; if so, the gap between prime numbers 
     * is compared to the previous (primeGap > local_primeGap) and the gap is updated accordingly. */
    for (i = first_num; last_prime <= last_num && (i <= LIMIT); i += 2) {   // i starts at an 1/odd and moves by 2 (odds). See splitNums.c.
        if (primeCheck(i)) {                        // if prime found in the group
            if (! last_prime) {                     // if first prime (0) in group do nothing
            }
            else {                                  // if not first prime in group
                primeGap = i - last_prime;          // set the gap to i - last_prime
                if (primeGap > local_primeGap) {    // check if the current gap > local_primeGap
                    local_primeGap = primeGap;      // if so sets the local_primeGap to current primeGap
                }
            }
            last_prime = i;                         // set last_prime to most recent prime in group (i)
    	}
    }
    
    curr_time = elapsed_time + MPI_Wtime();         // get current proc time
    
    // Print results for each processor, keep this on one line or it gets messy.
    
    printf(" Processor: %d Finished at: %10.9f seconds.\n The largest gap between prime numbers in the set from %d to %d is:  %d\n\n\n",proc, curr_time, first_num, last_num, local_primeGap);
    fflush (stdout); 

    MPI_Reduce(&local_primeGap, &global_primeGap, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD); // Collect local prime gap
    elapsed_time += MPI_Wtime();     // Turn off timer
    MPI_Finalize();                  // Finalize the MPI environment

    // Print total results
    if (!proc) {
        printf(" * The largest gap between prime numbers from 2 to %d is:  %d\n\n", LIMIT, global_primeGap);
        fflush (stdout); 
        printf(" ** Total elapsed time: %10.6f **\n\n", elapsed_time);
        fflush (stdout); 

    }

    return 0;

} // End main()
