#include <stdio.h>
#include <omp.h>

/* Simple: assume it's a multiple of NUM */
#define NUM 20
#define CHUNK 4

int main()
{
	int arr[NUM], i;
	
	#pragma omp parallel num_threads(4) private(i) shared(arr)
	{		
	    #pragma omp single
		{
			printf("[Thread %d/%d] I am the producer\n", omp_get_thread_num(), omp_get_num_threads());
			for(i=0; i<NUM/CHUNK; i++)
			{
				// One could also use firstprivate(arr). Why?
				#pragma omp task firstprivate(i) shared(arr)
				{
					printf("[Thread %d/%d] i is %d. I will execute from %d to %d\n",
						   omp_get_thread_num(), omp_get_num_threads(), i, i * CHUNK, (i+1) * CHUNK - 1);
					int j;
					for(j=0; j<CHUNK; j++) // This doesn't work, for instance, if NUM is not multiple of CHUNK
										   // A quick&dirty fix could be:
										   //   for(j=0; j<CHUNK && idx < NUM; j++)
					{
						// Compute index to work on
						
						int idx = i * CHUNK + j;
						// printf("[Thread %d/%d] i is %d j is %d CHUNK is %d NUM is %d => idx is %d\n",
							   // omp_get_thread_num(), omp_get_num_threads(), i,j, CHUNK, NUM, idx);
						arr[idx] = idx * 2;
					}
				}
			}
		} // end of single
	}
	
	printf("\n----------------\n");
	for(i=0; i<NUM; i++)
		printf("arr[%d] is %d\n", i, arr[i]);
	
	return 0;
}