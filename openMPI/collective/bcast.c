#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
  int numprocs, rank, namelen;
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  char buffer[10];

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Get_processor_name(processor_name, &namelen);

  int root = 0;

  if (rank == root) {
    strcpy(buffer, "Jack");
  }

  MPI_Bcast(buffer, 10, MPI_CHAR, root, MPI_COMM_WORLD);

  printf("Process %d on %s : hello %s \n", rank, processor_name, buffer);

  MPI_Finalize();
}

