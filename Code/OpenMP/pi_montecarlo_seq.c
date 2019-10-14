#include <math.h>
#include <string.h>
#include <stdio.h>

#define SECONDS 1000000000
#define _printf(...) printf(__VA_ARGS__)
//#define _printf(...)

#include <time.h>
#include <sys/time.h>
unsigned long long gettime(void)
{
    struct timespec t;
    int r;

    r = clock_gettime(CLOCK_MONOTONIC, &t);
    if (r < 0)
	{
        printf("Error to get time! (%i)\n", r);
        return -1;
    }

    return (unsigned long long) t.tv_sec * SECONDS + t.tv_nsec;
}

unsigned int seedp = 0;
#include <stdlib.h>
float randNumGen()
{
    int random_value = rand_r(&seedp); //Generate a random number (parallel version)
    //int random_value = rand(); //Generate a random number
    float unit_random = random_value / (float) RAND_MAX; //make it between 0 and 1
    return unit_random;
}

int main()
{
    unsigned long long t_start, t_delta, counter=0;
    float in_count = 0;
	unsigned long long tot_iterations = 10000000L;

	_printf("[get_pi] tot_iterations = %llu\n", tot_iterations); 

    t_start = gettime();
    
    //srand ( time(NULL) ); // initiate random seed (in case you use rand)
	seedp = time(NULL);
	
	for(counter=0;counter<tot_iterations;counter++)
	{
		float x = randNumGen();
		float y = randNumGen();

		float result = sqrt((x*x) + (y*y));

		if(result < 1.0)
			in_count += 1;         //check if the generated value is inside a unit circle		
	}

    float pi = 4.0 * in_count / tot_iterations;
	
    t_delta = gettime() - t_start;
    
    printf("pi :\t \t3.1415926535897932384626433832795028841971693993751058209\n");
    printf("get_pi: \t%.10f \ttime:\t%llu \tus\n", pi, t_delta/1000);

	return 0;
}
