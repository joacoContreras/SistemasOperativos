#include <windows.h>
#include <stdio.h>

int main() {
    STARTUPINFO si[2];
    PROCESS_INFORMATION pi[2];
    char *commands[] = {
        "cmd.exe /c echo Proceso de alta prioridad",
        "cmd.exe /c echo Proceso de baja prioridad"
    };
    DWORD priorities[] = {
        HIGH_PRIORITY_CLASS,
        IDLE_PRIORITY_CLASS // (LOW_PRIORITY_CLASS también puede usarse)
    };

    for (int i = 0; i < 2; i++) {
        ZeroMemory(&si[i], sizeof(si[i]));
        si[i].cb = sizeof(si[i]);
        ZeroMemory(&pi[i], sizeof(pi[i]));

        if (!CreateProcess(
            NULL,
            commands[i],
            NULL,
            NULL,
            FALSE,
            priorities[i],
            NULL,
            NULL,
            &si[i],
            &pi[i]
        )) {
            printf("Fallo al crear el proceso %d (Error: %lu)\n", i + 1, GetLastError());
            return 1;
        } else {
            printf("Proceso %d creado con PID %lu\n", i + 1, pi[i].dwProcessId);
        }
    }

    // Esperar que terminen
    WaitForSingleObject(pi[0].hProcess, INFINITE);
    WaitForSingleObject(pi[1].hProcess, INFINITE);

    // Liberar recursos
    for (int i = 0; i < 2; i++) {
        CloseHandle(pi[i].hProcess);
        CloseHandle(pi[i].hThread);
    }

    printf("Procesos terminados.\n");
    return 0;
}
