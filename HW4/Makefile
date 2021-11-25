#/*------------------------------------------------------------------------------
# *   Name:		    Jason Bisnette
# *   Class:		CSC 718
# *   Professor:	Dr. Yong Wang
# *   Assignment:	#4
# *   Due Date:	    07 December 2021
# *   File Name: 	Makefile
# *   Description:	Makefile for compiling assignment source code to executables.
# *-------------------------------------------------------------------------------*/

CC = gcc
CC2 = mpicc
CFLAGS = -Wall -g3
TARGET1=idCount_serial
TARGET2=idCount_omp
TARGET3=idCount_mpi

executables = $(TARGET1) $(TARGET2) $(TARGET3)

all : $(executables)

# executable construction ----------------------------------

$(TARGET1) : $(TARGET1).c
	$(CC) $(CFLAGS) $(TARGET1).c -o $(TARGET1)

$(TARGET2) : $(TARGET2).c
	$(CC) $(CFLAGS) -fopenmp $(TARGET2).c -o $(TARGET2)

$(TARGET3) : $(TARGET3).c
	$(CC2) $(CFLAGS) $(TARGET3).c -o $(TARGET3)


# file cleanup ---------------------------------------------

.PHONY : clean clean_o clean_exe

clean :
	rm *.o $(executables) -f

clean_o :
	rm *.o -f

clean_exe :
	rm $(executables) -f
