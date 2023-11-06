//Basak Ozarslan 2385623
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N 5 // Number of elements for the array
#define numOfThread 2
void *childThread(int *array);
void *parentThread(int *array);
int main()
{
    pthread_t p[numOfThread];
    int *ptr = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        ptr[i] = 334;
    printf("The values of the array elements:\n");
    for (int i = 0; i < N; i++)
        printf("%d\n", ptr[i]);

    for (int i = 0; i < numOfThread; i++)
    {
        if (i == 0)
        {
            pthread_create(&p[i], NULL, (void *(*)(void *))childThread, (void *)ptr);
        }
        else
        {
            pthread_create(&p[i], NULL, (void *(*)(void *))parentThread, (void *)ptr);
        }
        pthread_join(p[i], NULL);
    }
    free(ptr);
    return 0;
}
void *childThread(int *array)
{
    printf("Updating the values of the array elements:\n");

    for (int i = 0; i < N; i++)
        array[i] = 462;

    pthread_exit(0);
}
void *parentThread(int *array)
{
    printf("The values of the array elements again:\n");
    for (int i = 0; i < N; i++)
        printf("%d \n", array[i]);

    pthread_exit(0);
}
