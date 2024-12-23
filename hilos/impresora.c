#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

// Definir el número de impresoras disponibles
#define NUM_IMPRESORAS 3

// Crear un semáforo contador para las impresoras
sem_t impresoras;

// Función para simular el uso de una impresora por un hilo
void* usar_impresora(void* arg) {
    int id = *((int*)arg);  // ID del trabajo (hilo)

    printf("Trabajo %d: Intentando usar una impresora...\n", id);

    // Decrementar el semáforo (tomar una impresora)
    sem_wait(&impresoras);

    printf("Trabajo %d: Impresora tomada. Imprimiendo...\n", id);
    sleep(2);  // Simular el tiempo que tarda en imprimir
    printf("Trabajo %d: Impresión terminada. Liberando impresora.\n", id);

    // Incrementar el semáforo (liberar una impresora)
    sem_post(&impresoras);

    return NULL;
}

int main() {
    pthread_t trabajos[10];  // Array de hilos
    int ids[10];  // Array para almacenar los IDs de los trabajos (hilos)

    // Inicializar el semáforo con el número de impresoras disponibles
    sem_init(&impresoras, 0, NUM_IMPRESORAS);

    // Crear 10 trabajos (hilos)
    for (int i = 0; i < 10; i++) {
        ids[i] = i + 1;  // Asignar un ID a cada trabajo
        pthread_create(&trabajos[i], NULL, usar_impresora, &ids[i]);
    }

    // Esperar a que todos los trabajos terminen
    for (int i = 0; i < 10; i++) {
        pthread_join(trabajos[i], NULL);
    }

    // Destruir el semáforo
    sem_destroy(&impresoras);

    return 0;
}