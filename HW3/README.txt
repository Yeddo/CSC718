/*--------------------------------------------------------------------------------------------
 *   Name:		    JB
 *   Class:		    CSC 718
 *   Professor:	    Dr. Yong Wang
 *   Assignment:	#3
 *   Due Date:	    16 November 2021
 *   File Name: 	README.txt
 *   Description:	Instructions for files
 *-------------------------------------------------------------------------------------------*/

# Twenty Five (25) files included:
	1 - Makefile
	2 - sieve1
    3 - sieve1.c
	4 - sieve2
    5 - sieve2.c
	6 - sieve3
    7 - sieve3.c
	8 - p1
    9 - p1.c
    10 - p2
    11 - p2.c
    12 - p3
    13 - p3.c
    14 - p4
	15 - p4.c
	16 - p1_omp
	17 - p1_omp.c
	18 - p2_omp
	19 - p2_omp.c
	20 - p3_omp
	21 - p3_omp.c
	22 - p4_omp
	23 - p4_omp.c
	24 - README.txt
	25 - running.txt

# NOTES -----------------------------------------------------------------------------------------------------------------------

	- Created all code in VS Code on Ubuntu/Focal Linux.
    - No need to specifiy threads for the openmp programs. The code will determine that for your system. I used int 
	threads = omp_get_num_procs(); and omp_set_num_threads(threads); to set the threads.

	- The instructor provided files for the assingment are included for convienence (sieve# ... n) .

# How to compile -----------------------------------------------------------------------------------------------------------------------

	- type "make"
	- or 
    - for OpenMP gcc -Wall -g3 -fopenmp p#_omp.c -o p#_omp
    - for OpenMPI mpicc -Wall -g3 sieve#.c -o sieve# -lm # Need -lm for <math> library
    - for serial program, gcc -Wall -g3 <program name>

# How to Execute -----------------------------------------------------------------------------------------------------------------------


# p1_omp ------------------------------------------------------------------------------------------------------------

# How to run p1_omp:
	- ./p1_omp

# Average run time of p1_omp:
	
	- 0.286s

# Expected output of p1_omp:
	- After running the program the following will be displayed in the terminal:
 
test@ubuntu:/mnt/hgfs/VM_SHARE/HW3$ ./p1_omp
Thread 8 finished in: 0.2535 seconds.
Thread 7 finished in: 0.2548 seconds.
Thread 0 finished in: 0.2555 seconds.
Thread 15 finished in: 0.2558 seconds.
Thread 11 finished in: 0.2684 seconds.
Thread 6 finished in: 0.2698 seconds.
Thread 5 finished in: 0.2715 seconds.
Thread 14 finished in: 0.2725 seconds.
Thread 3 finished in: 0.2825 seconds.
Thread 4 finished in: 0.2835 seconds.
Thread 2 finished in: 0.2837 seconds.
Thread 1 finished in: 0.2841 seconds.
Thread 9 finished in: 0.2847 seconds.
Thread 10 finished in: 0.2847 seconds.
Thread 13 finished in: 0.2848 seconds.
Thread 12 finished in: 0.286 seconds.
	pi is 3.14159265359 calculated in 0.286 seconds with 16 threads.

# p2_omp --------------------------------------------------------------------------------------------------------------

# How to run p2_omp:
	-  ./p2_omp

# Average run time of p2_omp:
	- 0.001874s

# Expected output of p2_omp:
	- After running the program the following will be displayed in the terminal:

est@ubuntu:/mnt/hgfs/VM_SHARE/HW3$ ./p2_omp
Thread 8 finished in: 0.00115 seconds.
Thread 15 finished in: 0.00115 seconds.
Thread 0 finished in: 0.00115 seconds.
Thread 7 finished in: 0.00115 seconds.
Thread 3 finished in: 0.00115 seconds.
Thread 6 finished in: 0.00115 seconds.
Thread 14 finished in: 0.00115 seconds.
Thread 10 finished in: 0.00115 seconds.
Thread 1 finished in: 0.00115 seconds.
Thread 11 finished in: 0.00115 seconds.
Thread 13 finished in: 0.00115 seconds.
Thread 2 finished in: 0.00115 seconds.
Thread 5 finished in: 0.00115 seconds.
Thread 4 finished in: 0.00115 seconds.
Thread 12 finished in: 0.00115 seconds.
Thread 9 finished in: 0.00115 seconds.
	Sum = 199999379657117505182169563136.000000 in 0.001874 seconds with 16 threads.


# p3_omp --------------------------------------------------------------------------------------------------------------------------


# How to run p3_omp:
	-  ./p3_omp

# Average run time of HW2.Q2_mpiPrimeConsecCount:
	- 0.35911592s


# Expected output of HW2.Q3_mpiPrimeGap:
	- After running the program the following will be displayed in the terminal:

 hread 4 finished in 0.358170351
Thread 14 finished in 0.358170786
Thread 6 finished in 0.358170841
Thread 15 finished in 0.358170796
Thread 12 finished in 0.358170316
Thread 0 finished in 0.358170296
Thread 5 finished in 0.358170806
Thread 11 finished in 0.358173176
Thread 3 finished in 0.358170786
Thread 13 finished in 0.358170841
Thread 8 finished in 0.358170816
Thread 7 finished in 0.358170351
Thread 10 finished in 0.358170276
Thread 2 finished in 0.358170306
Thread 1 finished in 0.358170816
Thread 9 finished in 0.358170316
	Sum = 329762680001713515003904.000000 calculated in 0.35911592 seconds with 16 threads.


# p4_omp -----------------------------------------------------------------------------------------------------------------------------


# How to run p4_omp:
	-  ./p4_omp

# Average run time of p4_omp
	- 0.019600573 w/670 COLUMNS 150/70 ROWS
	- 0.001438394s w/67 COLUMNS 15/7 ROWS

# Expected output of p4_omp:
	- After running the program the following will be displayed in the terminal:
	- NOTE: This was only 67 ROWS 15/7 COLUMNS for display purposes. The default 670 150/70 is very large and doesn't display nice.
	
test@ubuntu:/mnt/hgfs/VM_SHARE/HW3$ ./p4_omp
Thread 2 completed row 20
Thread 2 completed row 21
Thread 2 completed row 22
Thread 2 completed row 23
Thread 2 completed row 24
Thread 2 completed row 25
Thread 2 completed row 26
Thread 2 completed row 27
Thread 2 completed row 28
Thread 2 completed row 29
Thread 4 completed row 40
Thread 0 completed row 0
Thread 0 completed row 1
Thread 0 completed row 2
Thread 0 completed row 3
Thread 0 completed row 4
Thread 0 completed row 5
Thread 0 completed row 6
Thread 0 completed row 7
Thread 0 completed row 8
Thread 0 completed row 9
Thread 6 completed row 60
Thread 6 completed row 61
Thread 5 completed row 50
Thread 5 completed row 51
Thread 5 completed row 52
Thread 5 completed row 53
Thread 5 completed row 54
Thread 5 completed row 55
Thread 5 completed row 56
Thread 5 completed row 57
Thread 5 completed row 58
Thread 5 completed row 59
Thread 1 completed row 10
Thread 1 completed row 11
Thread 1 completed row 12
Thread 1 completed row 13
Thread 1 completed row 14
Thread 1 completed row 15
Thread 1 completed row 16
Thread 1 completed row 17
Thread 1 completed row 18
Thread 1 completed row 19
Thread 3 completed row 30
Thread 3 completed row 31
Thread 3 completed row 32
Thread 3 completed row 33
Thread 3 completed row 34
Thread 3 completed row 35
Thread 3 completed row 36
Thread 3 completed row 37
Thread 3 completed row 38
Thread 4 completed row 41
Thread 4 completed row 42
Thread 4 completed row 43
Thread 4 completed row 44
Thread 4 completed row 45
Thread 4 completed row 46
Thread 4 completed row 47
Thread 4 completed row 48
Thread 4 completed row 49
Thread 3 completed row 39

Thread 4 completed in 0.022738816 seconds
Thread 10 completed in 0.022751142 seconds
Thread 11 completed in 0.022799691 seconds
Thread 13 completed in 0.022820467 seconds
Thread 14 completed in 0.022739116 seconds
Thread 6 completed in 0.022738936 seconds
Thread 7 completed in 0.022739202 seconds
Thread 5 completed in 0.022739201 seconds
Thread 2 completed in 0.022739166 seconds
Thread 15 completed in 0.022739152 seconds
Thread 0 completed in 0.022739152 seconds
Thread 9 completed in 0.022761776 seconds
Thread 1 completed in 0.022738947 seconds
Thread 3 completed in 0.022770887 seconds
Thread 12 completed in 0.022773387 seconds
Thread 8 completed in 0.022775351 seconds

******************************************************
Result Matrix:
  0.00   819.00   1638.00   2457.00   3276.00   4095.00   4914.00   
  0.00   910.00   1820.00   2730.00   3640.00   4550.00   5460.00   
  0.00   1001.00   2002.00   3003.00   4004.00   5005.00   6006.00   
  0.00   1092.00   2184.00   3276.00   4368.00   5460.00   6552.00   
  0.00   1435.00   2870.00   4305.00   5740.00   7175.00   8610.00   
  0.00   1540.00   3080.00   4620.00   6160.00   7700.00   9240.00   
  0.00   1645.00   3290.00   4935.00   6580.00   8225.00   9870.00   
  0.00   1750.00   3500.00   5250.00   7000.00   8750.00   10500.00   
  0.00   1855.00   3710.00   5565.00   7420.00   9275.00   11130.00   
  0.00   1960.00   3920.00   5880.00   7840.00   9800.00   11760.00   
  0.00   2065.00   4130.00   6195.00   8260.00   10325.00   12390.00   
  0.00   2170.00   4340.00   6510.00   8680.00   10850.00   13020.00   
  0.00   2275.00   4550.00   6825.00   9100.00   11375.00   13650.00   
  0.00   2380.00   4760.00   7140.00   9520.00   11900.00   14280.00   
  0.00   2485.00   4970.00   7455.00   9940.00   12425.00   14910.00   
  0.00   2590.00   5180.00   7770.00   10360.00   12950.00   15540.00   
  0.00   2695.00   5390.00   8085.00   10780.00   13475.00   16170.00   
  0.00   2800.00   5600.00   8400.00   11200.00   14000.00   16800.00   
  0.00   2905.00   5810.00   8715.00   11620.00   14525.00   17430.00   
  0.00   3010.00   6020.00   9030.00   12040.00   15050.00   18060.00   
  0.00   2429.00   4858.00   7287.00   9716.00   12145.00   14574.00   
  0.00   2512.00   5024.00   7536.00   10048.00   12560.00   15072.00   
  0.00   2595.00   5190.00   7785.00   10380.00   12975.00   15570.00   
  0.00   2678.00   5356.00   8034.00   10712.00   13390.00   16068.00   
  0.00   2761.00   5522.00   8283.00   11044.00   13805.00   16566.00   
  0.00   2844.00   5688.00   8532.00   11376.00   14220.00   17064.00   
  0.00   2927.00   5854.00   8781.00   11708.00   14635.00   17562.00   
  0.00   3010.00   6020.00   9030.00   12040.00   15050.00   18060.00   
  0.00     0.00     0.00     0.00     0.00     0.00     0.00   
  0.00     0.00     0.00     0.00     0.00     0.00     0.00   
  0.00   4165.00   8330.00   12495.00   16660.00   20825.00   24990.00   
  0.00   4270.00   8540.00   12810.00   17080.00   21350.00   25620.00   
  0.00   4375.00   8750.00   13125.00   17500.00   21875.00   26250.00   
  0.00   4480.00   8960.00   13440.00   17920.00   22400.00   26880.00   
  0.00   4585.00   9170.00   13755.00   18340.00   22925.00   27510.00   
  0.00   4690.00   9380.00   14070.00   18760.00   23450.00   28140.00   
  0.00   4795.00   9590.00   14385.00   19180.00   23975.00   28770.00   
  0.00   4900.00   9800.00   14700.00   19600.00   24500.00   29400.00   
  0.00   5005.00   10010.00   15015.00   20020.00   25025.00   30030.00   
  0.00   5110.00   10220.00   15330.00   20440.00   25550.00   30660.00   
  0.00   4459.00   8918.00   13377.00   17836.00   22295.00   26754.00   
  0.00   5320.00   10640.00   15960.00   21280.00   26600.00   31920.00   
  0.00   5425.00   10850.00   16275.00   21700.00   27125.00   32550.00   
  0.00   5530.00   11060.00   16590.00   22120.00   27650.00   33180.00   
  0.00   5635.00   11270.00   16905.00   22540.00   28175.00   33810.00   
  0.00   5740.00   11480.00   17220.00   22960.00   28700.00   34440.00   
  0.00   5845.00   11690.00   17535.00   23380.00   29225.00   35070.00   
  0.00   5950.00   11900.00   17850.00   23800.00   29750.00   35700.00   
  0.00   6055.00   12110.00   18165.00   24220.00   30275.00   36330.00   
  0.00   6160.00   12320.00   18480.00   24640.00   30800.00   36960.00   
  0.00   6265.00   12530.00   18795.00   25060.00   31325.00   37590.00   
  0.00   6370.00   12740.00   19110.00   25480.00   31850.00   38220.00   
  0.00   6475.00   12950.00   19425.00   25900.00   32375.00   38850.00   
  0.00   6580.00   13160.00   19740.00   26320.00   32900.00   39480.00   
  0.00   6685.00   13370.00   20055.00   26740.00   33425.00   40110.00   
  0.00   6790.00   13580.00   20370.00   27160.00   33950.00   40740.00   
  0.00   6895.00   13790.00   20685.00   27580.00   34475.00   41370.00   
  0.00   7000.00   14000.00   21000.00   28000.00   35000.00   42000.00   
  0.00   7105.00   14210.00   21315.00   28420.00   35525.00   42630.00   
  0.00   7210.00   14420.00   21630.00   28840.00   36050.00   43260.00   
  0.00   7315.00   14630.00   21945.00   29260.00   36575.00   43890.00   
  0.00   7420.00   14840.00   22260.00   29680.00   37100.00   44520.00   
******************************************************
Done.
	Calculation complete in 0.023129247 seconds using 16 threads.





