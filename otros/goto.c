#include <stdio.h>

int main() {
    int i = 0;

    // Usamos el operador goto para saltar a la etiqueta "fin"
    start:
    printf("i = %d\n", i);
    i++;

    if (i < 5)
        goto start;  // Si i es menor que 5, vuelve a la etiqueta "start"

    printf("Fin del programa.\n");

    return 0;
}