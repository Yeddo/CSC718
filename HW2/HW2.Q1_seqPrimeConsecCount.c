/*--------------------------------------------------------------------------------------------
 *   Name:		    JB
 *   Class:		    CSC 718
 *   Professor:	    Dr. Yong Wang
 *   Assignment:	#2
 *   Due Date:	    21 October 2021
 *   File Name: 	HW2.Q1_seqPrimeConsecCount.c
 *   Description:	
 *              A prime number is a positive integer evenly divisible by exactly two positive
 *              integers: itself and 1. Write a sequential program to determine for all 
 *              integers less than 1,000,000, the number of times that two consecutive odd 
 *              integers are both prime numbers. 
 *   Notes:		
 *-------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include "primeCheck.h" // prime number utility

#define LIMIT 1000000   // # of integers to check

int main(int argc, char *argv[]) {

    int curr_odd = 0;       // tracks current odd prime
    int next_odd;           // tracks next_odd prime
    int i;                  // loop counter
    int local_count = 0;    // track the local number of pairs of primes

    /* Each iteration checks if the pair of odd numbers (i - 2) and i are both prime and if so adds 1 to local_count. 
    *  This also checks one odd # past last_num because you have to check the end of the set with the beginning of next. */
    for (i = 1; i <= LIMIT; i += 2) {
	    next_odd = primeCheck(i);               // check if prime
        if (curr_odd == 1 && next_odd == 1) {
            local_count += 1;                   // Add 1 if both curr_odd and next_odd are prime, 0 otherwise
        }                
	    curr_odd = next_odd;                    // Update curr_odd for next_odd iteration
    }

    // Print total results
    printf(" * The number of times there are consecutive odd numbers between 2 and %d are prime is: %d\n\n", LIMIT, local_count);
    fflush (stdout); 

    return 0;
} // End Main
