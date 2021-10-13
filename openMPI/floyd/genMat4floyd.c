/*
 *	generates matrix for floyd programs
 *
 *	Andrea Di Blas, November 2004
 */

#define		MAX_DIST	10
#define		INFTY		((int) 1 << (sizeof(int) * 8 - 3))
#define		MAX_RAND	(((unsigned)1 << 31) - 1)

#include	<stdio.h>
#include	<stdlib.h>

/******************************************************************************/
int		main(int argc, char *argv[])
{	int			i, j;
	int			n;
	FILE		*fp;
	unsigned	seed;
	int			*Astorage;
	int			**A;
	double		r;		/* matrix density */
	int 		x;

	if(argc != 5)
	{	fprintf(stderr, "\nUsage: genMat4floyd <n> <r> <outfile> <seed>");
		fprintf(stderr, "\nWhere nxn is the size of the matrix into outfile");
		fprintf(stderr, "\n      r is the edge density, and");
		fprintf(stderr, "\n   seed is for the random number gen");
		fprintf(stderr, "\n");
		exit(1);
	}

	n = atoi(argv[1]);
	r = atof(argv[2]);

	if((fp = fopen(argv[3], "w")) == NULL)
	{	fprintf(stderr, "\n*** can't write file %s ***\n", argv[2]);
		exit(1);
	}
	
	seed = (unsigned)atoi(argv[4]);

	srandom(seed);

	/* write array dimensions n and n */
	fwrite(&n, sizeof(int), 1, fp);
	fwrite(&n, sizeof(int), 1, fp);

	if((Astorage = (int *)malloc(n * n * sizeof(int))) == NULL)
	{	fprintf(stderr, "\n*** out of memory ***\n");
		exit(2);
	}

	if((A = (int **)malloc(n * sizeof(int *))) == NULL)
	{	fprintf(stderr, "\n*** out of memory ***\n");
		exit(2);
	}

	/* initialize array handle */
	for(i = 0; i < n; ++i)
		A[i] = &Astorage[i * n];

	/* set all values */
	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j)
		{	x = (int)((double)MAX_DIST / r * (double)random() / (double)MAX_RAND);
			if(x == 0)
				x = 1;
			A[i][j]  = x <= MAX_DIST ? x : INFTY;
//			A[i][j]  = 48 + (49 << 8) + (50 << 16) + (51 << 24);
		}
	
	/* set diagonal to 0 */
	for(i = 0; i < n; ++i)
		A[i][i] = 0;

	/* write to file */
	fwrite(Astorage, sizeof(int), n * n, fp);

	fclose(fp);
	return(0);

}
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
