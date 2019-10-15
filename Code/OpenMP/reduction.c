#include <stdio.h>
#include <omp.h>

int main()
{
	int a = 11;
	
	printf("[SEQUENTIAL] I am thread %d, a is %d\n\n", omp_get_thread_num(), a);
	
	#pragma omp parallel num_threads(4) reduction(*:a)
	{
		a += 1;
		
		printf("[PARREG] I am thread %d, a is %d\n", omp_get_thread_num(), a);
	}
	
	printf("\n[SEQUENTIAL] I am thread %d, a is %d\n", omp_get_thread_num(), a);
	
	return 0;
}