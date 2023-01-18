#include <stdio.h>
#include <time.h>
#ifdef _OPENACC
#include <openacc.h>
#endif

#define NX 50000

int main(void)
{
    printf("here");
    double vecA[NX], vecB[NX], vecC[NX];
    double sum;
    int i;

    /* Initialization of the vectors */
    for (i = 0; i < NX; i++) {
        vecA[i] = 1.0 / ((double) (NX - i));
        vecB[i] = vecA[i] * vecA[i];
    }
    
    clock_t t;
    t = clock();
    
    /* TODO:
     * Implement vector addition on device with OpenACC
     * vecC = vecA + vecB
     */
    for (i = 0; i < NX; i++) {
       vecC[i] = vecA[i] + vecB[i];
    } 

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

    sum = 0.0;
    /* Compute the check value */
    for (i = 0; i < NX; i++) {
        sum += vecC[i];
    }
    
    printf("fun() took %f seconds to execute \n", time_taken);
    printf("Reduction sum: %18.16f\n", sum);

    return 0;
}