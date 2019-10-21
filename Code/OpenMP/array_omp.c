#include <stdio.h>
#include <omp.h>

#define NUM 19
int main()
{
	int arr[NUM], i;
	
	#pragma omp parallel num_threads(4) private(i) shared(arr)
	{
		#pragma omp for 
		for(i=0; i<NUM; i++)
		{
			printf("[Thread %d/%d] Executing iteration %d\n", omp_get_thread_num(), omp_get_num_threads(), i);
			arr[i] = i * 2;
		}
	}
		
	printf("\n----------------\n");
	for(i=0; i<NUM; i++)
		printf("arr[%d] is %d\n", i, arr[i]);
	
	return 0;
}