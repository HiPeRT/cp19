#include <mpi.h>
#include <stdio.h>

int main (int argc, char* argv[])
{
  int id, p;
  int n;
  //Inizializzo la libreria MPI
  MPI_Init(&argc, &argv);
  //Richiedo il numero totale di processor elements
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  //Richiedo il mio ID tra questi
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  
  if (id == 0)
  {
    printf("Inserisci un numero: \n");
    fflush(stdin);
    scanf("%d",&n);
  }
  
  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

  printf("%d Received: %d\n", id, n);
  
  //Chiudo la libreria
  MPI_Finalize();
  return 0;
}
