#include <stdio.h>
#include <unistd.h>

int main() {
	int pid;
	pid = fork();
	if (pid == 0) {
		printf("Soy el hijo , mi PID es: %d\n", getpid());
	
    } else if(pid < 0) {
        perror("Error en fork\n");
	
    } else {
        printf("Soy el padre, PID del hijo es %d\n", pid);
    }
	return 0;
}
