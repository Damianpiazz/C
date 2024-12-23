#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Inicializar la semilla para la generación de números aleatorios
    srand(time(NULL));

    // Definir el rango
    int min = 10, max = 50;

    // Generar un número aleatorio entre min y max
    int random_number = rand() % (max - min + 1) + min;

    printf("Número aleatorio entre %d y %d: %d\n", min, max, random_number);

    return 0;
}
