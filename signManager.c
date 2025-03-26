#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void signManager(int sig_num){
    if (sig_num == SIGINT) {
        printf("\n→ Signal SIGINT (Ctrl+C) received, program still on.\n");
        fflush(stdout);
    } else if (sig_num == SIGTSTP) {
        printf("\n→ Signal SIGTSTP (Ctrl+Z) received, program ended.\n");
        exit(0);
    }
}

int main() {
    signal(SIGINT, signManager);
    printf("Press Ctrl+c to try... Ctrl+z to end\n");
    while(1) {
        sleep(1);
    }
    return 0;
}