#include <stdio.h>
#include <unistd.h>

int main() {
	int pid;
	pid = fork();
	if (pid == 0) {
		printf("Soy el hijo , mi PID es: %d\n", getpid());
        printf("Soy el padre , mi PID es: %d\n", getppid());

	
    } else if(pid < 0) {
        perror("Error en fork\n");
	
    }
	return 0;
}