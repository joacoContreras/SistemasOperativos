#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define THREADS_NUM 3

long long partial_results[THREADS_NUM] = {1,1,1};


// Definimos un nuevo tipo de dato estructurado
typedef struct {
    int start; // Indice inicial del arreglo que va a procesar el hilo
    int end;    // Indice final del arreglo que va a procesar el hilo
    int thread_id;
} ThreadData;

// Funcion que va a ejecutar cada hilo
void* compute_partial_factorial(void* arg) {
    ThreadData* data = (ThreadData*) arg; 
    long long product = 1;
    for (int i = data->start; i < data->end; i++)
    {
        product *= i;
    }
    partial_results[data->thread_id] = product;
    pthread_exit(NULL);
}


int main() {
    pthread_t threads[THREADS_NUM];
    ThreadData thread_data[THREADS_NUM];

    // Definir los subrangos
    int ranges[THREADS_NUM][2] = {{1,4}, {5, 8}, {9, 12}};

    for (int i = 0; i < THREADS_NUM; i++) {
        thread_data[i].start = ranges[i][0];
        thread_data[i].end = ranges[i][1];
        thread_data[i].thread_id = i;
        pthread_create(&threads[i], NULL, compute_partial_factorial,(void*) &thread_data[i]);
    }

    // Esperar a que terminen todos los hilos
    for (int i = 0; i < THREADS_NUM; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Combinar los resultados
    long long factorial = 1;
    for (int i = 0; i < THREADS_NUM; i++)
    {
        factorial *= partial_results[i];
    }

    printf(" (12!) = %12d\n", factorial);

    return 0;
}