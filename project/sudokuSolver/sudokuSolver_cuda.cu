/*-------------------------------------------------------------------------------------------------------------
 *   Name:		    Jason Bisnette
 *   Class:		    CSC 718
 *   Professor:	    Dr. Yong Wang
 *   Assignment:	Final Project
 *   Due Date:	    08 December 2021
 *   File Name: 	sudokuSolver_cuda.cu
 *   Description:
 *              CUDA Version:
 *              Programming Assignment: A simple Sudoku puzzle solver for a puzzle size(s) of 9 x 9. 
 *              This program uses a backtracking algorithm to complete Sudoku puzzles: https://bit.ly/3d3kGTL
 *
 *   Notes:		- Puzzle files are included in the sudokuBoards folder of varying sizes.
 *              
 *              - Blank spaces are annotated with 0s in the puzzle file.
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
 *              - Fill in the numbers from 1 - size exactly once in each row, column, and minigrid (sqrt(size))
 *               region.
 * 
 *              Backtracking termination conditions (Only 2):
 *              - The sudoku is already filled, meaning there is no white space.
 *              - There are no more empty spots left for the algorithm to check, and the current candidate
 *               does not reach the goal.
 *-----------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>   // pow()
#include <string.h>
#include <cuda_runtime.h>
#include <time.h>
#include <cuda.h>
#include <cuda_device_runtime_api.h>

#ifndef __CUDACC__
    #define __CUDACC__
#endif

// 9x9 Sudoku
#define N 9
#define MINIGRID_SIZE 3 // sqrt(N)
#define CELLS 81
#define ITERATIONS 18 // number of ITERATIONS to run Searh

// 16x16 Sudoku
//#define N 16
//#define MINIGRID_SIZE 4
//#define CELLS 256

/*
 * Max puzzles for allowed for tree. Maximum size for int is 2^30 otherwise overflow
 * May need to be adjusted for harder (less filled in) puzzles
 * Works for > 16 (worst case for 9x9 81 cell sudoku)
 * Might need to change to long or long long for larger more complicated puzzles but this will require
 * altering the data types to other functions.
*/
const int MAX_PUZZLES = pow(2,28);

// Reads in puzzle file to the 1D array : sudoku.
void readPuzzle(char *FileName, int *sudoku) {
    FILE * file = fopen(FileName, "r");

    if (file == NULL) {
        printf("File load fail!\n"); return;
    }

    char trash; // Holds first line in file to be used later for doing larger puzzles
    char num;  // Holds the puzzle lines after every read

    // Throw this away for now ...
    if (!fscanf(file, "%c\n", &trash)) { 
        printf("File loading error!\n");
        exit(-1);
    }

    // Read puzzle from the file
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!fscanf(file, "%c\n", &num)) {
                printf("File loading error!\n");
                exit(-1);
            }

            // Puts #s and 0s in the proper spot in array.
            if (num >= '1' && num <= 'N') { // If # > 0 put in array otherwise place the 0.
                // The idea here is the puzzle is stored in a 1D flat array instead of 2D. So to reference
                // row/column : row 1 is in element 0-8, row 2 is in element 9-17, etc...
                sudoku[i * N + j] = (int) (num - '0'); // removes null terminator and puts # in array
            } else { 
                sudoku[i * N + j] = 0; // Put a 0.
            }
        }
    }
} // end readPuzzle()

// Prints the puzzle to stdout
void printSudoku(int *sudoku) {
    for (int i = 0; i < N; i++) {
        if (i % MINIGRID_SIZE == 0) {
            printf("\n");
        }
        for (int j = 0; j < N; j++) {
            if (j % MINIGRID_SIZE == 0) {
            printf(" | ");
            }
            printf("%2d ", sudoku[i * N + j]);
        }
        printf(" |\n");
    }
    printf("\n\n");
} // end printSudoku()

// This function takes in a bool array and clears it to false.
__device__
void clearArray(bool *seenArray, int size) {
    
    for (int i = 0; i < size; i++) {
        seenArray[i] = false;
    }
} // end clearArray

 // Checks the puzzle to see if it is valid.
__device__
bool validBoard(const int *sudoku) {
    
    bool seen[N];           // Array of size N to track valid #s
    clearArray(seen, N);    // Clears array

    // Check rows. Rows are stored contiguously (1D array). To access row and col : sudoku[row * N + col]
    for (int row = 0; row < N; row++) {
        clearArray(seen, N);
        for (int col = 0; col < N; col++) {
            int valid = sudoku[row * N + col];
            if (valid != 0) {
                if (seen[valid - 1]) {
                    return false;
                } else {
                    seen[valid - 1] = true;
                }
            }
        }
    } // end row check

    // Check columns. Rows are stored contiguously (1D array). To access row and col : sudoku[row * N + col]
    for (int col = 0; col < N; col++) {
        clearArray(seen, N);

        for (int row = 0; row < N; row++) {
            int valid = sudoku[row * N + col];

            if (valid != 0) {
                if (seen[valid - 1]) {
                    return false;
                } else {
                    seen[valid - 1] = true;
                }
            }
        }
    } // end column check

    // Check minigrids
    for (int rowID = 0; rowID < MINIGRID_SIZE; rowID++) {
        for (int colID = 0; colID < MINIGRID_SIZE; colID++) {
            clearArray(seen, N);
            for (int row = 0; row < MINIGRID_SIZE; row++) {
                for (int col = 0; col < MINIGRID_SIZE; col++) {
                    int valid = sudoku[(rowID * MINIGRID_SIZE + row) * N + (colID * MINIGRID_SIZE + col)];
                    if (valid != 0) {
                        if (seen[valid - 1]) {
                            return false;
                        } else {
                            seen[valid-1] = true;
                        }
                    }
                }
            }
        }
    } // end minigrid check
    return true; // Valid board
} // end validBoard()

/**
 * changedIndex is between 0 and N * N - 1. Stores the index of the Sudoku that was changed
 * 
 * Assumes the Sudoku does not have the value at the index. 
 * 
 * Checks for validity for the new change.
  */
__device__
bool validBoard(const int *sudoku, int changedIndex) {

    int row = changedIndex / N;
    int col = changedIndex % N;

    // If index is less than 0, then default
    if (changedIndex < 0) {
        return validBoard(sudoku); // Call validboard(puzzle)
    }

    // Keep index between 1 and N (size of 1D of the sudoku)
    if ((sudoku[changedIndex] < 1) || (sudoku[changedIndex] > N)) {
        return false; // Not valid 
    }

    bool seen[N];           // Array for seen #s
    clearArray(seen, N);   // Create seenArray

    // Check rows. Rows are stored contiguously (1D array). To access row and col : sudoku[row * N + col]
    for (int i = 0; i < N; i++) {
        int valid = sudoku[row * N + i];
        if (valid != 0) {
            if (seen[valid - 1]) {
                return false;
            } else {
                seen[valid - 1] = true;
            }
        }
    } // end row check

    // Check columns. Rows are stored contiguously (1D array). To access row and col : sudoku[row * N + col]
    clearArray(seen, N);
    for (int j = 0; j < N; j++) {
        int valid = sudoku[j * N + col];
        if (valid != 0) {
            if (seen[valid - 1]) {
                return false;
            } else {
                seen[valid - 1] = true;
            }
        }
    } // end column check

    // Check minigrid. MINIGRID_SIZE is minigrid size or sqrt(N)
    int rowID = row / MINIGRID_SIZE; 
    int colID = col / MINIGRID_SIZE; 

    clearArray(seen, N); // Create seenArray

    // Moves within the minigrids
    for (int i = 0; i < MINIGRID_SIZE; i++) {
        for (int j = 0; j < MINIGRID_SIZE; j++) {
            int valid = sudoku[(rowID * MINIGRID_SIZE + i) * N + (colID * MINIGRID_SIZE + j)];
            if (valid != 0) {
                if (seen[valid - 1]) {
                    return false; // Not valid
                } else {
                    seen[valid - 1] = true;
                }
            }
        }
    } // end minigrid check
    return true; // Sudoku is valid
} // end validBoard() <- w/index

// Backtrack has each thread try to solve a different sudoku in the puzzle array.
__global__
void backtrack(int *puzzle,const int numBoards,int *emptySpaces,int *numEmptySpaces,int *finished,int *solvedSudoku) {

    int index = blockDim.x * blockIdx.x + threadIdx.x;
    int *currentPuzzle;         // Location for current puzzle being worked on
    int *currentEmptySpaces;    // Tracks location of empty spaces in currenly loaded puzzle
    int currentNumEmptySpaces;  // Tracks # of empty spaces in current puzzle

    // While more work to do.
    // Finished var is key to stopping the kernel so it does not iterate until end.
    while ((*finished == 0) && (index < numBoards)) {
    
        int emptyIndex = 0; // Set the emptyIndex to 0

        currentPuzzle = puzzle + index * CELLS;             // Gets current puzzle
        currentEmptySpaces = emptySpaces + index * CELLS;   // Gets current empty spaces
        // Each value stores the number of empty spaces in the corresponding sudoku.
        currentNumEmptySpaces = numEmptySpaces[index];      // Gets # of empty spaces for current puzzle

        // While there are still spots in the Sudoku that are empty do this
        while ((emptyIndex >= 0) && (emptyIndex < currentNumEmptySpaces)) {
            
            currentPuzzle[currentEmptySpaces[emptyIndex]]++; // Move to next empty spot

            // If not a valid board and all the #s are attemped just backtrack or just continue to next iteration
            if (!validBoard(currentPuzzle, currentEmptySpaces[emptyIndex])) {
                if (currentPuzzle[currentEmptySpaces[emptyIndex]] >= N) {
                    currentPuzzle[currentEmptySpaces[emptyIndex]] = 0;
                    emptyIndex--; // Backup
                }
            }
            else { // If the Sudoku is valid increment the emptyIndex and continue
                emptyIndex++; // Move forward
            }
        } 

        // Solution found, stop kernel and copy the results to the solveSodoku array
        if (emptyIndex == currentNumEmptySpaces) {
            *finished = 1; // <-- this stops the kernel
            for (int i = 0; i < N * N; i++) {
                solvedSudoku[i] = currentPuzzle[i]; // Copy current solved puzzle to solvedSudoku array
            }
        }
        index += gridDim.x * blockDim.x;
    }
} // end backtrack()

// Call backtrack kernel
void deviceBacktrack(const  int blocks,const  int threadsPerBlock,int *puzzle,const int numBoards, int *emptySpaces, int *numEmptySpaces, int *finished, int *solvedSudoku) {

    backtrack<<<blocks, threadsPerBlock>>>(puzzle, numBoards, emptySpaces, numEmptySpaces, finished, solvedSudoku);
} // end deviceBacktrack()


// This kernel takes old puzzles and finds all possible puzzles by filling in the empty spaces.
// puzzleIndex must start at zero!
// This is a breadth first search as it was easier than depth first to parallelize!
__global__
void deviceSearch(int *oldPuzzles,int *newPuzzles,int puzzleIndexReset,int *puzzleIndex,int *emptySpaces,int *emptyCount) {
    
    int index = blockIdx.x * blockDim.x + threadIdx.x;

    
    while (index < puzzleIndexReset) {
    
        int found = 0; // Set found to 0 to enter for loop

        // Find next empty position
        for (int i = (index * N * N); (i < (index * N * N) + N * N) && (found == 0); i++) {
            if (oldPuzzles[i] == 0) {               // Empty found!
                found = 1;                          // Set to 1 and if not found set to 0
                int location = (i - N * N * index);   // Set location in array
                int row = (location / N);             // Get proper row
                int col = (location % N);             // Get proper column
                
                // Find correct # to fit in location
                for (int num = 1; num <= N; num++) {
                    
                    int fits = 1; // Set to fits and if num does not fit change to 0

                    // Check rows
                    for (int numRow = 0; numRow < N; numRow++) { 
                        if (oldPuzzles[numRow * N + col + N * N * index] == num) {
                            fits = 0;
                        }
                    }
                    
                    // Check columns
                    for (int numCol = 0; numCol < N; numCol++) {  
                        if (oldPuzzles[row * N + numCol + N * N * index] == num) {
                            fits = 0; // Does not fit
                        }
                    }

                    // Check minigrids
                    for (int numRow = MINIGRID_SIZE * (row / MINIGRID_SIZE); numRow < MINIGRID_SIZE; numRow++) {
                        for (int numCol = MINIGRID_SIZE * (col / MINIGRID_SIZE); numCol < MINIGRID_SIZE; numCol++) {
                            if (oldPuzzles[numRow * N + numCol + N * N * index] == num) {
                                fits = 0; // Does not fit
                            }
                        }
                    }

                    // If it made it this far num fits by default
                    if (fits == 1) {
                        
                        // Move to the next Puzzle (prevent race condition)
                        int nextPuzzleIndex = atomicAdd(puzzleIndex, 1); 
                        int emptiesIndex = 0;  // Reset emptiesIndex

                        // Copy puzzles, old -> new
                        for (int numRow = 0; numRow < N; numRow++) {
                            for (int numCol = 0; numCol < N; numCol++) {
                                newPuzzles[nextPuzzleIndex * CELLS + numRow * N + numCol] = oldPuzzles[index * CELLS + numRow * N + numCol];
                                if (oldPuzzles[index * CELLS + numRow * N + numCol] == 0 && (numRow != row || numCol != col)) {

                                    emptySpaces[emptiesIndex + CELLS * nextPuzzleIndex] = numRow * N + numCol;
                                    emptiesIndex++; // Move to the next spot
                                }
                            }
                        }
                        // Set empties count/index for new puzzle
                        emptyCount[nextPuzzleIndex] = emptiesIndex;
                        // Put number in puzzle at proper location
                        newPuzzles[nextPuzzleIndex * CELLS + row * N + col] = num; 
                    }
                }
            }
        }
        index += blockDim.x * gridDim.x;
    }
} // end deviceSearch()


void callSearchKernel(const int blocks,const int threadsPerBlock,int *oldPuzzles,int *newPuzzles,int puzzleIndexReset,int *puzzleIndex,int *emptySpaces,int *emptyCount) {
    
    deviceSearch<<<blocks, threadsPerBlock>>>(oldPuzzles, newPuzzles, puzzleIndexReset, puzzleIndex, emptySpaces, emptyCount);
} // end callSearchKernel()

int main(int argc, char *argv[]) {
    
    if (argc != 4){
        printf("\n\tERROR: Incorrect # of args.\n"
        "\t\t\tSyntax: ./sudokuSolver <threads per block> <max number of blocks> <puzzleFile>\n\n");
        exit(-1);
    }

    clock_t time;               // clock struct from <time.h>
    double timeTaken;           // End time variable
    int *sudoku;                // Sudoku puzzle 1D array
    /*
     *  newPuzzles and oldPuzzles contain multiple puzzles in a 1D array. To access a specific puzzle within 
     *  the array use newPuzzle[board# * N * N + row * N + column]
    */
    int *newPuzzles;            // New puzzles after search
    int *oldPuzzles;            // The previous puzzle
    int *emptySpaces;           // Location of empty spaces
    int *emptyCount;            // Number of empty spaces
    int *puzzleIndex;           // Location of new puzzle
    int puzzleIndexReset = 1;   // Need to set puzzleIndex to zero every iteration so use this to track them
    int *deviceFinished;        // Bool var for solution found
    int *deviceSolved;          // To store solvedSudoku Sudoku from device
    int *solvedSudoku ;         // Stores solved Sudoku
    int threadsPerBlock = atoi(argv[1]); // Holds user input # threads from arg and convert to int
    int maxBlocks = atoi(argv[2]);       // Holds user input maxblocks from arg and convert to int
    char* filename = argv[3];   // Filename of the starting sudoku
    int puzzleCount;             // number of puzzle after a call to search function

    time = clock(); // Start timer

    // Allocate space for puzzle
    if((sudoku = (int*)malloc((N * N) * sizeof(int))) == NULL) { 
        printf("Error: Not enough memory.\n");
        exit(-1); // Exit/error cannot aquire memory
    }

    readPuzzle(filename, sudoku); // Read in sudoku from file

    // Allocate space for solved puzzle
    if((solvedSudoku = (int*)malloc((N * N) * sizeof(int))) == NULL) { 
        printf("Error: Not enough memory.\n");
        exit(-1); // Exit/error cannot aquire memory
    }

    memset(solvedSudoku, 0, (N * N) * sizeof(int)); // Fill solvedSudoku array with 0s

    printf("\nPuzzle file -> %s is : %d x %d\n\n", argv[3], N, N); // Puzzle name and size of puzzle 
    printf("Loaded Sudoku Puzzle: \n");
    printSudoku(sudoku); // Print sudoku from file before solution

    cudaMalloc(&emptySpaces, MAX_PUZZLES * sizeof(int));                 // Allocate memory
    cudaMalloc(&emptyCount, (MAX_PUZZLES / CELLS + 1) * sizeof(int));    // Allocate memory
    cudaMalloc(&newPuzzles, MAX_PUZZLES * sizeof(int));                  // Allocate memory
    cudaMemset(newPuzzles, 0, MAX_PUZZLES * sizeof(int));                // Fill with 0s
    cudaMalloc(&oldPuzzles, MAX_PUZZLES * sizeof(int));                  // Allocate memory
    cudaMemset(oldPuzzles, 0, MAX_PUZZLES * sizeof(int));                // Fill with 0s
    // copy the sudoku to oldPuzzles on device. (cudaMemcpyHostToDevice = 1)
    cudaMemcpy(oldPuzzles, sudoku, N * N * sizeof(int), cudaMemcpyHostToDevice); 
    cudaMalloc(&puzzleIndex, sizeof(int));                       // Allocate memory
    cudaMemset(puzzleIndex, 0, sizeof(int));                     // Make puzzleIndex 0

    // Call the kernel to generate puzzle
    callSearchKernel(maxBlocks,threadsPerBlock,oldPuzzles,newPuzzles,puzzleIndexReset,puzzleIndex,emptySpaces,emptyCount);

    // Loop through ITERATIONS to generate more puzzles in the binary tree
    for (int i = 0; i < ITERATIONS; i++) {

        // Copy puzzleIndex to puzzleCount 
        cudaMemcpy(&puzzleCount, puzzleIndex, sizeof(int), cudaMemcpyDeviceToHost);
        cudaMemset(puzzleIndex, 0, sizeof(int)); // Change puzzleIndex to 0

        // Left
        if (i % 2 == 0) {
            callSearchKernel(maxBlocks,threadsPerBlock,newPuzzles,oldPuzzles,puzzleCount,puzzleIndex,emptySpaces,emptyCount);
        }
        // Right
        else {
            callSearchKernel(maxBlocks,threadsPerBlock,oldPuzzles,newPuzzles,puzzleCount,puzzleIndex,emptySpaces,emptyCount);
        }
    }

    // Copy puzzleIndex from device to puzzleCount on host
    cudaMemcpy(&puzzleCount, puzzleIndex, sizeof(int), cudaMemcpyDeviceToHost);
    cudaMalloc(&deviceFinished, sizeof(int));           // Allocate memory
    cudaMemset(deviceFinished, 0, sizeof(int));         // Fill with 0s
    cudaMalloc(&deviceSolved, (N * N) * sizeof(int));   // Allocate memory
    // Copy sudoku from host to deviceSolved on device
    cudaMemcpy(deviceSolved, sudoku, (N * N) * sizeof(int), cudaMemcpyHostToDevice);

    // If odd # of ITERATIONS then send to oldPuzzle instead of newPuzzle
    if (ITERATIONS % 2 == 1) {
        newPuzzles = oldPuzzles;
    }

    // Call backtracking algorithm
    deviceBacktrack(maxBlocks,threadsPerBlock,newPuzzles,puzzleCount,emptySpaces,emptyCount,deviceFinished,deviceSolved);

    // Puzzle soved! Copy deviceSolved from device to solvedSudoku on host
    cudaMemcpy(solvedSudoku, deviceSolved, (N * N) * sizeof(int), cudaMemcpyDeviceToHost);

    time = clock() - time;                      // Stop timer
    timeTaken = ((double)time)/CLOCKS_PER_SEC;  // Calculate time

    // Print results
    printf("\nPuzzle Solved: \n");
    printSudoku(solvedSudoku);
    printf("\t\tThe %d x %d puzzle %s was solved in %f seconds\n\n", N, N, argv[3], timeTaken);

    // Free all allocated memory
    free(sudoku);
    free(solvedSudoku);
    cudaFree(emptySpaces);
    cudaFree(emptyCount);
    cudaFree(newPuzzles);
    cudaFree(oldPuzzles);
    cudaFree(puzzleIndex);
    cudaFree(deviceFinished);
    cudaFree(deviceSolved);

    return 0; 
} // end main()