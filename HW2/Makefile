#/*------------------------------------------------------------------------------
# *   Name:		    Jason Bisnette
# *   Class:		CSC 718
# *   Professor:	Dr. Yong Wang
# *   Assignment:	#2
# *   Due Date:	    
# *   File Name: 	Makefile
# *   Description:	Makefile for compiling assignment source code to executables.
# *-------------------------------------------------------------------------------*/

CC = mpicc
CFLAGS = -Wall -g3
# The math library must be linked in when building the executable. in Linux/Unix, just add -lm to mpicc command. (mpicc test.c -o test -lm)
TARGET1=HW2.Q1_seqPrimeConsecCount
TARGET2=HW2.Q2_mpiPrimeConsecCount
TARGET3=HW2.Q3_mpiPrimeGap
TARGET4=HW2.Q4_mpiRectPI
TARGET5=splitNums.c
TARGET6=primeCheck.c
TARGET7=splitNums.h
TARGET8=primeCheck.h

executables = $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4)

all : $(executables)

# executable construction ----------------------------------

$(TARGET1) : $(TARGET1).c
	$(CC) $(CFLAGS) $(TARGET1).c $(TARGET6) -o $(TARGET1) -lm

$(TARGET2) : $(TARGET2).c
	$(CC) $(CFLAGS) $(TARGET2).c $(TARGET5) $(TARGET6) -o $(TARGET2) -lm

$(TARGET3) : $(TARGET3).c
	$(CC) $(CFLAGS) $(TARGET3).c $(TARGET5) $(TARGET6) -o $(TARGET3) -lm

$(TARGET4) : $(TARGET4).c
	$(CC) $(CFLAGS) $(TARGET4).c -o $(TARGET4)
	

# file cleanup ---------------------------------------------

.PHONY : clean clean_o clean_exe

clean :
	rm *.o $(executables) -f

clean_o :
	rm *.o -f

clean_exe :
	rm $(executables) -f
