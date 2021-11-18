/*--------------------------------------------------------------------------------------------
 *   Name:		    Jason Bisnette
 *   Class:		    CSC 718
 *   Professor:	    Dr. Yong Wang
 *   Assignment:	#2
 *   Due Date:	    21 October 2021
 *   File Name: 	HW2.Q2_mpiPrimeConsecCount.c
 *   Description:	
 *              A prime number is a positive integer evenly divisible by exactly two positive
 *              integers: itself and 1. Write a parallel program to determine, for all
 *              integers less than 1,000,000, the number of times that two consecutive odd
 *              integers are both prime.
 *   Notes:		
 *-------------------------------------------------------------------------------------------*/

#include <mpi.h>
#include <stdio.h>
#include "primeCheck.h"     // prime number utility
#include "splitNums.h"      // utility to split data evenly among processes

#define LIMIT 1000000       // # of integers to check

int main(int argc, char *argv[]) {

    int id;                 // process id
    int proc;               // # of process
    int first_num;          // 1st number in group
    int last_num;           // last number in group
    int curr_odd = 0;       // if current odd integer is prime
    int next_odd;           // if next_odd odd integer is prime
    int i;                  // loop counter
    int local_count = 0;    // track the local number of pairs of primes
    int global_count = 0;   // track the overall number of pairs of primes

    double elapsed_time;    // execution time
    double curr_time;	    // proc time

    MPI_Init(&argc, &argv);                 // Initialize the MPI environment
    MPI_Barrier(MPI_COMM_WORLD);            // Block/Process starting point
    elapsed_time = -MPI_Wtime();            // Start timer here
    MPI_Comm_size(MPI_COMM_WORLD, &id);     // Get the id of the processes
    MPI_Comm_rank(MPI_COMM_WORLD, &proc);   // Get the # of the process

    /* Globally split the numbers from 1 to LIMIT into evenly sized groups depending on #processes. 
     * Locally set first_num and last_num to be the smallest and largest values of the  group. */
    splitNums(proc, id, LIMIT, &first_num, &last_num);

    /* This prevents the following for loop from going 1 over on the last set of numbers. */
    if (proc != (id - 1)) {
	    last_num += 2;
    }

    /* Each iteration checks if the pair of odd numbers (i - 2) and i are both prime and if so adds 1 to local_count. 
    *  This also checks one odd # past last_num because you have to check the end of the set with the beginning of next. */
    for (i = first_num; i <= last_num; i += 2) {
	    next_odd = primeCheck(i);               // check if prime
        if (curr_odd == 1 && next_odd == 1) {
            local_count += 1;                   // Add 1 if both curr_odd and next_odd are prime, 0 otherwise
        }                
	    curr_odd = next_odd;                    // Update curr_odd for next_odd iteration
    }
    
    curr_time = elapsed_time + MPI_Wtime();     // get current proc time
    
    // Print results for each processor
    printf(" Processor: %d  finished at: %10.6f seconds\n"
    	   " The number of times consecutive odd numbers between %d and %d are prime is: %d\n\n", proc, curr_time, first_num, last_num, local_count);
    fflush (stdout); 


    MPI_Reduce(&local_count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); // Collect local consecutive primes count
    elapsed_time += MPI_Wtime();    // Turn off timer
    MPI_Finalize();                 // Finalize the MPI environment.

    // Print total results
    if (!proc) {
        printf(" * The number of times consecutive odd numbers between 2 and %d are prime is: %d\n\n", LIMIT, global_count);
        fflush (stdout); 
        printf(" ** Total elapsed time: %10.6f **\n\n", elapsed_time);
        fflush (stdout); 

    }

    return 0;
} // End Main
