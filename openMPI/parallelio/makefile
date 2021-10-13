EXECS=wr_at
MPICC?=mpicc

all: ${EXECS}

wr_at : wr_at.c
	${MPICC} -o wr_at wr_at.c

clean:
	rm ${EXECS}
