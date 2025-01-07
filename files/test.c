#include <stdio.h>
#include <unistd.h>

int main() {
    // Ruta al ejecutable de awk
    char *program = "/usr/bin/awk";

    // Argumentos para awk
    char *args[] = {
        "awk",
        "{print \"Texto:\\n \\\"\" $0 \"\\\"\"}", // Script awk
        NULL
    };

    // Variables de entorno (puedes usar NULL si no necesitas entorno específico)
    char *env[] = {NULL};

    // Redirigir la entrada estándar (echo "hello world" -> awk)
    if (fork() == 0) {
        execlp("echo", "echo", "hello world", NULL);
    } else {
        execve(program, args, env);
    }

    perror("execve failed");
    return 1;
}
