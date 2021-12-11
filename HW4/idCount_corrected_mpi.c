/*--------------------------------------------------------------------------------------------
 *   Name:		    Jason Bisnette
 *   Class:		    CSC 718
 *   Professor:	    Dr. Yong Wang
 *   Assignment:	#4
 *   Due Date:	    07 December 2021
 *   File Name: 	idCount_mpi.c
 *   Description:
 *              OpenMPI Version:
 *              Programming Assignment: A small college wishes to assign unique identification 
 *              numbers to all of its present and future students. The administration is thinking 
 *              of using a given various constraints that have been placed on what is considered 
 *              to be an “acceptable” identifier. The “acceptable” identifier must meet the
 *              following constraints:
 *                 1.	The identifier is a six-digit combination of the numerals 0-9
 *                 2.	The first digit may not be a 0.
 *                 3.	Two consecutive digits may not be the same.
 *                 4.	The sum of the digits may not be 7, 11, or 13. 
 *
 *
 *   Notes:		
 *-------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int idCheck(int num) {

    char arr[6];                    // Holds number.
    // See: https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm
    sprintf(arr, "%u", num);        // Sends the # to an array. needs to be char!
    int sum = 0;                    // Holds sum value.

    // Walk through array. Need to stop at element 4 because the check is i+1.
    for(int i = 0; i < 5; i++) {    // 3. Two consecutive digits may not be the same.
        if(arr[i] == arr[i+1]) {
            return 0;               // Consecutive #s are the same.
        }

    }

    // Walk through array.
    for(int i = 0; i < 6; i++) { 
        sum += arr[i]-48;                               // Calculate sum. The code added the char value. It needs to be integer value (-48).
        if((sum == 7) || (sum == 11) || (sum == 13)) {  // 4. The sum of the digits may not be 7, 11, or 13.
            return 0;                                   // They = 7, 11, or 13
        }
    }

    return 1; // valid #

} // end idCheck()

int main(int argc, char *argv[]) {

    int count;          // Counter for valid IDs
    int N = 1000;        // Times to run work load. AKA, waste some time
    int id;             // Proccess id
    int proc;           // # of process
    int globalCount;    // Count after procs are reduced

    /* The following 2 varibles help satisfy the first two requirements:
            1. The identifier is a six-digit combination of the numerals 0-9
            2. The first digit may not be a 0. 
    */
    int start = 100000; // Start Value
    int end = 999999;   // End Value

    double sTime;
    double eTime;

    MPI_Init (&argc, &argv);        // Initialize the MPI environment
    MPI_Barrier(MPI_COMM_WORLD);    // Block/Process starting point
    sTime = -MPI_Wtime();           // Start timer here
    MPI_Comm_rank (MPI_COMM_WORLD, &proc);  // Get the # of the process 
    MPI_Comm_size(MPI_COMM_WORLD, &id);     // Get the id of the process

    /*
        The outter loop runs the inner loop N times to test parallization as the work is done
        pretty fast on a single processor.
    */
    for (int wasteTime = 0; wasteTime < N; wasteTime++) { 
      count = 0;                // Set counter variable here for  wasteTime intervals.
        // The for loop needs to be split up among processors
        for (int n = start + proc; n <= end; n += id) {
            if (idCheck(n)) {   // Call worker function
            count++;
            }
        }
    }

    eTime = sTime + MPI_Wtime();        // Get current proc time
    printf("Processor %d finished in : %.9g seconds.\n", proc, eTime);
    fflush (stdout);

    MPI_Reduce (&count, &globalCount, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); // Collect local count of valid #s
    sTime += MPI_Wtime();               // Turn off timer
    MPI_Finalize();                     // Finalize the MPI environment

    if (!proc) { // Print count of valid identifiers.
        printf("The number of valid unique identifiers is: %d\n"
        "\tCalculated in %.9g seconds.\n\n", globalCount, eTime);
        fflush (stdout);
     }

    return 0;

} // end main()
