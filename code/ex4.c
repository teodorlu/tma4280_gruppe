#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"

/*
	Variables used in the program
*/
Vector vector;


/*
   Function for testing the OpenMP lib
 */
void openMpTest() {
  #pragma omp parallel for schedule(static)
  for (int i = 0; i < 4; ++i)
  {
    printf("OpenMP Test. Iteration %d\n", i);
  }
}

void fillVector_ex4(Vector x) {
  int i;
  for(i=0; i<x->len; ++i)
    x->data[i*x->stride] = 1.0 / i*i;
}

void setupVector(int n) {
	vector = createVector(n);
	fillVector_ex4(vector);
}


void mpiTest(int rank) {

}


int main(int argc, char** argv)
{
  openMpTest();

  // MPI Testing
  int rank, size, i, tag;
  MPI_Status status;
  char message[20];

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  tag = 100;

  if (rank == 0) {
    strcpy(message, "Hello world!");
    for (i=1; i < size; ++i)
      MPI_Send(message, 13, MPI_CHAR, i, tag, MPI_COMM_WORLD);
  } else
    MPI_Recv(message, 13, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);

  printf("process %d: %s\n", rank, message);

  MPI_Finalize();

  return 0;
}
