#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

int child_pid;  // Almacena el PID del hijo

void sigmanager(int sig_num) {
    if (child_pid > 0) {
        // Reenviar la señal al hijo
        kill(child_pid, sig_num);
    }
    
    if (sig_num == SIGTSTP) {
        printf("\n→ SIGTSTP recibido, terminando padre...\n");
        exit(0);
    }
}

void child_handler(int sig_num) {
    if (sig_num == SIGINT) {
        printf("\n→ [Hijo] SIGINT recibido, sigo ejecutando...\n");
        fflush(stdout);
    } else if (sig_num == SIGTSTP) {
        printf("\n→ [Hijo] SIGTSTP recibido, terminando hijo...\n");
        exit(0);
    }
}

int main() {
    child_pid = fork();

    if (child_pid == 0) {  
        // Proceso hijo
        signal(SIGINT, child_handler);
        signal(SIGTSTP, child_handler);

        printf("[Hijo] PID: %d, esperando señales...\n", getpid());
        while (1) { sleep(1); }
    } else if (child_pid > 0) {  
        // Proceso padre
        signal(SIGINT, sigmanager);
        signal(SIGTSTP, sigmanager);

        printf("[Padre] PID: %d, hijo creado con PID: %d\n", getpid(), child_pid);
        wait(NULL);  // Espera a que el hijo termine
        printf("\n[Padre] Hijo terminado, cerrando padre...\n");
    } else {
        perror("Error al crear el proceso hijo");
        return 1;
    }

    return 0;
}
