#include <stdio.h>
#include <omp.h>

int main()
{
	int a = 11;
	
	#pragma omp parallel num_threads(32)
	{
		if(omp_get_thread_num() == 0)
			a = 7;
		
		printf("I am thread %d, a is %d\n", omp_get_thread_num(), a);
	}
	
	return 0;
}