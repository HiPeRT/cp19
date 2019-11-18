#include <mpi.h>
#include <stdio.h>

#define N 4

int main (int argc, char* argv[])
{
  int id, p, n, i, a, b;
  //Inizializzo la libreria MPI
  MPI_Init(&argc, &argv);
  //Richiedo il numero totale di processor elements
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  //Richiedo il mio ID tra questi
  MPI_Comm_rank(MPI_COMM_WORLD, &id);

  a = 1;  

  MPI_Reduce(&a, &b, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
//  MPI_Allreduce(&a, &b, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

  printf("%d b is: %d\n", id, b);
  
  //Chiudo la libreria
  MPI_Finalize();
  return 0;
}
