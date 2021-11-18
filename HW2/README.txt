/*--------------------------------------------------------------------------------------------
 *   Name:		    Jason Bisnette
 *   Class:		    CSC 718
 *   Professor:	    Dr. Yong Wang
 *   Assignment:	#2
 *   Due Date:	    21 October 2021
 *   File Name: 	README.txt
 *   Description:	Instructions for files
 *-------------------------------------------------------------------------------------------*/

# Fourteen (16) files included:
	1 - Makefile
	2 - HW2.Q1_seqPrimeConsecCount
    3 - HW2.Q1_seqPrimeConsecCount.c
	4 - HW2.Q2_mpiPrimeConsecCount
    5 - HW2.Q2_mpiPrimeConsecCount.c
	6 - HW2.Q3_mpiPrimeGap
    7 - HW2.Q3_mpiPrimeGap.c
	8 - HW2.Q4.mpiRectPI
    9 - HW2.Q4.mpiRectPI.c
    10 - splitNums.c
    11 - primeCheck.c
    12 - splitNums.h
    13 - primeCheck.h
    14 - Performance_Chart.pdf
	15 - README.txt
	16 - machinefile.dsu


# NOTES -----------------------------------------------------------------------------------------------------------------------


primeCheck.c has 2 different methods for determining primes. The default method is called the 6k +/- 1 primality test/algorithm.
It is a much faster way to determine if a number is prime. To use the other method comment out the code desired and uncomment the 
slower method.


# How to compile -----------------------------------------------------------------------------------------------------------------------


(Note: The math library must be linked in when building the executable. in Linux/Unix, just add -lm to mpicc command. (mpicc test.c -o test -lm)
	- type "make"
	- For HW2.Q1_seqPrimeConsecCount : "mpicc -g -Wall HW2.Q1_seqPrimeConsecCount.c primeCheck.c -o HW2.Q1_seqPrimeConsecCount -lm"
    - For HW2.Q2-3 : "mpicc -g -Wall HW2.Q#*.c splitNums.c primeCheck.c -o HW2.Q#* -lm"
    - For HW2.Q4.mpiRectPI : "mpicc -g -Wall HW2.Q4.mpiRectPI.c -o HW2.Q4.mpiRectPI"


# How to Execute -----------------------------------------------------------------------------------------------------------------------


# HW2.Q1_seqPrimeConsecCount ------------------------------------------------------------------------------------------------------------

# How to run HW2.Q1_seqPrimeConsecCount (Sequential):
	- ./HW2.Q1_seqPrimeConsecCount

# Average run time of HW2.Q1_seqPrimeConsecCount:
	- I ran my  HW2.Q1_seqPrimeConsecCount from the command line with the linux time command:
		time ./HW2.Q1_seqPrimeConsecCount
	- See Included Performace_Chart.pdf

# Expected output of HW2.Q1_seqPrimeConsecCount:
	- After running the program the following will be displayed in the terminal:
 
 * The number of times there are consecutive odd numbers between 2 and 1000000 are prime is: 8169


real	0m0.151s
user	0m0.084s
sys	0m0.000s


# HW2.Q2_mpiPrimeConsecCount --------------------------------------------------------------------------------------------------------------


# How to run HW2.Q2_mpiPrimeConsecCount (openMPI):
	-  mpirun -np 4 -machinefile machinefile.dsu ./HW2.Q2_mpiPrimeConsecCount

# Average run time of HW2.Q2_mpiPrimeConsecCount:
	- See Included Performace_Chart.pdf


# Expected output of HW2.Q2_mpiPrimeConsecCount:
	- After running the program the following will be displayed in the terminal:

 Processor: 2  finished at:   0.022861 seconds
 The number of times consecutive odd numbers between 500001 and 750002 are prime is: 1849

 Processor: 1  finished at:   0.040133 seconds
 The number of times consecutive odd numbers between 250001 and 500002 are prime is: 1977

 Processor: 0  finished at:   0.038052 seconds
 The number of times consecutive odd numbers between 1 and 250002 are prime is: 2588

 Processor: 3  finished at:   0.061350 seconds
 The number of times consecutive odd numbers between 750001 and 1000000 are prime is: 1755

 * The number of times consecutive odd numbers between 2 and 1000000 are prime is: 8169

 ** Total elapsed time:   0.060185 **


# HW2.Q3_mpiPrimeGap --------------------------------------------------------------------------------------------------------------------------


# How to run HW2.Q3_mpiPrimeGap (openMPI):
	-  mpirun -np 4 -machinefile machinefile.dsu ./HW2.Q3_mpiPrimeGap

# Average run time of HW2.Q2_mpiPrimeConsecCount:
	- See Included Performace_Chart.pdf


# Expected output of HW2.Q3_mpiPrimeGap:
	- After running the program the following will be displayed in the terminal:

 Processor: 3 Finished at: 0.024054766 seconds.
 The largest gap between prime numbers in the set from 750001 to 1000000 is:  100

 Processor: 2 Finished at: 0.024759531 seconds.
 The largest gap between prime numbers in the set from 500001 to 750000 is:  98

 Processor: 0 Finished at: 0.029292345 seconds.
 The largest gap between prime numbers in the set from 1 to 250000 is:  86

 Processor: 1 Finished at: 0.036051750 seconds.
 The largest gap between prime numbers in the set from 250001 to 500000 is:  114

 * The largest gap between prime numbers from 2 to 1000000 is:  114

 ** Total elapsed time:   0.036584 **


# HW2.Q4.mpiRectPI -----------------------------------------------------------------------------------------------------------------------------


# How to run HW2.Q4.mpiRectPI (openMPI):
	-  mpirun -np 4 -machinefile machinefile.dsu ./HW2.Q4.mpiRectPI

# Average run time of HW2.Q2_mpiRectPI
	- See Included Performace_Chart.pdf

# Expected output of HW2.Q4.mpiRectPI:
	- After running the program the following will be displayed in the terminal:
	
 Processor: 2  finished at:   0.003711 seconds
 Area: 0.78539791340

 Processor: 3  finished at:   0.004422 seconds
 Area: 0.78539741340

 Processor: 0  finished at:   0.006128 seconds
 Area: 0.78539891340

 Processor: 1  finished at:   0.006881 seconds
 Area: 0.78539841340

 * The value from summing the rectangles is:  3.14159265359

 ** Total elapsed time:   0.007275 **

	
