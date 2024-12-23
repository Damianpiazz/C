#include <stdio.h>
#include <stdlib.h>

#define MAX 5 // Tamaño máximo de la cola circular
#define STATUS_CONTINUAR 1

int ejecucion;
int id = 0;

// Estructura para almacenar los datos de cada nodo
typedef struct {
    int i;
    int valor;
} Data;

// Estructura para la cola circular
typedef struct ColaCircular {
    Data elementos[MAX]; // Array para almacenar los elementos
    int frente;           // Índice del primer elemento
    int final;            // Índice del último elemento
    int longitud;         // Número de elementos en la cola
} ColaCircular;

// Firmas de funciones para la gestión de la cola circular
void inicializar_cola(ColaCircular *cola);
void enQueue(Data dato, ColaCircular *cola);
Data deQueue(ColaCircular *cola);
void imprimir_cola(ColaCircular *cola);

// Función para la gestión de la consola
void menu_consola(ColaCircular *cola) {
    int interfaz = 1;
    int seleccion;
    int size;
    Data dato;
    
    while (interfaz == STATUS_CONTINUAR) {
        // Limpiar consola
        system("CLS");
        printf("MENU\n\n");
        printf("1. Insertar elemento a la cola\n");
        printf("2. Eliminar elemento de la cola\n");
        printf("3. Consultar longitud de cola\n");
        printf("0. Fin programa\n\n");
        printf("> Seleccione una opción: ");
        scanf("%d", &seleccion);
        system("CLS");
        
        switch (seleccion) {
            case 1:
                id++;
                dato.i = id;
                dato.valor = rand() % 100;
                enQueue(dato, cola);
                break;
            case 2:
                deQueue(cola);
                break;
            case 3:
                size = cola->longitud;
                printf("Tamaño de la cola circular: %d\n", size);
                break;
            case 0:
                printf("Fin del programa ...\n");
                exit(0);
                break;
            default:
                printf("Error: ingreso un valor incorrecto\n");
                break;
        }
        imprimir_cola(cola);
        system("PAUSE");
    }
}

// Hilo principal
int main() {
    ejecucion = 1;
    srand(time(NULL));
    
    ColaCircular cola;
    inicializar_cola(&cola);  // Inicializa la cola circular
    
    while (ejecucion == STATUS_CONTINUAR) {
        menu_consola(&cola);
    }
    return 0;
}

// Inicializa la cola circular
void inicializar_cola(ColaCircular *cola) {
    cola->frente = 0;
    cola->final = -1;
    cola->longitud = 0;
}

// Inserta un elemento en la cola circular
void enQueue(Data dato, ColaCircular *cola) {
    if (cola->longitud == MAX) {
        printf("Error: La cola está llena\n");
    } else {
        cola->final = (cola->final + 1) % MAX; // Circular el índice
        cola->elementos[cola->final] = dato;
        cola->longitud++;
    }
}

// Elimina un elemento de la cola circular
Data deQueue(ColaCircular *cola) {
    if (cola->longitud == 0) {
        printf("Error: La cola está vacía\n");
        Data vacio = {0, 0}; // Valor vacío
        return vacio;
    } else {
        Data dato = cola->elementos[cola->frente];
        cola->frente = (cola->frente + 1) % MAX; // Circular el índice
        cola->longitud--;
        return dato;
    }
}

// Imprime los elementos de la cola
void imprimir_cola(ColaCircular *cola) {
    if (cola->longitud == 0) {
        printf("La cola está vacía\n");
        return;
    }
    printf("Contenido de la cola circular:\n");
    printf("--------------------------------------------------\n");
    printf("|  i  |   Valor   |     Dirección     |\n");
    printf("--------------------------------------------------\n");
    
    int idx = cola->frente;
    for (int i = 0; i < cola->longitud; i++) {
        printf("| %3d | %9d | %p |\n", 
               cola->elementos[idx].i, 
               cola->elementos[idx].valor, 
               (void*)&cola->elementos[idx]);
        idx = (idx + 1) % MAX;  // Circular el índice
    }
    printf("--------------------------------------------------\n");
}