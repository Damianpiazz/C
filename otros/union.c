#include <stdio.h>

union data {
    int i;
    float f;
    char c;
};

int main() {
    union data d;

    // Asignamos un valor a la variable "i"
    d.i = 42;
    printf("Valor de i: %d\n", d.i);

    // Asignamos un valor a la variable "f" (esto sobrescribe el valor de "i")
    d.f = 3.14;
    printf("Valor de f: %.2f\n", d.f);

    // Asignamos un valor a la variable "c" (esto sobrescribe el valor de "f")
    d.c = 'A';
    printf("Valor de c: %c\n", d.c);

    // Imprime el valor de "i" después de cambiar el valor de "c"
    printf("Valor de i después de asignar c: %d\n", d.i);

    return 0;
}