#include <stdio.h>

extern int x;  // Declaración de la variable global definida en otro archivo
extern void mostrar();  // Declaración de la función mostrar

int main() {
    printf("Valor de x desde main: %d\n", x);  // Acceso a la variable global
    mostrar();  // Llamada a la función definida en variable.c
    return 0;
}