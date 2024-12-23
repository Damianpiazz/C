#include <stdio.h>
#include <stdlib.h>

#define K 2  // Número de dimensiones

// Estructura para representar un punto en K dimensiones
typedef struct {
    int punto[K];  // Arreglo para almacenar las coordenadas del punto
} Punto;

// Estructura para un nodo en el árbol K-D
typedef struct Nodo {
    Punto punto;               // El punto que guarda el nodo
    struct Nodo *izquierda;    // Subárbol izquierdo
    struct Nodo *derecha;      // Subárbol derecho
} Nodo;

// Función para crear un nuevo nodo
Nodo* crear_nodo(Punto punto) {
    Nodo *nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));
    nuevo_nodo->punto = punto;
    nuevo_nodo->izquierda = NULL;
    nuevo_nodo->derecha = NULL;
    return nuevo_nodo;
}

// Función para insertar un punto en el árbol K-D
Nodo* insertar(Nodo *raiz, Punto punto, int profundidad) {
    if (raiz == NULL) {
        return crear_nodo(punto);
    }

    // Calcular la dimensión actual (circularmente)
    int indice = profundidad % K;

    // Comparar el punto con la dimensión correspondiente
    if (punto.punto[indice] < raiz->punto.punto[indice]) {
        raiz->izquierda = insertar(raiz->izquierda, punto, profundidad + 1);
    } else {
        raiz->derecha = insertar(raiz->derecha, punto, profundidad + 1);
    }

    return raiz;
}

// Función para imprimir el árbol K-D en preorden (recursiva)
void imprimir_arbol(Nodo *raiz) {
    if (raiz != NULL) {
        printf("(");
        for (int i = 0; i < K; i++) {
            printf("%d ", raiz->punto.punto[i]);
        }
        printf(")\n");
        imprimir_arbol(raiz->izquierda);
        imprimir_arbol(raiz->derecha);
    }
}

// Función para buscar el punto más cercano en el árbol K-D
void buscar_punto_mas_cercano(Nodo *raiz, Punto punto, int profundidad, Punto *mejor_punto, int *mejor_distancia) {
    if (raiz == NULL) return;

    // Calcular la distancia del punto actual
    int distancia = 0;
    for (int i = 0; i < K; i++) {
        distancia += (raiz->punto.punto[i] - punto.punto[i]) * (raiz->punto.punto[i] - punto.punto[i]);
    }

    // Si es el punto más cercano hasta ahora, actualizamos
    if (*mejor_distancia == -1 || distancia < *mejor_distancia) {
        *mejor_distancia = distancia;
        *mejor_punto = raiz->punto;
    }

    // Calcular la dimensión actual
    int indice = profundidad % K;

    // Recurre por el subárbol correspondiente
    if (punto.punto[indice] < raiz->punto.punto[indice]) {
        buscar_punto_mas_cercano(raiz->izquierda, punto, profundidad + 1, mejor_punto, mejor_distancia);
        // Si la distancia mínima podría estar en el otro lado, lo comprobamos también
        if (punto.punto[indice] + *mejor_distancia > raiz->punto.punto[indice]) {
            buscar_punto_mas_cercano(raiz->derecha, punto, profundidad + 1, mejor_punto, mejor_distancia);
        }
    } else {
        buscar_punto_mas_cercano(raiz->derecha, punto, profundidad + 1, mejor_punto, mejor_distancia);
        // Verificamos también el otro subárbol
        if (punto.punto[indice] - *mejor_distancia < raiz->punto.punto[indice]) {
            buscar_punto_mas_cercano(raiz->izquierda, punto, profundidad + 1, mejor_punto, mejor_distancia);
        }
    }
}

// Función principal
int main() {
    Nodo *raiz = NULL;

    // Insertar puntos en el árbol
    Punto puntos[] = {{3, 6}, {17, 15}, {13, 15}, {6, 12}, {9, 1}, {2, 7}, {10, 19}};
    int n = sizeof(puntos) / sizeof(puntos[0]);

    for (int i = 0; i < n; i++) {
        raiz = insertar(raiz, puntos[i], 0);
    }

    // Imprimir el árbol K-D
    printf("Árbol K-D:\n");
    imprimir_arbol(raiz);

    // Buscar el punto más cercano
    Punto buscar = {10, 5};
    Punto mejor_punto;
    int mejor_distancia = -1;
    buscar_punto_mas_cercano(raiz, buscar, 0, &mejor_punto, &mejor_distancia);

    printf("\nEl punto más cercano a (%d, %d) es (%d, %d)\n", buscar.punto[0], buscar.punto[1], mejor_punto.punto[0], mejor_punto.punto[1]);

    return 0;
}