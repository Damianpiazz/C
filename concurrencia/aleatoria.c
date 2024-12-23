#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>  // Para wait()
#include <time.h>      // Para usar srand() y rand()

void crear_hijos_aleatorios(int nivel, int max_nivel) {
    if (nivel > max_nivel) {
        return;  // Si hemos alcanzado el nivel máximo, no creamos más hijos
    }

    // Número aleatorio de hijos que creará este proceso (entre 1 y 3)
    int num_hijos = rand() % 3 + 1;  // Genera un número aleatorio entre 1 y 3

    printf("Proceso de nivel %d con PID %d, Padre PID: %d, Creando %d hijos\n", 
           nivel, getpid(), getppid(), num_hijos);

    // Crear los hijos
    for (int i = 0; i < num_hijos; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("Error al crear hijo");
            exit(1);
        }

        if (pid == 0) {  // Este es el hijo
            crear_hijos_aleatorios(nivel + 1, max_nivel);  // Llamada recursiva para crear más hijos
            exit(0);  // El hijo termina después de crear sus propios hijos
        }
    }

    // El proceso padre espera a que todos sus hijos terminen
    for (int i = 0; i < num_hijos; i++) {
        wait(NULL);  // Espera a que cada hijo termine
    }
}

int main() {
    srand(time(NULL));  // Inicializa la semilla de números aleatorios
    int max_nivel = 3;  // Profundidad máxima de creación de hijos
    printf("Creando hijos de manera aleatoria hasta el nivel %d...\n", max_nivel);
    crear_hijos_aleatorios(1, max_nivel);  // Inicia la creación desde el nivel 1
    return 0;
}