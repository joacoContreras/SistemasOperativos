#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

int fibonacci[NUM_THREADS]; // Arreglo compartido para almacenar resultados

// Función que cada hilo ejecutará
void *compute_fibonacci(void *param) {
    int index = *(int *)param;
    
    // Cálculo de Fibonacci sin recursión
    if (index == 0) {
        fibonacci[index] = 0;
    } else if (index == 1) {
        fibonacci[index] = 1;
    } else {
        fibonacci[index] = fibonacci[index - 1] + fibonacci[index - 2];
    }
    
    pthread_exit(0);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

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

    return 0;
}
