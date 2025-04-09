#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4
#define ARRAY_SIZE 100

int array[ARRAY_SIZE];
int partial_sums[NUM_THREADS];

// Definimos un nuevo tipo de dato estructurado
typedef struct {
    int start; // Indice inicial del arreglo que va a procesar el hilo
    int end;    // Indice final del arreglo que va a procesar el hilo
    int thread_id;
} ThreadData;

// Funcion que va a ejecutar cada hilo
void* sum_range(void* arg) {
    ThreadData* data = (ThreadData*) arg; 
    int sum = 0;
    for (int i = data->start; i < data->end; i++)
    {
        sum += array[i];
    }
    partial_sums[data->thread_id] = sum;
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    // Inicializar arreglo
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = i + 1;
    }
    
    // Crear hilos
    int chunck_size = ARRAY_SIZE / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_data[i].start = i * chunck_size;
        thread_data[i].end = (i == NUM_THREADS - 1) ? ARRAY_SIZE : (i + 1) * chunck_size;
        thread_data[i].thread_id = i;
        pthread_create(&threads[i], NULL, sum_range, &thread_data[i]);
    }

    // Esperar a que terminen todos los hilos
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Sumar los resultados parciales
    int total_sum = 0;
    for (int i = 0; i < NUM_THREADS; i++)
    {
        total_sum += partial_sums[i];
    }

    printf("Total summatory: %d\n", total_sum);

    return 0;
}