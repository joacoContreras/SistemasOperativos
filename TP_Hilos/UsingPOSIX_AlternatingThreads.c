#include <stdio.h>
#include <pthread.h>

int number = 1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond = PTHREAD_COND_INITIALIZER;

void* print_odds(void* arg) {
    while (number <= 10) {
        pthread_mutex_lock(&mutex);
        while (number % 2 == 0  && number <= 10)
        {
            pthread_cond_wait(&cond, &mutex);
        }
        if (number <= 10) {
            printf("Odd number: %d\n", number);
            number++;
        }
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void* print_evens(void* arg) {
    while (number <= 10)
    {
        pthread_mutex_lock(&mutex);
        while (number % 2 != 0 && number <= 10)
        {
            pthread_cond_wait(&cond, &mutex);
        }
        if (number <= 10)
        {
            printf("Even number: %d\n", number);
            number++;
        }
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t evenThread, oddThread;

    pthread_create(&evenThread, NULL, print_evens, NULL);
    pthread_create(&oddThread, NULL, print_odds, NULL);

    pthread_join(oddThread, NULL);
    pthread_join(evenThread, NULL);
    return 0;
} 