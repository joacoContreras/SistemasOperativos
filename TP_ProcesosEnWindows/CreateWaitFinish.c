#include <windows.h>
#include <stdio.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    char cmd[] = "cmd.exe /c for /L %i in (1,0,2) do echo Corriendo";

    if (!CreateProcess(
        NULL,
        cmd,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    )) {
        printf("No se pudo crear el proceso (Error: %lu)\n", GetLastError());
        return 1;
    }

    printf("Proceso creado, esperando 5 segundos...\n");
    Sleep(5000);

    TerminateProcess(pi.hProcess, 0);

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    printf("Proceso terminado.\n");
    return 0;
}
