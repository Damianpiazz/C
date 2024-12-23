#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

// Semáforo binario para sincronizar operaciones
sem_t semaforo;

// Variables compartidas
int saldo = 1000; // Balance inicial de la cuenta

// Firmas de las funciones de los hilos
static void *vender(void* arg);
static void *depositar(void* arg);

int main() {
    // Inicializa el semáforo con valor 1 (permitiendo acceso)
    sem_init(&semaforo, 0, 1);

    pthread_t hilo_venta, hilo_deposito;

    // Crear hilos para venta y depósito
    pthread_create(&hilo_venta, NULL, *vender, NULL);
    pthread_create(&hilo_deposito, NULL, *depositar, NULL);

    // Esperar a que los hilos terminen
    pthread_join(hilo_venta, NULL);
    pthread_join(hilo_deposito, NULL);

    // Mostrar el saldo final
    printf("Saldo final: %d\n", saldo);

    // Destruir el semáforo
    sem_destroy(&semaforo);

    return 0;
}

static void* vender(void* arg) {
    // Solicitar acceso al semáforo (espera)
    sem_wait(&semaforo);

    // Sección crítica: operación de venta
    printf("Realizando venta...\n");
    if (saldo >= 200) {
        saldo -= 200;
        printf("Venta realizada. Nuevo saldo: %d\n", saldo);
    } else {
        printf("Saldo insuficiente para realizar la venta.\n");
    }

    // Liberar el semáforo (sección crítica terminada)
    sem_post(&semaforo);

    return NULL;
}

static void* depositar(void* arg) {
    // Solicitar acceso al semáforo (espera)
    sem_wait(&semaforo);

    // Sección crítica: operación de depósito
    printf("Realizando depósito...\n");
    saldo += 500;
    printf("Depósito realizado. Nuevo saldo: %d\n", saldo);

    // Liberar el semáforo (sección crítica terminada)
    sem_post(&semaforo);

    return NULL;
}