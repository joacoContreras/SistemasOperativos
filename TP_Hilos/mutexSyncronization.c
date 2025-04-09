#include <pthread.h>
#include <stdio.h>>
#include <stdlib.h>

#define NUM_THREADS 2
#define INCREMENTS 10000

int counter = 0;
pthread_mutex_t lock;

void* incrementCounter(void* arg) {
    for (int i = 0; i < INCREMENTS; i++)
    {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Inicializar mutex
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("couldn't init mutex...");
        return 1;
    }

    // Crear hilos
    for (int i = 0; i < NUM_THREADS; i++)
    {
        if (pthread_create(&threads[i], NULL, incrementCounter, NULL) != 0)
        {
            printf("Couldn't init thread: %d\n", i);
            return 1;
        }
    }
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Final counter value: %d\n", counter);

    pthread_mutexattr_destroy(&lock);
    
    return 0;    
}