//Basak Ozarslan 2385623
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
void *worker(void *param);
double random_double();
#define NUMBER_OF_DARTS 50000000
#define numOfThread 4
float circle_count = 0.0;
pthread_mutex_t mutex;

int main(int argc, const char *argv[]) {

    /* seed the random number generator */
    srandom((unsigned)time(NULL));

    pthread_t threads[numOfThread];
    int darts_per_thread = NUMBER_OF_DARTS / numOfThread;

    pthread_mutex_init(&mutex, NULL);  //initialise mutex null

    int i;
    for (i = 0; i < numOfThread; i++) {
        pthread_create(&threads[i], NULL, worker, (void *)&darts_per_thread);
    }

    for (i = 0; i < numOfThread; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    /* estimate Pi */
    double estimated_pi = 4.0 * circle_count / NUMBER_OF_DARTS;

    printf("Pi = %f\n", estimated_pi);

    return 0;
}
/*
 * Generates a double precision random number
 */
double random_double() {
    return random() / ((double)RAND_MAX + 1);
}

void *worker(void *param) {
    int number_of_darts = *((int *)param);
    int hit_count = 0;
    double x, y;
    int i;
    for (i = 0; i < number_of_darts; i++) {

        /* generate random numbers between -1.0 and +1.0 (exclusive) */
        x = random_double() * 2.0 - 1.0;
        y = random_double() * 2.0 - 1.0;

        if (sqrt(x * x + y * y) < 1.0) {
            ++hit_count;
        }
    }

    pthread_mutex_lock(&mutex);
    circle_count += hit_count;
    pthread_mutex_unlock(&mutex);

    pthread_exit(0);
}

