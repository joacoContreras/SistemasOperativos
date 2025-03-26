#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int main() {
    int pid = fork();
    
    if (pid == 0) {
        // Código del hijo
        printf("Hijo ejecutándose... PID: %d\n", getpid());
        while(1); // Bucle infinito
    }
    return 0;
}