#include <stdio.h>
#include <omp.h>

int main()
{
	#pragma omp parallel num_threads(128)
	{ // Fork
	
		printf("I am thread %d, and I am BEFORE the explicit barrier construct\n", omp_get_thread_num());
		
		if(omp_get_thread_num() == 0)
		{
			// Explicit barrier
			#pragma omp barrier
		}
		
		printf("I am thread %d, and I am AFTER the explicit barrier construct\n", omp_get_thread_num());
		
	} // Implicit barrier + join
	
	return 0;
}