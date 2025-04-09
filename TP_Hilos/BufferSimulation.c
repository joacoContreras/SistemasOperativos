#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_ITEMS 10

int buffer = 0;
int full = 0; // 0 --> vacio; 1 --> lleno

pthread_mutex_t mutex; // mutex para proteger buffer
pthread_cond_t cond_full; // condicion: .buffer lleno
pthread_cond_t cond_empty; //           .buffer vacio

void* producer(void * arg) {
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        pthread_mutex_lock(&mutex);

        // Esperar si el buffer esta lleno
        while (buffer == 1) {
            pthread_cond_wait(&cond_empty, &mutex);
        }     
        // Producir un item
        buffer = i;
        printf("Producer produced: %d\n", buffer);
        full = 1;
        
        // Notificar al consumidor
        pthread_cond_signal(&cond_full);
        pthread_mutex_unlock(&mutex);

        sleep(1); // Simular tiempo de produccion
    }
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        pthread_mutex_lock(&mutex);

        // Esperar si el buffer esta vacio
        while (full == 0) {
            pthread_cond_wait(&cond_full, &mutex);
        }
        
        // Consumir el item
        printf("Consumer consumed: %d\n", buffer);
        full = 0;

        // Notificar al productor
        pthread_cond_signal(&cond_empty);
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
    pthread_exit(NULL);
}

    int main() {
        pthread_t prod, cons;

        // Inicializar mutex y condiciones
        pthread_mutex_init(&mutex, NULL);
        pthread_cond_init(&cond_full, NULL);
        pthread_cond_init(&cond_empty, NULL);

        // Crear hilos productor y consumidor
        pthread_create(&prod, NULL, producer, NULL);
        pthread_create(&cons, NULL, consumer, NULL);

        // Esperar a que terminen
        pthread_join(prod, NULL);
        pthread_join(prod, NULL);

        // Destruir recursos
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond_full);
        pthread_cond_destroy(&cond_empty);

        return 0;
}