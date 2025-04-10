#include <windows.h>
#include <stdio.h>

#define PROCESS_COUNT 3

int main() {
    STARTUPINFO si[PROCESS_COUNT];
    PROCESS_INFORMATION pi[PROCESS_COUNT];
    char cmd_line[PROCESS_COUNT][200];

    for (int i = 0; i < PROCESS_COUNT; i++) {
        snprintf(cmd_line[i], sizeof(cmd_line[i]),
            "cmd.exe /c for /L %%%%i in (1,1,5) do (echo Proceso %d - mensaje %%%%i & timeout /t 1 >nul)",
            i + 1, i + 1);
        
        ZeroMemory(&si[i], sizeof(si[i]));
        si[i].cb = sizeof(si[i]);
        ZeroMemory(&pi[i], sizeof(pi[i]));

        if (!CreateProcess(
            NULL,
            cmd_line[i],
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si[i],
            &pi[i]
        )) {
            printf("No se pudo crear el proceso %d (Error: %lu)\n", i + 1, GetLastError());
            return 1;
        } else {
            printf("Proceso %d creado.\n", i + 1);
        }
    }

    // Esperar a que todos terminen
    for (int i = 0; i < PROCESS_COUNT; i++) {
        WaitForSingleObject(pi[i].hProcess, INFINITE);
        CloseHandle(pi[i].hProcess);
        CloseHandle(pi[i].hThread);
    }

    printf("Todos los procesos terminaron.\n");
    return 0;
}
