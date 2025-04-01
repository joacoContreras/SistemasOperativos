#include <unistd.h>>
#include <stdlib.h>
#include <string.h>

#define SIZE 1024 * 1024 * 256 // 256 MB por proceso

int main()
{
    while (1)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            break; // Si fork falla, salir del bucle en este proceso
        }
        if (pid == 0)
        {
            // proceso hijo
            // reservar 256 MB de memoria y escribir en ella
            char *memory = (char *)malloc(SIZE);
            if (memory!= NULL)
            { // Llenar la memoria para forzar asignacion fisica
                memset(memory, 0xFF, SIZE);
            }
            // Bucle infinito consumiendo CPU
            volatile int x = 0;
            while (1)
            {
                x = x + 1; // operacion simple para mantener CPU ocupada 
            }
            // El proceso hijo nunca termina por si mismo
            }
        // el proceso padre sigue creando mas hijos
    }
    return 0;
}