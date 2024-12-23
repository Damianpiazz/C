#include <stdio.h>

int main() {
    int numero = -5;
    const char* resultado;

    // Usamos el operador condicional para verificar si el número es positivo o negativo
    resultado = (numero >= 0) ? "Positivo" : "Negativo";

    printf("El número es: %s\n", resultado);

    return 0;
}