#include <windows.h>
#include <stdio.h>

#define TASKS_NUMBER 3

int main() {
    STARTUPINFO if [TASKS_NUMBER];
    PROCESS_INFORMATION pi[TASKS_NUMBER];
    char comandos[TASKS_NUMBER][100] = {
        "cmd.exe /c echo Hi! from process 1",
        "cmd.exe /c echo This is process 2 running something...",
        "cmd.exe /c echo Process 3 finished."
    };

    for (int i = 0; i < TASKS_NUMBER; i++)
    {
        ZeroMemory(&si[i], sizeof(si[i]));
        si[i].cb = sizeof(si[i]);
        ZeroMemory(&pi[i], sizeof(pi[i]));
    }

    // Crear el proceso hijo
    if (!CreateProcess(
        NULL,           // Aplicacion (NULL = usar linea de comando)
        comandos[i],    // Comando a ejecutar
        NULL,           // Atributos de seguridad proceso
        NULL,           // Atributos de seguridad hilo
        FALSE,          // Heredar handles
        0,              // Flags de creacion
        NULL,           // Variables de entorno (NULL = heredar)
        NULL,           // Directorio actual (NULL = heredar)
        &si[i],         // Info de inicio
        &pi[i]          // Info del proceso creado
    )) {
        printf("Couldn't create process %d (Error: %lu)\n", i + 1, GetLastError());
        return 1;
    } else {
        printf("Process %d created with PID: %lu\n", i + 1, pi[i].dwProcessId);
    }
    
    // Esperar a que todos los procesos terminen
    HANDLE handles[TASKS_NUMBER];
    for (int i = 0; i < TASKS_NUMBER; i++)
    {
        handles[i] = pi[i].hProcess;
    }

    WaitForMultipleObjects(TASKS_NUMBER, handles, TRUE, INFINITE);

    // Cerrar los handles
    for (int i = 0; i < TASKS_NUMBER; i++)
    {
        CloseHandle(pi[i].hProcess);
        CloseHandle(pi[i].hThread);
    }

    printf("All processes have finished.\n");

    return 0;
}

