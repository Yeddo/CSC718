/*-------------------------------------------------------------------------------------------------------------
 *   Due Date:	    08 December 2021
 *   File Name: 	sudokuSolver_omp.c
 *   Description:
 *              OpenMP Version:
 *              Programming Assignment: A simple Sudoku puzzle solver for a puzzle size(s) of n x n. This program
 * 				uses the backtracking algorithm to complete Sudoku puzzles: https://bit.ly/3d3kGTL
 *
 *   Notes:		- Needs to be compiled with the -lm flag for the math libraries/sqrt function.
 *              - Puzzle files are included in the sudokuBoards folder of varying sizes.
 *              
 *              -The board files need to have the size of the board on the first line and 
 *              blank spaces are filled with 0s.
 *   
 *              Ex (9x9 puzzle):                            
 *              9                                           
 *              0 0 0 2 6 0 7 0 1                           
 *              6 8 0 0 7 0 0 9 0                           
 *              1 9 0 0 0 4 5 0 0                           
 *              8 2 0 1 0 0 0 4 0                           
 *              0 0 4 6 0 2 9 0 0                           
 *              0 5 0 0 0 3 0 2 8                           
 *              0 0 9 3 0 0 0 7 4                           
 *              0 4 0 0 5 0 0 3 6                           
 *              7 0 3 0 1 8 0 0 0                           
 *              
 *              For Sudoku, a candidate is valid if the following constraints are true:
 *              - Each row has unique numbers from 1 – size or empty spaces.
 *              - Each column has unique numbers from 1 – size or empty spaces.
 *              - Each sub-grid (minigrid) of 1 – size has the numbers 1 - size or empty spaces.
 * 
 *              Goal (only 1 to win):
 *              - Fill in the numbers from 1-size exactly once in each row, column, and minigrid (sqrt(size))
 *               region.
 * 
 *              Backtracking termination conditions (Only 2):
 *              - The board is already filled, meaning there is no white space.
 *              - There are no more empty spots left for the algorithm to check, and the current candidate
 *               does not reach the goal.
 *-----------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcat()
#include <math.h>   // sqrt()
#include <omp.h>    // OpenMP

double start;       // Start time variable

// This prints dynamically sized grid lines for Sudoku puzzle and prints the puzzle to stdout
void printSudoku(int size, int sudoku[size][size]) {

	int minigrid = (int)sqrt(size); // get the size of minigrid | <math.h>

    for(int row = 0; row < size; row++) {
        if ((row % minigrid) == 0) {
			printf("\n");
        }
        for(int col = 0; col < size; col++) {
            if((col % minigrid) == 0) { 				// Prints middle sudoku lines for the minigrids
                printf(" | "); 
            }
            printf("%2d ",sudoku[row][col]);			// Prints puzzle
        }
        printf(" |\n"); 								// Prints right side of sudoku
    }
    printf("\n\n");
} // end printSudoku()

// Free 2D pointer
void freeSudoku(int **sudoku, int size) {

    for(int row = 0; row < size; row++) {
        free(sudoku[row]); // Free rows
    }
    free(sudoku); // Free top level
} // end freeSudoku()

// Check if number fits in row
int checkRow(int size, int sudoku[size][size], int row, int num) {

    for (int col = 0; col < size; col++) {
        if (sudoku[row][col] == num) {
            return 1;
        }
    }
    return 0;
} // end

// Check if number fits in column
int checkColumn(int size, int sudoku[size][size], int col, int num) {

    for (int row = 0; row < size; row++) {
        if (sudoku[row][col] == num) {
            return 1;
        }
    }

    return 0;
} // end

// Check if number fits in minigrid
int checkMinigrid(int size, int sudoku[size][size], int startRow, int startCol, int num) {

    int minigrid = (int)sqrt(size); // get the size of minigrid | <math.h>

    for (int row = 0; row < minigrid; row++) {
        for (int col = 0; col < minigrid; col++) {
            if (sudoku[row + startRow][col + startCol] == num) {
                return 1;
            } 
        }
    }
    return 0;
} // end 

// Checks if number exists anywhere else in specific row/column/minigrid
int checkAll(int size, int sudoku[size][size], int row, int col, int num) {

    int minigridSize = (int)sqrt(size); // get the size of minigrid | <math.h>
    
    if (!checkRow(size, sudoku, row, num) 
    && !checkColumn(size, sudoku, col, num) 
    && !checkMinigrid(size, sudoku, row - (row % minigridSize), col - (col % minigridSize), num)) {
        return 1; // Does not exist anywhere else
    } else {
        return 0; // Number is seen elsewhere
    }
}

int findEmpty(int size, int sudoku[size][size], int *row, int *col) {

    for (*row = 0; *row < size; (*row)++) {
        for (*col = 0; *col < size; (*col)++) {
            if (sudoku[*row][*col] == 0) {
                return 1; // Empty spot found
            }
        }
    }
    return 0; // Not empty
}

// This solver uses the backtracking algorithm
int solveSudoku(int size, int sudoku[size][size], int threashold, int threads) {
    
    int row = 0;
    int col = 0;

    if (!findEmpty(size, sudoku, &row, &col)) { // If the cell is not empty do not do anything
        return 1; 
    }

    //#pragma omp nowait schedule(dynamic, 1)
    #pragma omp taskgroup                               // Wait on child tasks
    for (int num = 1; num <= size; num++ ) {            // Walk through valid numbers 1 through puzzle size   
        if (checkAll(size, sudoku, row, col, num)) {    // Check if the number fits
            // Parallel task, specify each data variable! (first private & shared), w/final tasking
            #pragma omp task default(none) firstprivate(sudoku, row, col, num, threashold) shared(start, size, threads) final(threashold>1)
            {			
				int sudokuCopy[size][size];	// Array to hold copy of puzzle	
				memcpy(sudokuCopy,sudoku,(size*size)*sizeof(int));	// Make a copy of the original puzzle			                
				
                sudokuCopy[row][col] = num;  // # to try in position 

                if(solveSudoku(size, sudokuCopy, threashold+1, threads)) {  // Check if puzzle solved
                    double end = omp_get_wtime();                           // Stop timer
                    //#pragma omp taskwait
                    printf("\nSolved sudoku : \n");
                    printSudoku(size, sudokuCopy);                          // Print solved puzzle
                    double time_spent = end - start;                        // Calculate elapsed time
                    // Print results
                    printf("\tPuzzled solved in %f seconds utilizting %d threads\n\n",time_spent, threads);
                    exit(0); // Done                    
                }
            }               // End omp task()                            
        } 
    }                       // If here try new number until num <= size
    #pragma omp taskwait    // Wait for completion of any children of current task
    return 0;               // Tried all nums
} // end solveSudoku()

int main(int argc, char *argv[]) {

    int threads = omp_get_num_procs();  // Get the # of processors available
    omp_set_num_threads(threads);       // Sets the number of threads used for parallel regions
    FILE *file;                         // File pointer
    int size;                           // Holds size of puzzle
        
    //Make sure there are enough arguments
    if(argc != 2) {
        printf("\n\tError: Incorrect # of args.\n"
        "\t\t\tSyntax: ./sudokuSolver_mpi <puzzleFile>\n\n");
        return 0;
    }
    
    if((file = fopen(argv[1],"r")) == NULL) {  //Open file and check for errors
        printf("Error: Could not open this file : %s \n", argv[1]);
        return 0;
    }   

    fscanf(file, "%d", &size);  // Read first line of puzzle file and store in size
        
    int sudoku[size][size];     // Declare 2D array of size x size to hold puzzle

    // Read in puzzle from file
    for (int row = 0; row < size; row++) { 
        for (int col = 0; col < size; col++) { 
            // Read next line and put values in 2d array. **fscanf disregards whitespace
            fscanf(file, "%d", &sudoku[row][col]);
        }
    }

    fclose(file);   // Close puzzle file

    printf("\nPuzzle file -> %s is : %d x %d\n\n", argv[1], size, size); // size of puzzle (1st line of file)  
        
    start = omp_get_wtime();        // Start the timer

    printf("Loaded Sudoku Puzzle: \n");
    printSudoku(size, sudoku);

    #pragma omp parallel default(none) shared(sudoku, size, threads) num_threads(threads)
    { // begin parallel region
	    //#pragma omp single nowait
        #pragma omp master
	    {
		    solveSudoku(size, sudoku, 1, threads);  
	    }
    } // end parallel region	
    return 0;   
} // end main()
