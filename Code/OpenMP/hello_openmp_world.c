#include <stdio.h>
#include <omp.h>

int main()
{
	int myid = omp_get_thread_num();
	printf("Hello SEQUENTIAL World! My id is %d\n\n", myid);
	
	#pragma omp parallel num_threads(4)
	{
		int myid2 = omp_get_thread_num();
		printf("Hello PARALLEL World! My id is %d\n", myid2);
	} // Implicit barrier
	
	//myid = omp_get_thread_num();
	printf("\nAfter parreg. My id is %d\n", myid);
	
	return 0;
}