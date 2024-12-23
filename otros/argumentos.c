#include <stdio.h>

int main(int argc, char *argv[]) {
    // Mostrar la cantidad de argumentos
    printf("Número de argumentos: %d\n", argc);

    // Imprimir cada argumento pasado
    for (int i = 0; i < argc; i++) {
        printf("Argumento %d: %s\n", i, argv[i]);
    }

    return 0;
}
