#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define MAX_ARISTAS 1000

// Estructura para representar una arista
typedef struct {
    int origen, destino, peso;
} Arista;

// Estructura para representar el subconjunto de un vértice
typedef struct {
    int padre, rango;
} Subconjunto;

// Funciones auxiliares para el algoritmo de Kruskal
int comparar(const void *a, const void *b);
int encontrar(Subconjunto *subconjuntos, int i);
void unir(Subconjunto *subconjuntos, int x, int y);

// Función para ejecutar el algoritmo de Kruskal
void kruskal(Arista *aristas, int V, int E) {
    // Paso 1: Ordenar las aristas por peso
    qsort(aristas, E, sizeof(Arista), comparar);

    // Crear los subconjuntos para cada vértice
    Subconjunto *subconjuntos = (Subconjunto *)malloc(V * sizeof(Subconjunto));
    for (int i = 0; i < V; i++) {
        subconjuntos[i].padre = i;
        subconjuntos[i].rango = 0;
    }

    // Paso 2: Seleccionar las aristas más pequeñas y agregarlas al MST
    Arista mst[MAX_VERTICES - 1];  // Árbol de expansión mínima
    int mstIndice = 0;  // Índice para el MST

    for (int i = 0; i < E && mstIndice < V - 1; i++) {
        int u = aristas[i].origen;
        int v = aristas[i].destino;

        // Encontrar los subconjuntos de los dos vértices
        int x = encontrar(subconjuntos, u);
        int y = encontrar(subconjuntos, v);

        // Si los subconjuntos son diferentes, no forman ciclo
        if (x != y) {
            mst[mstIndice++] = aristas[i];  // Agregar arista al MST
            unir(subconjuntos, x, y);  // Unir los subconjuntos
        }
    }

    // Imprimir el MST
    printf("Arbol de Expansión Mínima (Kruskal):\n");
    int peso_total = 0;
    for (int i = 0; i < mstIndice; i++) {
        printf("%d -- %d == %d\n", mst[i].origen, mst[i].destino, mst[i].peso);
        peso_total += mst[i].peso;
    }
    printf("Peso total del MST: %d\n", peso_total);

    free(subconjuntos);
}

// Función para comparar dos aristas (para la ordenación)
int comparar(const void *a, const void *b) {
    return ((Arista *)a)->peso - ((Arista *)b)->peso;
}

// Función para encontrar el subconjunto de un vértice
int encontrar(Subconjunto *subconjuntos, int i) {
    if (subconjuntos[i].padre != i) {
        subconjuntos[i].padre = encontrar(subconjuntos, subconjuntos[i].padre);  // Compresión de ruta
    }
    return subconjuntos[i].padre;
}

// Función para unir dos subconjuntos
void unir(Subconjunto *subconjuntos, int x, int y) {
    int raizX = encontrar(subconjuntos, x);
    int raizY = encontrar(subconjuntos, y);

    if (raizX != raizY) {
        // Unir los subconjuntos por rango (el árbol más pequeño se une al más grande)
        if (subconjuntos[raizX].rango < subconjuntos[raizY].rango) {
            subconjuntos[raizX].padre = raizY;
        } else if (subconjuntos[raizX].rango > subconjuntos[raizY].rango) {
            subconjuntos[raizY].padre = raizX;
        } else {
            subconjuntos[raizY].padre = raizX;
            subconjuntos[raizX].rango++;
        }
    }
}

// Función principal
int main() {
    int V, E;

    // Leer el número de vértices y aristas
    printf("Ingrese el número de vértices: ");
    scanf("%d", &V);
    printf("Ingrese el número de aristas: ");
    scanf("%d", &E);

    Arista aristas[E];

    // Leer las aristas
    printf("Ingrese las aristas (origen, destino, peso):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &aristas[i].origen, &aristas[i].destino, &aristas[i].peso);
    }

    // Ejecutar el algoritmo de Kruskal
    kruskal(aristas, V, E);

    return 0;
}