#include <mpi.h> 
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
  int rank, size;
  int A;
  MPI_Status stat;
  //Inizializzo la libreria MPI
  MPI_Init(&argc, &argv);
  //Richiedo il numero totale di processor elements
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  //Richiedo il mio ID tra questi
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  if (rank == 0)
  {
    printf("Sono il processo %d, inserisci un numero: ",rank);
    fflush(stdout);
    scanf("%d",&A);
    MPI_Send(&A, 1, MPI_INT, 1, 15, MPI_COMM_WORLD);
  }
  
  if (rank==1)
  {
    MPI_Recv(&A, 1, MPI_INT, 0, 15, MPI_COMM_WORLD, &stat);
    printf("Sono il processo %d, ho ricevuto il valore %d\n", rank, A);
  }
  
  
  //Chiudo la libreria
  MPI_Finalize();
  return 0;
}
