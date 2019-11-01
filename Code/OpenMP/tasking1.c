#include <stdio.h>
#include <omp.h>

int main()
{
	#pragma omp parallel num_threads(2)
	{
		printf("I am thread #%d and I am producing T0\n", omp_get_thread_num());
		#pragma omp task
		{
			printf("I am thread #%d and I am running T0\n", omp_get_thread_num());
		}
		
		printf("I am thread #%d and I am producing T1\n", omp_get_thread_num());
		#pragma omp task
		{
			printf("I am thread #%d and I am running T1\n", omp_get_thread_num());
		}
		
	} // parreg
	return 0;
}