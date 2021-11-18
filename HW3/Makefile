#/*------------------------------------------------------------------------------
# *   Name:		    Jason Bisnette
# *   Class:		CSC 718
# *   Professor:	Dr. Yong Wang
# *   Assignment:	#3
# *   Due Date:	    16 November 2021
# *   File Name: 	Makefile
# *   Description:	Makefile for compiling assignment source code to executables.
# *-------------------------------------------------------------------------------*/

CC = gcc
CFLAGS = -Wall -g3 -fopenmp
TARGET1=sieve1
TARGET2=sieve2
TARGET3=sieve3
TARGET4=p1_omp
TARGET5=p2_omp
TARGET6=p3_omp
TARGET7=p4_omp
TARGET8=p1
TARGET9=p2
TARGET10=p3
TARGET11=p4

executables = $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4) $(TARGET5) $(TARGET6) $(TARGET7) $(TARGET8) $(TARGET9) $(TARGET10) $(TARGET11)

all : $(executables)

# executable construction ----------------------------------

$(TARGET1) : $(TARGET1).c
	mpicc -Wall -g3 $(TARGET1).c -o $(TARGET1) -lm

$(TARGET2) : $(TARGET2).c
	mpicc -Wall -g3 $(TARGET2).c -o $(TARGET2) -lm

$(TARGET3) : $(TARGET3).c
	mpicc -Wall -g3 $(TARGET3).c -o $(TARGET3) -lm

$(TARGET4) : $(TARGET4).c
	$(CC) $(CFLAGS) $(TARGET4).c -o $(TARGET4)

$(TARGET5) : $(TARGET5).c
	$(CC) $(CFLAGS) $(TARGET5).c -o $(TARGET5)

$(TARGET6) : $(TARGET6).c
	$(CC) $(CFLAGS) $(TARGET6).c -o $(TARGET6)

$(TARGET7) : $(TARGET7).c
	$(CC) $(CFLAGS) $(TARGET7).c -o $(TARGET7)

$(TARGET8) : $(TARGET8).c
	$(CC) $(CFLAGS) $(TARGET8).c -o $(TARGET8)

$(TARGET9) : $(TARGET9).c
	$(CC) $(CFLAGS) $(TARGET9).c -o $(TARGET9)

$(TARGET10) : $(TARGET10).c
	$(CC) $(CFLAGS) $(TARGET10).c -o $(TARGET10)

$(TARGET11) : $(TARGET11).c
	$(CC) $(CFLAGS) $(TARGET11).c -o $(TARGET11)
	
# file cleanup ---------------------------------------------

.PHONY : clean clean_o clean_exe

clean :
	rm *.o $(executables) -f

clean_o :
	rm *.o -f

clean_exe :
	rm $(executables) -f
