#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <omp.h>

#define _printf(...) printf(__VA_ARGS__)
//#define _printf(...)

#define SECONDS 1000000000
#include <time.h>
#include <sys/time.h>
unsigned long long gettime(void)
{
    struct timespec t;
    int r;

    r = clock_gettime(CLOCK_MONOTONIC, &t);
    if (r < 0) {
        fprintf(stderr,"Error to get time! (%i)\n", r);
        return -1;
    }

    return (unsigned long long) t.tv_sec * SECONDS + t.tv_nsec;
}

float randNumGen()
{
	// Generate a random number
    int random_value = rand_r(/* Add thread-unique seed here. must be an "unsigned int *" */);
    float unit_random = random_value / (float) RAND_MAX; //make it between 0 and 1
    return unit_random;
}

int main()
{
    unsigned long long time = gettime(); // How to get time
    
//    for(i<NTHREADS)
//      /* Initialize thread-unique seed here */;
	
	
	float x = randNumGen(); // How to generate random number
	
    fprintf(stdout, "pi :\t \t3.1415926535897932384626433832795028841971693993751058209\n");
    
	return 0;
}
