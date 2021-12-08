#/*------------------------------------------------------------------------------
# *   Name:		    Jason Bisnette
# *   Class:		CSC 718
# *   Professor:	Dr. Yong Wang
# *   Assignment:	Project
# *   Due Date:	    08 December 2021
# *   File Name: 	Makefile
# *   Description:	Makefile for compiling assignment source code to executables.
# *-------------------------------------------------------------------------------*/

CC = gcc
GPU = nvcc
CFLAGS = -Wall -g3
TARGET1=sudokuSolver_serial
TARGET2=sudokuSolver_omp
TARGET3=sudokuSolver_cuda

executables = $(TARGET1) $(TARGET2) $(TARGET3)

all : $(executables)

# executable construction ----------------------------------

$(TARGET1) : $(TARGET1).c
	$(CC) $(CFLAGS) $(TARGET1).c -Wall -o $(TARGET1) -lm

$(TARGET2) : $(TARGET2).c
	$(CC) $(CFLAGS) -Wall -fopenmp $(TARGET2).c -o $(TARGET2) -lm

$(TARGET3) : $(TARGET3).cu
	$(GPU) $(TARGET3).cu -o $(TARGET3) -lm -arch=sm_35 -g -G

# file cleanup ---------------------------------------------

.PHONY : clean clean_o clean_exe

clean :
	rm *.o $(executables) -f

clean_o :
	rm *.o -f

clean_exe :
	rm $(executables) -f
