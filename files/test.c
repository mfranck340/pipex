#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int pipefd[2];  // Pipe para conectar los procesos

    // Crear un pipe
    if (pipe(pipefd) == -1) {
        perror("Error al crear pipe");
        exit(1);
    }

    // Crear el primer proceso para ejecutar 'cat'
    pid_t pid_cat = fork();
    if (pid_cat == -1) {
        perror("Error al hacer fork para cat");
        exit(1);
    }

    if (pid_cat == 0) {
        // Proceso hijo: Ejecutar 'cat < file1'
        // Redirigir la salida estándar a la escritura del pipe
        close(pipefd[0]);  // Cerrar lectura del pipe
        dup2(pipefd[1], STDOUT_FILENO);  // Redirigir stdout al pipe
        close(pipefd[1]);  // Ya no necesitamos el descriptor de escritura

        // Ejecutar el comando 'cat < file1'
        char *argv_cat[] = {"cat", "file1", NULL};
        if (execve("/bin/cat", argv_cat, NULL) == -1) {
            perror("Error ejecutando execve para cat");
            exit(1);
        }
    }

    // Crear el segundo proceso para ejecutar 'awk'
    pid_t pid_awk = fork();
    if (pid_awk == -1) {
        perror("Error al hacer fork para awk");
        exit(1);
    }

    if (pid_awk == 0) {
        // Proceso hijo: Ejecutar 'awk'
        // Redirigir la entrada estándar desde la lectura del pipe
        close(pipefd[1]);  // Cerrar escritura del pipe
        dup2(pipefd[0], STDIN_FILENO);  // Redirigir stdin desde el pipe
        close(pipefd[0]);  // Ya no necesitamos el descriptor de lectura

        // Ejecutar el comando 'awk'
        char *argv_awk[] = {"awk", "{count++} END {printf \"count: %i\" , count}", NULL};
        if (execve("/usr/bin/awk", argv_awk, NULL) == -1) {
            perror("Error ejecutando execve para awk");
            exit(1);
        }
    }

    // Cerrar los descriptores de pipe en el proceso padre
    close(pipefd[0]);
    close(pipefd[1]);

    // Esperar a que ambos procesos terminen
    wait(NULL);
    wait(NULL);

    return 0;
}
