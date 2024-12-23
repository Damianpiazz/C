#include <stdio.h>

enum color {
    ROJO,    // 0
    VERDE,   // 1
    AZUL     // 2
};

int main() {
    enum color c1, c2;

    c1 = ROJO;
    c2 = VERDE;

    printf("Color 1: %d\n", c1);  // Imprime 0
    printf("Color 2: %d\n", c2);  // Imprime 1

    return 0;
}
