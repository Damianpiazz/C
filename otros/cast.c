#include <stdio.h>

int main() {
    int entero = 7;
    float flotante;

    // Usamos el operador cast para convertir 'entero' a float
    flotante = (float)entero;

    printf("Valor entero: %d\n", entero);
    printf("Valor flotante (después del cast): %.2f\n", flotante);

    return 0;
}