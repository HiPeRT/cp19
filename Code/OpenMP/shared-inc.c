#include <stdio.h>
#include <omp.h>

int main()
{
	/* Declare lock var */
	omp_lock_t lock;
	/* Init the lock */
	omp_init_lock(&lock);

	int a = 0;
	#pragma omp parallel shared(a, lock) num_threads(1000)
	{
		/* If another thread set the lock,
		   I will wait */
		omp_set_lock(&lock);
		
		/* I can do my work being sure that no-
		   one else is here */
		a++;

		/* unset the lock so that other threads
		   can go */
		omp_unset_lock(&lock); 

	} // implicit barrier
	
	/*** Do this only once!! */
	/* Destroy lock */
	omp_destroy_lock(&lock);

	printf("a is %d\n", a);
	
	return 0;
}