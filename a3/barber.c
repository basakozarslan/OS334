#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdbool.h>
//Baþak Özarslan 2385623

pthread_mutex_t mutex;
sem_t semCustomer;
sem_t semCustomerDone;
sem_t semBarber;
sem_t semBarberDone;

//global variables
int numberOfChairs = 0;
int currentCustomerId = 0;
int numOfCustomers = 0;

void initCustomerArray(int *customerArray, int numOfCustomers){
    for(int i=0; i<numOfCustomers; i++) customerArray[i] = i;
}

void *customer(void *x){
    int customerID = *(int *)x;
    printf("Customer %d is waiting for a haircut\n", customerID);

    pthread_mutex_lock(&mutex);
    if(currentCustomerId == numberOfChairs){
        printf("Customer %d is waiting for a barber\n", customerID);
        sem_wait(&semBarber);
        while(1);
    }
    else{
        currentCustomerId++;
    }
    printf("Customer with id %d is getting a haircut\n Available number of chairs %d", customerID, numberOfChairs-currentCustomerId);
    pthread_mutex_unlock(&mutex);

    sem_post(&semCustomer);
    sem_post(&semBarber);
    printf("Customer %d is getting a haircut\n", customerID);

    sleep(rand()%5+5);

    sem_post(&semCustomerDone);
    sem_wait(&semBarberDone);

    pthread_mutex_lock(&mutex);
    currentCustomerId--;
    pthread_mutex_unlock(&mutex);
    if(customerID == numOfCustomers){
        printf("Customer %d is leaving\n", customerID);
        exit(0);
    }
}

void *barber(void *y){
    while(1){
        sem_wait(&semCustomer);  //wait()
        sem_post(&semBarber);   //signal()
        printf("Barber is working\n");
        sleep(rand()%5+5);
        printf("Barber finished\n");
        sem_wait(&semCustomerDone);  //wait()
        sem_post(&semBarberDone);  //signal()
    }
}
int main(){

    int *customerArray ;
    pthread_t barberThread, *customerThreads;

    printf("Enter number of chairs: ");
    scanf("%d", &numberOfChairs);
    printf("Enter number of customers: ");
    scanf("%d", &numOfCustomers);

    customerArray = (int *)malloc(sizeof(int)*numOfCustomers);
    customerThreads = (pthread_t *)malloc(sizeof(pthread_t)*numOfCustomers);
    initCustomerArray(customerArray,numOfCustomers);

    sem_init(&semCustomer,0,0);
    sem_init(&semCustomerDone,0,0);
    sem_init(&semBarber,0,0);
    sem_init(&semBarberDone,0,0);
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&barberThread, NULL, barber, NULL); //create thread for barber
    //create threads for customer

    for(int i = 0; i < numOfCustomers; i++){
        pthread_create(&customerThreads[i], NULL, customer, (void *)&customerArray[i]);
        sleep(rand()%5+1);
    }

    for(int i = 0; i < numOfCustomers; i++){
        pthread_join(customerThreads[i], NULL);
    }

    return 0;
}
