/*-------------------------------------------------------------------------------------------------------------
 *   Name:		    Jason Bisnette
 *   Class:		    CSC 718
 *   Professor:	    minigrid. Yong Wang
 *   Assignment:	Final Project
 *   Due Date:	    08 December 2021
 *   File Name: 	sudokuSolver_serial.c
 *   Description:
 *              Serial Version:
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
#include <string.h>     // strcpy()
#include <math.h>       // sqrt()
#include <time.h>

// Reads puzzle from file and stores in 2D array
int **readPuzzle(FILE *file, int *size) {

    int **sudoku;     // Sudoku puzzle 2D array
    
    /* 
        The first line in the puzzle file contains the size of the grid 
        (e.g., 9 x 9 would have the # 9 on the first line).
        The following lines contain the grid.
    */
    fscanf(file,"%d",size); // Read first line of puzzle file and store in size

    if((sudoku = (int**)malloc(*size * sizeof(int*))) == NULL) { // Make space
        return NULL; // If cannot aquire memory
    }

    // Read puzzle file into 2D array
    for(int row = 0; row < *size; row++) {
        if((sudoku[row] = (int*)malloc(*size * sizeof(int))) == NULL) { // Make space
            return NULL; // If cannot aquire memory
        }
        for(int col = 0; col < *size; col++) {
            // Read next line and put values in 2D array. **fscanf disregards whitespace
            fscanf(file,"%d",&sudoku[row][col]);
        }
    }
    return sudoku; // Return the array puzzle to solve
} // end readPuzzle()

// This prints dynamically sized grid lines for Sudoku puzzle and prints the puzzle to stdout
void printSudoku(int **sudoku, int size) {

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


// This solver uses the backtracking algorithm
int solveSudoku(int **sudoku,int size) {

    int row;        // Outer/Row Loop Counter
    int col;        // Inner/Column Loop Counter
    int i;          // Loop Counter
    int num;        // Variable for trying numbers to fit in a cell
    int empty = 0;  // Bool variable for finding empty spots (0s)
    int fits;       // Bool variable for if a number fits in a cell or not
    int gridRow;    // Minigrid Outer loop counter
    int gridCol;    // Minigrid Inner loop counter
    int rowStart;    // Minigrid Outer lop start condition
    int rowEnd;      // Minigrid Outer loop end condition
    int colStart;    // Minigrid Inner loop start condition
    int colEnd;      // Minigrid Inner loop end condition
    int minigrid;    // Variable for the minigrid size. A 9x9 sudoku has a 3x3 minigrid size.

    //Look for an empty cell (the next zero (0))
    for(row = 0; row < size && !empty; row++) {
        for(col = 0;col < size && !empty; col++) {
            if(sudoku[row][col] == 0) {     // Empty spot found
                empty = 1;                  // Stops loop  
            }
        }
    }

    // set row and col to correct spot because loop will increment on found 0 before stopping
    row--; 
    col--; 

    // No 0s found. Sudoku filled in.
    if(!empty) {
        return 1;
    }

    minigrid = (int)sqrt(size); // get the size of minigrid
    
    /*
    Find a number that fits this cell (1 - size per the rules. 9 x 9 would be 1 - 9, 
    16 x 16 would be 1 - 16, etc).
    */
    for(num = 1; num <= size; num++) {
        fits = 1;   // Set to 1/true
        // Check if it fits horizontally (row)
        for(i = 0; i < size && fits; i++) {
            if(sudoku[row][i] == num) {
                fits = 0; // Does not fit
            }
        }
        //Check if it fits vertically (column)
        for(i = 0; i < size && fits; i++) {
            if(sudoku[i][col] == num) {
                fits = 0; // Does not fit
            }
        }

        //Check if it fits in a minigrid (3x3, etc)
        rowStart = floor((row/minigrid) * minigrid); // Find starting row position of minigrid
        rowEnd = rowStart + minigrid;                // Find end row postion of minigrid
        colStart = floor((col/minigrid) * minigrid); // Find starting column position of minigrid
        colEnd = colStart + minigrid;                // Find end column position of minigrid
        //rowStart = row - (row % minigrid);           // Find starting row position of minigrid
        //rowEnd = row - (row % minigrid) + minigrid;  // Find end row postion of minigrid
        //colStart = col-(col % minigrid);             // Find starting column position of minigrid
        //colEnd = col - (col % minigrid) + minigrid;  // Find end column position of minigrid

        for(gridRow = rowStart; gridRow < rowEnd && fits; gridRow++) {
            for(gridCol = colStart; gridCol < colEnd && fits; gridCol++) {
                if(sudoku[gridRow][gridCol] == num) {
                    fits = 0; // Does not fit
                }
            }
        }

        // If number is correct put in puzzle and recursive call solveSudoku() until complete
        if(fits) {
            sudoku[row][col] = num;         //Place number and solve the other cells
            if(solveSudoku(sudoku, size)) { // ** This is the core backtracking part **
                return 1;                   // If success return 1
            } else {
                sudoku[row][col] = 0;       // Cannot proceed with this solution try a new number
            }
        }
    } 
  return 0; //Out of options
} // end solveSudoku()

// Free 2D pointer
void freeSudoku(int **sudoku, int size) {

    for(int row = 0; row < size; row++) {
        free(sudoku[row]); // Free rows
    }
    free(sudoku); // Free top level
} // end freeSudoku()

int main(int argc, char const *argv[]) {
    
    clock_t time;       // Time from <time.h>
    double timeTaken;   // End time variable
    int **sudoku;       // Sudoku board 2D array
    int size;           // Holds size of sudoku
    FILE *file;         // File pointer
   
    // Make sure there are enough arguments
    if(argc != 2) {
        printf("\n\tError: Incorrect # of args.\n"
        "\t\t\tSyntax: ./sudokuSolver_serial <puzzleFile>\n\n");
        return 0;
    }

    // Open file and check for errors
    if((file = fopen(argv[1],"r")) == NULL) {
        printf("Error: Could not open this file : %s \n", argv[1]);
        return 0;
    }

    time = clock(); // Start timer

    // Read puzzle file and check for memory allocation errors
    if((sudoku = readPuzzle(file, &size)) == NULL) {
        printf("Error:Not enough memory.\n");
        return 0;
    }

    fclose(file); // Close file

    // Print puzzle before 
    printf("\nPuzzle file -> %s is : %d x %d\n\n", argv[1], size, size); // size of puzzle (1st line of file) 
    printf("Loaded Sudoku Puzzle: \n");
    printSudoku(sudoku, size);

    // Solve and print puzzle
    if(solveSudoku(sudoku, size)) {
        time = clock() - time;                      // Stop timer
        timeTaken = ((double)time)/CLOCKS_PER_SEC;  // Calculate time
        // Print results
        printf("\nSolved sudoku : \n");
        printSudoku(sudoku, size);
        freeSudoku(sudoku, size);
        printf("\t\tCompleted in %f seconds on 1 processor.\n\n", timeTaken);
    } else {
        time = clock() - time;                      // Stop timer
        timeTaken = ((double)time)/CLOCKS_PER_SEC;  // Calculate time
        // Cannot solve this puzzle and print results
        printf("No solution for this puzzle.\n"); 
        freeSudoku(sudoku, size);
        printf("\t\tCompleted in %f seconds on 1 processor.\n\n", timeTaken);
    }
    return 0;
} // end main()