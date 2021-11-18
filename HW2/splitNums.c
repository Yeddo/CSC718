/*-------------------------------------------------------------------------------------
 *   Name:		    Jason Bisnette
 *   Class:		    CSC 718
 *   Professor:	    Dr. Yong Wang
 *   Assignment:	#2
 *   Due Date:	    21 October 2021
 *   File Name: 	splitNums.c
 *   Description:	
 *              Breaks the numbers from 1 to limit into evenly sized groups depending on
 *              the number of processors; *first_num and *last_num are the smallest and 
 *              largest values of the processor group.
 *-----------------------------------------------------------------------------------*/

#include <mpi.h>

void splitNums(int proc, int id, int limit, int *first_num, int *last_num) {

    *first_num = ((proc * limit) / id) + 1;  // Calculate smallest number per process
    *last_num = ((proc + 1) * limit) / id;   // Calculate largest number per process

     
    if (((*first_num) % 2) == 0) {           // if first number of group is even
	    (*first_num)++;                      // move to first odd number in group
    }
} // End splitNums()