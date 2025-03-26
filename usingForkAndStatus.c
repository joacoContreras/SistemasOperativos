#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();
    int status;  // Variable para almacenar el estado del hijo

    if (pid == 0) {
        // Código del hijo
        printf("Hijo ejecutándose...\n");
        sleep(2);
        printf("Hijo terminado.\n");
        exit(0);  // Se usa exit() para retornar un código de salida
    } 
    else if (pid > 0) {
        // Código del padre
        printf("Padre esperando al hijo...\n");
        wait(&status);  // Se espera al hijo y se guarda su estado

        // Análisis del estado del hijo
        if (WIFEXITED(status)) {
            printf("Hijo ha terminado normalmente con código de salida %d.\n", WEXITSTATUS(status));
        } 
        else if (WIFSIGNALED(status)) {
            printf("Hijo terminó por señal %d.\n", WTERMSIG(status));
        } 
        else {
            printf("Hijo terminó de forma desconocida.\n");
        }
    } 
    else {
        // Error en fork()
        perror("Error al crear el proceso hijo");
        return 1;
    }

    return 0;
}
