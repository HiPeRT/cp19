#include <stdio.h>
#include <omp.h>

int main()
{
	#pragma omp parallel num_threads(4)
	{
		#pragma omp sections
		{
			/* A */
			#pragma omp section
				printf("[Thread %d/%d] I am executing section A\n", omp_get_thread_num(), omp_get_num_threads());
				
			/* B */
			#pragma omp section
			{
				printf("[Thread %d/%d] I am executing section B\n", omp_get_thread_num(), omp_get_num_threads());
			}
			
			/* C */
			#pragma omp section
			{
				printf("[Thread %d/%d] I am executing section C\n", omp_get_thread_num(), omp_get_num_threads());
			}
			
		} // end of SECTIONS: implicit barrier
	} // end of parreg:implicit barrier
	return 0;
}