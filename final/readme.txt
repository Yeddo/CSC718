/*--------------------------------------------------------------------------------------------
 *   Name:		    Jason Bisnette
 *   Class:		    CSC 718
 *   Professor:	    Dr. Yong Wang
 *   Assignment:	Final Exam
 *   Due Date:	    14 December 2021
 *   File Name: 	README.txt
 *   Description:	Instructions for files
 *-------------------------------------------------------------------------------------------*/

# Nine (9) files included:
	1 - Makefile
	2 - hps
    3 - hps.c
	4 - hps_omp
    5 - hps_omp.c
	6 - hps_mpi
    7 - hps_mpi.c
	8 - README.txt
	9 - machinefile.dsu


# NOTES -----------------------------------------------------------------------------------------------------------------------


# How to compile -----------------------------------------------------------------------------------------------------------------------

	- type "make"
	- or 
    - for OpenMP gcc -Wall -g3 -fopenmp hps_omp.c -o hps_omp
    - for OpenMPI mpicc -Wall -g3 hps_mpi.c -o hps_mpi
    - for serial program, gcc -Wall -g3 hps.c -o hps

# How to Execute -----------------------------------------------------------------------------------------------------------------------

# hps :

# How to run hps:
	- time ./hps 1000000 100

# Average run time of hps :

	real	0m0.825s
	user	0m0.824s
	sys	0m0.000s

# Expected output of hps :

14.3927267228657236313811274931885876766448000137443116534184330458129585075179950035682981759472191007

real	0m0.825s
user	0m0.824s
sys	0m0.000s


------------------------------------------

# hps_omp :

	**This program automatically finds the number of threads it can run with and uses that value**

# How to run hps_omp:
	- ./hps_omp 1000000 100

# Average run time of hps_omp

	- With 4 threads : 	1.02235045 seconds

# Expected output of hps_omp

Thread 3 finished in 0.844460427
Thread 2 finished in 0.848916812
Thread 0 finished in 0.901387787
Thread 1 finished in 0.902301314

S(1000000) = 14.3927267228657236313811274931885876766448000137443116534184330458129585075179950035682981759472191007 to 100 digits of precison.

	Calculated in 0.902320709 seconds with 4 threads.


------------------------------------------

# hps_mpi :

# How to run hps_mpi :
	- mpirun -np 4 -machinefile -machiefileinfo.dsu ./hps_mpi 1000000 100

# Average run time of hps_mpi : 

	- The average run time on the Rushmore cluster with 4 CPUs is : 23.2527661 seconds


# Expected output of hps_mpi :

 Processor: 1  finished in: 0.214437650 seconds
 Processor: 3  finished in: 0.218578074 seconds
 Processor: 0  finished in: 0.218586264 seconds
 Processor: 2  finished in: 0.218581949 seconds

S(1000000) = 14.3927267228657236313811274931885876766448000137443116534184330458129585075179950035682981759472191007 to 100 digits of precison.

	Calculated in 0.218671583 seconds using 4 processors.
