#include <windows.h>
#include <stdio.h>

#define TASKS_NUMBER 3

int main() {
    STARTUPINFO si[TASKS_NUMBER];              // Corrección: era "if", debe ser "si"
    PROCESS_INFORMATION pi[TASKS_NUMBER];

    // Comandos que los procesos hijos van a ejecutar
    char comandos[TASKS_NUMBER][100] = {
        "cmd.exe /c echo Hi! from process 1",
        "cmd.exe /c echo This is process 2 running something...",
        "cmd.exe /c echo Process 3 finished."
    };

    // Inicializar estructuras STARTUPINFO y PROCESS_INFORMATION
    for (int i = 0; i < TASKS_NUMBER; i++) {
        ZeroMemory(&si[i], sizeof(si[i]));
        si[i].cb = sizeof(si[i]);
        ZeroMemory(&pi[i], sizeof(pi[i]));
    }

    // Crear los procesos
    for (int i = 0; i < TASKS_NUMBER; i++) {
        // CreateProcess requiere que el segundo argumento sea modificable, así que hacemos una copia
        char commandLine[100];
        strcpy(commandLine, comandos[i]);

        if (!CreateProcess(
            NULL,               // Aplicación (NULL = usar línea de comandos)
            commandLine,        // Línea de comando (modificable)
            NULL,               // Atributos de seguridad del proceso
            NULL,               // Atributos de seguridad del hilo
            FALSE,              // Heredar handles
            0,                  // Flags de creación
            NULL,               // Variables de entorno (NULL = heredar)
            NULL,               // Directorio actual (NULL = heredar)
            &si[i],             // Info de inicio
            &pi[i]              // Info del proceso creado
        )) {
            printf("Couldn't create process %d (Error: %lu)\n", i + 1, GetLastError());
            return 1;
        } else {
            printf("Process %d created with PID: %lu\n", i + 1, pi[i].dwProcessId);
        }
    }

    // Esperar a que todos los procesos terminen
    HANDLE handles[TASKS_NUMBER];
    for (int i = 0; i < TASKS_NUMBER; i++) {
        handles[i] = pi[i].hProcess;
    }

    WaitForMultipleObjects(TASKS_NUMBER, handles, TRUE, INFINITE);

    // Cerrar los handles
    for (int i = 0; i < TASKS_NUMBER; i++) {
        CloseHandle(pi[i].hProcess);
        CloseHandle(pi[i].hThread);
    }

    printf("All processes have finished.\n");

    return 0;
}
