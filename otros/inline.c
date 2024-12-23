#include <stdio.h>

inline float cuadrado(float x) {
    return x * x;
}

int main() {
    float numero = 5.0;
    float resultado = cuadrado(numero);  // La llamada a la función puede ser reemplazada por x * x
    printf("El cuadrado de %.2f es %.2f\n", numero, resultado);
    return 0;
}
