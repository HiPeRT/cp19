#include <stdio.h>
#include <pthread.h>

/* PThread body function */
void *body(void *args)
{
	int * arg_ptr = (int *) args;
	
	pthread_t myid = pthread_self();
	printf("[THREAD] Hello World! I am thread #%d\n", myid);
	printf("[THREAD] args is @ 0x%llx\n", arg_ptr);
	printf("[THREAD] args is %d\n", *arg_ptr);
	(*arg_ptr) = 7;
	
	pthread_exit((void *) 100);
}

int main()
{
	pthread_t tid;
	pthread_attr_t attr;
	void *thread_return;
	int my_var = 11;
	printf("[MAIN] my_var is @ 0x%llx\n", &my_var);
	
	// Init attr
    pthread_attr_init(&attr);
	
	printf("[MAIN] Before pthread_create...\n");
	// Create thread
	int res = pthread_create (&tid,
                              &attr,
							  body,
							  (void *) &my_var);
	printf("[MAIN] Thread #%d created! res is %d\n", tid, res);

	// Destroy attr
    pthread_attr_destroy(&attr);
	
	// ...do your work....
	
	printf("[MAIN] Before joining thread #%d\n", tid);
	res = pthread_join (tid, &thread_return);
	printf("[MAIN] Joined thread #%d! res is %d\n", tid, res);
	
	int retval = (int) thread_return;
	
	printf("[MAIN] retval is %d\n", retval);
	printf("[MAIN] my_var is %d\n", my_var);
	
	return 0;
}