/*--------------------------------------------------------------------------------------------
 *   Name:		    JB
 *   Class:		    CSC 718
 *   Professor:	    Dr. Yong Wang
 *   Assignment:	Final Exam
 *   Due Date:	    14 December 2021
 *   File Name: 	hps_omp.c
 *   Description:
 *              OpenMP Version:	
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
#include <omp.h>

double start;                       // Start time
double threadTime;                  // Thread timer

// HPS function()
long unsigned *hpsOMP(int d, int n) {

    long unsigned int *digits;
    digits = (long unsigned int *)malloc(sizeof(long unsigned int) * (d+11));

    int	tid;                            // Holds thread #
    tid = omp_get_thread_num();         // Gets thread #

    for (int digit = 0; digit < d + 11; ++digit)
        digits[digit] = 0;

    int i;
    long unsigned int digit;
    long unsigned int remainder;

    // Parallel region
    #pragma omp parallel for private(i, remainder, digit)
    for (i = 1; i <= n; ++i) {
        remainder = 1;
        for (digit = 0; digit < d + 11 && remainder; ++digit) {
            long unsigned int div = remainder / i;
            long unsigned int mod = remainder % i;
            #pragma omp atomic // critical section, only 1 thread at a time can do this so they do not step on each other
            digits[digit] += div;
            remainder = mod * 10;
        }
    }
    threadTime = omp_get_wtime() - start;                       // Get each threads finsh time
    printf("Thread %d finished in %.9g\n", tid, threadTime);    // Print thread time

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

    return digits; // Return pointer

} // end function()

int main(int argc, const char **argv) {

    int threads = omp_get_num_procs();  // Get the # of processors available
    omp_set_num_threads(threads);       // Sets the number of threads used for parallel 
    int i;                              // Counter
    double end;                         // End time

    if (argc != 3)
    {
	printf("usage: hps n d\n");
	printf("    n: value of N (Example: 5 => 1/1 + 1/2 + 1/3 + 1/4 + 1/5)\n");
	printf("    d: numbers of Digits (Example: 5 => 0,xxxxx) \n");
	exit(-1);
    }

    int n = atoi((char*)argv[1]);   // value of N
    int d = atoi((char*)argv[2]);	// numbers of digits

    long unsigned int *harmonicSum;
    harmonicSum = (long unsigned int *)malloc(sizeof(long unsigned int) * (d+11));

    //int output[d + 10];           // Array for output
    start = omp_get_wtime();        // Start the timer

    #pragma omp parallel
        harmonicSum = hpsOMP(d, n);

    end = omp_get_wtime() - start;  // End total timer and get results

    // printing fanciness ...
    printf("\nS(%d) = ", n);
    printf("%ld.", harmonicSum[0]);
    for (i = 1; i <= d; ++i) 
    {
	    printf("%ld",harmonicSum[i]);
    }
    printf(" to %d digits of precison.\n", d);
    printf("\n\tCalculated in %.9g seconds with %d threads.\n\n", end, threads);

    free(harmonicSum); // Free memory

    return 0;
} // end main()