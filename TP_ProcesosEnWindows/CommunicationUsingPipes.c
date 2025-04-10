#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hReadPipe, hWritePipe;
    SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE }; // Heredable

    // Crear la tubería
    if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0)) {
        printf("Error creando pipe (%lu)\n", GetLastError());
        return 1;
    }

    // Información para crear el proceso hijo
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;  // Indicamos que usaremos los handles personalizados
    si.hStdInput = hReadPipe;           // Redirigir la entrada estándar al pipe de lectura
    si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE); // Salida estándar normal
    si.hStdError = GetStdHandle(STD_ERROR_HANDLE);   // Error estándar normal

    ZeroMemory(&pi, sizeof(pi));

    // Comando del hijo: "type con" leerá desde stdin (redirigido)
    char cmd[] = "cmd.exe /c type con";

    // Crear el proceso hijo
    BOOL success = CreateProcess(
        NULL,
        cmd,
        NULL,
        NULL,
        TRUE,             // Permitir heredar los handles
        0,
        NULL,
        NULL,
        &si,
        &pi
    );

    if (!success) {
        printf("Error al crear el proceso hijo (%lu)\n", GetLastError());
        CloseHandle(hReadPipe);
        CloseHandle(hWritePipe);
        return 1;
    }

    // Cerramos el extremo de lectura en el proceso padre (no se usa)
    CloseHandle(hReadPipe);

    // Mensaje que enviará el padre al hijo por la tubería
    const char* mensaje = "Hola hijo, este mensaje viene del proceso padre usando pipes.\n";
    DWORD bytesEscritos;
    WriteFile(hWritePipe, mensaje, (DWORD)strlen(mensaje), &bytesEscritos, NULL);

    // MUY IMPORTANTE: cerrar el extremo de escritura para que el hijo sepa que terminó
    CloseHandle(hWritePipe);

    // Esperar a que el proceso hijo termine
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Limpiar
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    printf("Proceso hijo finalizado.\n");

    return 0;
}
