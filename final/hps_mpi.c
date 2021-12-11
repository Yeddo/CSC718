/*--------------------------------------------------------------------------------------------
 *   Name:		    Jason Bisnette
 *   Class:		    CSC 718
 *   Professor:	    Dr. Yong Wang
 *   Assignment:	Final Exam
 *   Due Date:	    14 December 2021
 *   File Name: 	hps_mpi.c
 *   Description:
 *              OpenMPI Version:	
 *              Programming Assignment: 
 *                      The program can be used to calculate harmonic progression sum.
 *                      The simplest harmonic progression is	1/, 1/2, 1/3, ...
 *                      
 *                      Let S(n) = 1/1 + 1/2 + 1/3 + ... + 1/i.
 *                      
 *                      For example S(7) = 2.592857142857 to 12 digits of precison.
 *-------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

int proc;   // # of processors
int id;     // processor ID

// Combines values from all processes and distributes
void reduce(long unsigned int send_digits[], int d, int n) {

    long unsigned int recv_digits[d+11];    // Holds recieved data
    int i = 0;                              // Loop counter
    
    for(i = 0; i < d + 11; i++) {
        recv_digits[i] = 0;                 // Fill with 0's
    }

    MPI_Reduce(send_digits, recv_digits,(d+11),MPI_UNSIGNED_LONG,MPI_SUM,0,MPI_COMM_WORLD); // Combines values from all processes

    for(i = 0; i < d + 11; i++) {
        send_digits[i] = recv_digits[i];    // Put recived into send
    }
} // end reduce()

// Worker function to distribute the tasks among processors
void worker(long unsigned int *digits, int d, int n) {
    
    MPI_Comm_size(MPI_COMM_WORLD, &id);     // Get process identifier
    MPI_Comm_rank(MPI_COMM_WORLD, &proc);   // Get # of processors

    int i;                                  // Counter variable
    long unsigned int digit;                // Array
    long unsigned int remainder;

    for (i = proc+1; i <= n; i+=id){        // proc and id handle the splitting up of the work between processors
        remainder = 1;
        for (digit = 0; digit < d + 11 && remainder; ++digit) {
            long unsigned int div = remainder / i;
            long unsigned int mod = remainder % i;
            digits[digit] += div;
            remainder = mod * 10;
        }
    }
} // end worker()


long unsigned *hpsMPI(int d, int n) {
    
    long unsigned int *digits;
    digits = (long unsigned int *)malloc(sizeof(long unsigned int) * (d+11));

    for (int digit = 0; digit < d + 11; ++digit)
        digits[digit] = 0;

    worker(digits, d, n); // Call worker to do work
    reduce(digits, d, n); // Reduce and redistribute
    
    // step r1: init regroupng, from d+11-1 to 1
    for (int i = d + 11 - 1; i > 0; --i) {
        digits[i - 1] += digits[i] / 10;
        digits[i] %= 10;
    }

    // step r2: skip all the digiths after d
    if (digits[d + 1] >= 5) {
        ++digits[d];
    }

    // step r3: regrouping again because of r2
    for (int i = d; i > 0; --i) {
        digits[i - 1] += digits[i] / 10;
        digits[i] %= 10;
    }
   
    return digits;
} // end hpsMPI()

int main(int argc, char **argv) {

    int i;                  // loop counter
    double elapsed_time;    // execution time
    double curr_time;	    // proc time

    if (!proc) { // Just master
        if (argc != 3) {
	        printf("usage: hps n d\n");
	        printf("    n: value of N (Example: 5 => 1/1 + 1/2 + 1/3 + 1/4 + 1/5)\n");
	        printf("    d: numbers of Digits (Example: 5 => 0,xxxxx) \n");
	        exit(-1);
        }
    }

    int n = atoi((char*)argv[1]);           // value of N
    int d = atoi((char*)argv[2]);	        // numbers of digits

    MPI_Init(&argc, &argv);                 // Initialize the MPI environment
    MPI_Barrier(MPI_COMM_WORLD);            // Block/Process starting point

    elapsed_time = -MPI_Wtime();            // Start timer here

    long unsigned int *harmonicSum;         // Holds results
    harmonicSum = (long unsigned int *)malloc(sizeof(long unsigned int) * (d+11)); // Make space
    harmonicSum = hpsMPI(d,n);              // Call HPS function
    curr_time = elapsed_time + MPI_Wtime(); // Get current proc time
    
    printf(" Processor: %d  finished in: %10.9f seconds\n" ,proc, curr_time); // Print results for each processor
    fflush (stdout);

    elapsed_time += MPI_Wtime();    // Turn off timer
    MPI_Finalize();                 // Finalize the MPI environment

    // Print results
    if (!proc) { // Just master
        printf("\nS(%d) = ", n);
        printf("%ld.", harmonicSum[0]);
        for (i = 1; i <= d; ++i) 
        {
	        printf("%ld",harmonicSum[i]);
        }
        printf(" to %d digits of precison.\n", d);
        printf("\n\tCalculated in %10.9f seconds using %d processors.\n\n", elapsed_time, id);    
        fflush(stdout);
    }

    free(harmonicSum); // free space
    
    return 0;
} // end main()