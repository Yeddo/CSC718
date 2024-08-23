/*--------------------------------------------------------------------------------------------
 *   Name:		    JB
 *   Class:		    CSC 718
 *   Professor:	    Dr. Yong Wang
 *   Assignment:	#2
 *   Due Date:	    21 October 2021
 *   File Name: 	primeCheck.c
 *   Description:	
 *                  Function to find if a number (n) is prime. The default prime finding 
 *                  method in this program uses the primality test algorithm 6k+/- 1 
 *                  optimization and is much faster. This can be used because we're just
 *                  testing for primes not getting them.
 *   Notes:		
 *                  The math library must be linked in when building the executable. 
 *                  Add -lm to mpicc command (e.g., mpicc test.c -o test -lm).
 *-------------------------------------------------------------------------------------------*/

#include <mpi.h>
#include <math.h>   // sqrt() function

#define FALSE    0  // boolean declaration
#define TRUE     1  // boolean declaration

// Return TRUE if n is prime, FALSE if not prime.
int primeCheck(int n) {

    // 1 is not a prime number by definition so not prime/FALSE.
    if (n <= 1) {
	    return FALSE;
    }
    // 2 and 3 are both primes so return prime/TRUE.
    if (n <= 3) {
	    return TRUE;
    }
    // Checks for two common cases, divisible by 2 or 3 so not prime/FALSE.
    else if (((n % 2) == 0) || ((n % 3) == 0)) {
	    return FALSE;
    }

/*
    // This is the "traditional" method, but is very slow.
    // If n is divisible by any number between 2 and n/2, not prime.
    for (int i = 5; i <= (n/2); i++) {
        if (n % i == 0) { 
            return FALSE;
        }
    }
*/
  
    int n_sqrt = (int) sqrt(n); // get the sqrt of n
    // This method uses the 6k+/- 1 primality test optimization and is much faster.
    for (int i = 5; i <= n_sqrt; i += 6) {
	    if (((n % i) == 0) || ((n % (i + 2)) == 0)) {
	        return FALSE;
	    }
    } 


    return TRUE; // If we're here, prime/TRUE!

} // end primeCheck()
