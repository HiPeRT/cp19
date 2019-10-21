#include <stdio.h>
#include <omp.h>

#define NUM 19
int main()
{
	int arr[NUM], i;
	
	#pragma omp parallel num_threads(4) private(i) shared(arr)
	{
		// Knowing NUM
		int myid = omp_get_thread_num();
		int num_threads = omp_get_num_threads();
		
		int chunk = NUM / num_threads;
		int chunk_last;
		if(NUM % num_threads == 0)
		{
			chunk_last = chunk;
		}
		else
		{
			chunk ++;
			chunk_last = NUM % chunk;
		}
		
		printf("chunk is %d chunk_last = %d\n", chunk, chunk_last);
		
		int i_start = myid * chunk;
		int i_end;
		if(myid == num_threads - 1  && NUM % num_threads != 0)
			i_end = i_start + chunk_last;
		else
			i_end = i_start + chunk;
	
		printf("[Thread %d/%d] i_start is %d i_end = %d\n", myid, num_threads, i_start, i_end);
		
		for(i=i_start; i<i_end; i++)
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