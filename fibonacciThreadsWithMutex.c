#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

int fibonacci[NUM_THREADS];  // Arreglo compartido
pthread_mutex_t mutex;       // Mutex para sincronizar acceso

// Función que cada hilo ejecutará
void *compute_fibonacci(void *param) {
    int index = *(int *)param;

    // Bloquear la sección crítica
    pthread_mutex_lock(&mutex);
    
    if (index == 0) {
        fibonacci[index] = 0;
    } else if (index == 1) {
        fibonacci[index] = 1;
    } else {
        fibonacci[index] = fibonacci[index - 1] + fibonacci[index - 2];
    }

    // Desbloquear la sección crítica
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(0);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    // Inicializar el mutex
    pthread_mutex_init(&mutex, NULL);

    // Crear hilos
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, compute_fibonacci, &thread_args[i]);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Imprimir resultados
    printf("Fibonacci: ");
    for (int i = 0; i < NUM_THREADS; i++) {
        printf("%d ", fibonacci[i]);
    }
    printf("\n");

    // Destruir el mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
