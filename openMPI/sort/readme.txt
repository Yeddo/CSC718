
There are three sample programs:

quicksort.c: sequential quick sort;
qsort.c: parallel quick sort;
bsort.c: parallel bubble sort;

Both qsort and bsort requires an input data file including unsorted number list. A sample file, infile, is included too. The first number is the total number in the list and followed by unsorted number list.

qsort.c - Parallel sorting algorithm based on quicksort
	compile: mpicc -Wall -O -o qsort qsort.c
	run:     mpirun -np num_procs qsort in_file out_file

bsort.c - Parallel sorting algorithm based on bubblesort
	compile: mpicc -Wall -O -o bsort bsort.c
	run:     mpirun -np num_procs bsort in_file out_file
