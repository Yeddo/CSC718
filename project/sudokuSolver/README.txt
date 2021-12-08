/*--------------------------------------------------------------------------------------------
 *   Name:		    Jason Bisnette
 *   Class:		    CSC 718
 *   Professor:	    Dr. Yong Wang
 *   Assignment:	Project
 *   Due Date:	    08 December 2021
 *   File Name: 	README.txt
 *   Description:	Instructions for files
 *-------------------------------------------------------------------------------------------*/

# Twenty Nine (9) files included:
	1 - Makefile
	2 - README.txt
    3 - sudokuSolver_serial.c
	4 - sudokuSolver_serial
    5 - sudokuSolver_omp.c
	6 - sudokuSolver_omp
    7 - sudokuSolver_cuda.cu
    8 - sudokuSolver_cuda
    9 - sudokuPuzzles/      <-- folder containing various puzzles/sizes

# NOTES -----------------------------------------------------------------------------------------------------------------------

	- Created all code in VS Code on Ubuntu/Focal Linux. 
    - All will compile on Ubuntu w/appropriate packages, namely CUDA (sudo apt install nvidia-cuda-toolkit).

    - Serial version and OpenMP versions tested on Ubuntu/Focal Linux. These will run any n x n dimension 
    puzzle.

    - CUDA version ran on DSU  Amazon Web Services (AWS) neuron environment. This will only work with
    9 x 9 puzzles.

    - No need to specifiy threads for the openmp version. The code will determine that for your system. 
    I used int threads = omp_get_num_procs(); and omp_set_num_threads(threads); to set the threads.

	- These programs use a backtracking algorithm to complete Sudoku puzzles: https://bit.ly/3d3kGTL.

# How to compile -----------------------------------------------------------------------------------------------------------------------

	- type "make"
	- or 
    - for serial program, gcc -Wall -g3 sudokuSolver_serial.c -o sudokuSolver_serial -lm
    - for OpenMP gcc -Wall -g3 -fopenmp sudokuSolver_omp.c -o sudokuSolver_omp -lm
    - for CUDA program, nvcc sudokuSolver_cuda.cu -o sudokuSolver_cuda -lm -arch=sm_35 -g -G

# How to Execute -----------------------------------------------------------------------------------------------------------------------


# sudokuSolver_serial ------------------------------------------------------------------------------------------------------------

# How to run p1_omp:
	- ./sudokuSolver <puzzleFile>

# Average run time of sudokuSolver_serial:
	
    - 9x9:
    Easiest: 0m0.004 seconds
    Medium: 0m0.006 seconds
    Hard: 0m0.025 seconds
    Diabolical: 0m0.549 seconds
    Worst case: 0m25.065 seconds

    - 16x16
    Easiest: 0m0.942 seconds
    Medium: ran for 40+ min and was still going. Stopped for time’s sake.
    Hardest: ran too long and the medium went for 40+ min so I did not continue for time’s sake.

    - 25x25
    Easy: 0m10.866 seconds
    Hard: ran too long so I did not continue for time’s sake.

    - 64x64
    Easy: 0m5.349 seconds

# Expected output of sudokuSolver_serial:
	- After running the program the following will be displayed in the terminal:

Puzzle file -> testBoards/9x9/diabolical.txt is : 9 x 9

Loaded Sudoku Puzzle: 

 |  0  0  0  |  0  3  7  |  6  0  0  |
 |  0  0  0  |  6  0  0  |  0  9  0  |
 |  0  0  8  |  0  0  0  |  0  0  4  |

 |  0  9  0  |  0  0  0  |  0  0  1  |
 |  6  0  0  |  0  0  0  |  0  0  9  |
 |  3  0  0  |  0  0  0  |  0  4  0  |

 |  7  0  0  |  0  0  0  |  8  0  0  |
 |  0  1  0  |  0  0  9  |  0  0  0  |
 |  0  0  2  |  5  4  0  |  0  0  0  |



Solved sudoku : 

 |  9  5  4  |  1  3  7  |  6  8  2  |
 |  2  7  3  |  6  8  4  |  1  9  5  |
 |  1  6  8  |  2  9  5  |  7  3  4  |

 |  4  9  5  |  7  2  8  |  3  6  1  |
 |  6  8  1  |  4  5  3  |  2  7  9  |
 |  3  2  7  |  9  6  1  |  5  4  8  |

 |  7  4  9  |  3  1  2  |  8  5  6  |
 |  5  1  6  |  8  7  9  |  4  2  3  |
 |  8  3  2  |  5  4  6  |  9  1  7  |


		Completed in 0.537238 seconds on 1 processor.


# sudokuSolver_omp --------------------------------------------------------------------------------------------------------------

# How to run sudokuSolver_omp:
	-  ./sudokSolver_omp

# Average run time of sudokuSolver_omp:
	- 9x9
    Easiest: 0.000205 seconds
    Medium: 0.002219 seconds
    Hard: 0.011838 seconds
    Diabolical: 0.078208 seconds
    Worst case: 0.757406 seconds

    - 16x16
    Easy: 0.000641 seconds
    Medium: 0.000553 seconds
    Hard: 34.530307 seconds

    - 25x25
    Easy: 0.000517 seconds
    Hard: 0.000927 seconds

    - 64x64
    Easy: 0.003575 seconds

# Expected output of sudokuSolver_omp:
	- After running the program the following will be displayed in the terminal:

Puzzle file -> testBoards/testPuzz.txt is : 9 x 9

Loaded Sudoku Puzzle: 

 |  0  0  0  |  2  6  0  |  7  0  1  |
 |  6  8  0  |  0  7  0  |  0  9  0  |
 |  1  9  0  |  0  0  4  |  5  0  0  |

 |  8  2  0  |  1  0  0  |  0  4  0  |
 |  0  0  4  |  6  0  2  |  9  0  0  |
 |  0  5  0  |  0  0  3  |  0  2  8  |

 |  0  0  9  |  3  0  0  |  0  7  4  |
 |  0  4  0  |  0  5  0  |  0  3  6  |
 |  7  0  3  |  0  1  8  |  0  0  0  |



Solved sudoku : 

 |  4  3  5  |  2  6  9  |  7  8  1  |
 |  6  8  2  |  5  7  1  |  4  9  3  |
 |  1  9  7  |  8  3  4  |  5  6  2  |

 |  8  2  6  |  1  9  5  |  3  4  7  |
 |  3  7  4  |  6  8  2  |  9  1  5  |
 |  9  5  1  |  7  4  3  |  6  2  8  |

 |  5  1  9  |  3  2  6  |  8  7  4  |
 |  2  4  8  |  9  5  7  |  1  3  6  |
 |  7  6  3  |  4  1  8  |  2  5  9  |


	Puzzled solved in 0.000425 seconds utilizting 4 threads


# sudokuSolver_cuda --------------------------------------------------------------------------------------------------------------------------

# How to run sudokuSolver_mpi:
	-  ./sudokuSolver_cuda <threadPerBlock> <maxBlocks> <puzzleFile>
    - ex: ./sudokuSolver_cuda 1024 512 <puzzleFile>
    - ex: ./sudokuSolver_cuds 512 256 <puzzleFile>

# Average run time:
    - 9x9:
    Easiest: 0m0.391 seconds
    Medium: 0m0.833 seconds
    Hard: 0m1.151 seconds
    Diabolical: 0m2.476 seconds
    Worst case: 67m21.954 seconds


# Expected output of sudokuSolver_cuda:
	- After running the program the following will be displayed in the terminal:

Puzzle file -> ../easy.txt is : 9 x 9

Loaded Sudoku Puzzle:

 |  0  2  6  |  0  0  0  |  8  1  0  |
 |  3  0  0  |  7  0  8  |  0  0  6  |
 |  4  0  0  |  0  5  0  |  0  0  7  |

 |  0  5  0  |  1  0  7  |  0  9  0  |
 |  0  0  3  |  9  0  5  |  1  0  0  |
 |  0  4  0  |  3  0  2  |  0  5  0  |

 |  1  0  0  |  0  3  0  |  0  0  2  |
 |  5  0  0  |  2  0  4  |  0  0  9  |
 |  0  3  8  |  0  0  0  |  4  6  0  |



Puzzle Solved:

 |  7  2  6  |  4  9  3  |  8  1  5  |
 |  3  1  5  |  7  2  8  |  9  4  6  |
 |  4  8  9  |  6  5  1  |  2  3  7  |

 |  8  5  2  |  1  4  7  |  6  9  3  |
 |  6  7  3  |  9  8  5  |  1  2  4  |
 |  9  4  1  |  3  6  2  |  7  5  8  |

 |  1  9  4  |  8  3  6  |  5  7  2  |
 |  5  6  7  |  2  1  4  |  3  8  9  |
 |  2  3  8  |  5  7  9  |  4  6  1  |


                The 9 x 9 puzzle ../easy.txt was solved in 0.396347 seconds

