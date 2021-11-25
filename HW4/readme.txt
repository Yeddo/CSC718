/*--------------------------------------------------------------------------------------------
 *   Name:		    Jason Bisnette
 *   Class:		    CSC 718
 *   Professor:	    Dr. Yong Wang
 *   Assignment:	#4
 *   Due Date:	    07 December 2021
 *   File Name: 	README.txt
 *   Description:	Instructions for files
 *-------------------------------------------------------------------------------------------*/

# Nine (9) files included:
	1 - Makefile
	2 - idCount_serial
    3 - idCount_serial.c
	4 - idCount_omp
    5 - idCount_omp.c
	6 - idCount_mpi
    7 - idCount_mpi.c
	8 - README.txt
	9 - machinefile.dsu


# NOTES -----------------------------------------------------------------------------------------------------------------------

    - I added a loop to the work being done in each of the programs. This is due to if finishing quickly in serial. The loop
	effectively just runs the set of numbers over and over N times. You can change the N variable to any number. For this 
	assignment I used 1000 times as the baseline.

# How to compile -----------------------------------------------------------------------------------------------------------------------

	- type "make"
	- or 
    - for OpenMP gcc -Wall -g3 -fopenmp idCount_omp.c -o idCount_omp
    - for OpenMPI mpicc -Wall -g3 idCount_mpi.c -o idCount_mpi
    - for serial program, gcc -Wall -g3 <program name>

# How to Execute -----------------------------------------------------------------------------------------------------------------------

# idCount_serial :

# How to run idCount_serial:
	- ./idCount_serial

# Average run time of idCount_serial :

	real	1m12.325s
	user	1m2.158s
	sys		0m4.968s

# Expected output of idCount_serial :

test@ubuntu:/mnt/hgfs/VM_SHARE/hw4$ time ./idCount_serial
The number of valid unique identifiers is: 531441

real	1m12.325s
user	1m2.158s
sys		0m4.968s

------------------------------------------

# idCount_omp :

	**This program automatically finds the number of threads it can run with and uses that value**

# How to run idCount_omp:
	- ./idCount_omp

# Average run time of idCount_omp

	- With 4 threads : 	18.9514896 seconds
	- With 16 threads : 6.89820549 seconds

# Expected output of idCount_omp

est@ubuntu:/mnt/hgfs/VM_SHARE/hw4$ ./idCount_omp
Thread 10 finished in : 6.81622455 seconds.
Thread 0 finished in : 6.81930664 seconds.
Thread 11 finished in : 6.82464219 seconds.
Thread 4 finished in : 6.82817579 seconds.
Thread 8 finished in : 6.83226939 seconds.
Thread 7 finished in : 6.83823158 seconds.
Thread 2 finished in : 6.83973536 seconds.
Thread 6 finished in : 6.8405992 seconds.
Thread 5 finished in : 6.85219111 seconds.
Thread 13 finished in : 6.85294602 seconds.
Thread 15 finished in : 6.87594744 seconds.
Thread 1 finished in : 6.87916558 seconds.
Thread 14 finished in : 6.88755104 seconds.
Thread 12 finished in : 6.88812199 seconds.
Thread 3 finished in : 6.88897232 seconds.
Thread 9 finished in : 6.89815412 seconds.

The number of valid unique identifiers is: 531441
	Calculated in 6.89820549 seconds utilizing 16 threads.


------------------------------------------

# idCount_mpi :

# How to run idCount_mpi :
	- mpirun -np 4 -machinefile -machiefileinfo.dsu ./idCount_mpi

# Average run time of idCount_mpi : 

	- The average run time on the Rushmore cluster with 4 CPUs is : 23.2527661 seconds
	- The average run time on my virtual machine with 16 CPUs is : 6.65341965 seconds

# Expected output of idCount_mpi :

test@ubuntu:/mnt/hgfs/VM_SHARE/hw4$ mpirun -np 16 ./idCount_mpi
Processor 15 finished in : 6.5237379 seconds.
Processor 7 finished in : 6.52894265 seconds.
Processor 1 finished in : 6.5695469 seconds.
Processor 12 finished in : 6.60879278 seconds.
Processor 9 finished in : 6.6221806 seconds.
Processor 8 finished in : 6.65206295 seconds.
Processor 0 finished in : 6.65341965 seconds.
Processor 3 finished in : 6.65756241 seconds.
Processor 14 finished in : 6.6677201 seconds.
Processor 6 finished in : 6.72223291 seconds.
Processor 5 finished in : 6.75262816 seconds.
Processor 4 finished in : 6.76298383 seconds.
Processor 11 finished in : 6.8142628 seconds.
Processor 10 finished in : 6.82609177 seconds.
Processor 2 finished in : 6.9355314 seconds.
Processor 13 finished in : 6.97436169 seconds.
The number of valid unique identifiers is: 531441
	Calculated in 6.65341965 seconds.