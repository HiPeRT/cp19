#include <stdio.h>
#include <omp.h>

int main()
{
	int myid = omp_get_thread_num();
	printf("Hello SEQUENTIAL World! My id is %d\n\n", myid);
	
	omp_set_num_threads(6); // From now on, every parreg has 6 threads
	
	#pragma omp parallel num_threads(4) // This parreg has four threads
	{
		int myid2 = omp_get_thread_num();
		printf("Hello PARALLEL World! My id is %d out of %d\n", myid2, omp_get_num_threads());
	} // Implicit barrier
	
	//myid = omp_get_thread_num();
	printf("\nAfter parreg. My id is %d\n", myid);
	
	return 0;
}