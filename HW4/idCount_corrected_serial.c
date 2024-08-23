/*--------------------------------------------------------------------------------------------
 *   Name:		    JB
 *   Class:		    CSC 718
 *   Professor:	    Dr. Yong Wang
 *   Assignment:	#4
 *   Due Date:	    07 December 2021
 *   File Name: 	idCount_serial.c
 *   Description:
 *              Serial Version:
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

// Begin main()
int main() {

    int count;          // Counter for valid IDs
    int N = 1000;          // Times to run work load. AKA, waste some time.
    
    /* The following varibles help satisfy the first two requirements:
            1. The identifier is a six-digit combination of the numerals 0-9
            2. The first digit may not be a 0. 
    */
    int start = 100000; // Start Value
    int end = 999999;   // End Value

    /*
        The outter loop runs the inner loop N times to test parallization as the work is done
        pretty fast on a single processor.
    */
    for (int wasteTime = 0; wasteTime < N; wasteTime++) { 
      count = 0;                // Set counter variable here for  wasteTime intervals.
        for (int n = start; n <= end; n++) {
            if (idCheck(n)) {   // Call worker function
            count++;
            }
       }
    }

    // Print count of valid identifiers.
    printf("The number of valid unique identifiers is: %d\n", count);
   
return 0;

} // end main()
