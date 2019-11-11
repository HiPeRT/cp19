#include <mpi.h> 
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
  int rank, size;
  //Inizializzo la libreria MPI
  MPI_Init(&argc, &argv);
  //Richiedo il numero totale di processor elements
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  //Richiedo il mio ID tra questi
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  printf("CIAO! Sono il processo %d di %d\n", rank, size);
  //for(int i=0; i< 100000000000; i++);

  //Chiudo la libreria
  MPI_Finalize();
  return 0;
}
