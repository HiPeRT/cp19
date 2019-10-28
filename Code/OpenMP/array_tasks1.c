#include <stdio.h>
#include <omp.h>

#define NUM 19
int main()
{
	int arr[NUM], i;
	
	#pragma omp parallel num_threads(4) private(i) shared(arr)
	{		
	    //#pragma omp single
		{
			printf("[Thread %d/%d] I am the producer\n", omp_get_thread_num(), omp_get_num_threads());
			#pragma omp for schedule(static)
			for(i=0; i<NUM; i++)
			{
				//#pragma omp task firstprivate(i) shared(arr)
				{
					printf("[Thread %d/%d] i is %d. I will execute\n",
						   omp_get_thread_num(), omp_get_num_threads(), i);
					arr[i] = i * 2;
				}
			}
		} // Barrier
	}
	
	printf("\n----------------\n");
	for(i=0; i<NUM; i++)
		printf("arr[%d] is %d\n", i, arr[i]);
	
	return 0;
}