#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include<time.h>

int thread_count;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s ,number of threads> <number of samples>\n", argv[0]);
        return -1;
    }

    thread_count = strtol(argv[1],NULL,10);

    int samples = atoi(argv[1]);
    int count = 0;


    // Start parallel region
    #pragma omp parallel num_threads(thread_count)
    {
        unsigned int seed = (unsigned int)(time(NULL)) ^ omp_get_thread_num(); // Unique seed per thread
        int local_count = 0;

        #pragma omp for
        for (int i = 0; i < samples; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;
            if (x * x + y * y <= 1.0) {
                local_count++;
            }
        }

        // Critical section to update global count
        #pragma omp atomic
        count += local_count;
    }

    // Calculate pi estimate
    double pi_estimate = 4.0 * count / samples;
    printf("Estimate of pi: %.7f\n", pi_estimate);

    return 0;
}
