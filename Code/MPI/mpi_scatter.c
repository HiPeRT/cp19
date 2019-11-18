#include <mpi.h>
#include <stdio.h>

#define N 4

int main (int argc, char* argv[])
{
  int id, p, n, i;
  int A[N], local_A;

  for(i=0; i<N; i++)
    A[i] = 100 + i;

  //Inizializzo la libreria MPI
  MPI_Init(&argc, &argv);
  //Richiedo il numero totale di processor elements
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  //Richiedo il mio ID tra questi
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  
  MPI_Scatter(A, 1, MPI_INT, &local_A, 1, MPI_INT, 0, MPI_COMM_WORLD);
//  MPI_Allreduce(&a, &b, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

  printf("%d local_A is: %d\n", id, local_A);
  
  //Chiudo la libreria
  MPI_Finalize();
  return 0;
}
