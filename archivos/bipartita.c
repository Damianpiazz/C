#include <stdio.h>
#include <string.h>

typedef struct {
    int idPersona;        // ID único de la persona
    char nombre[50];      // Nombre de la persona
    int edad;             // Edad de la persona
    char telefono[20];    // Teléfono de la persona
} Persona;

typedef struct {
    int idPersona;        // ID de la persona
    long offset;          // Desplazamiento del registro en el archivo de datos
} Indice;

// Funciones
void crearIndice(FILE *dataFile, FILE *indexFile);
void buscarPersonaPorID(FILE *dataFile, FILE *indexFile, int idPersona);
void imprimirPersona(Persona *persona);
int buscarIndiceBinario(FILE *indexFile, int idPersona);

int main() {
    FILE *dataFile, *indexFile;
    int opcion, id;

    // Abrir el archivo de datos de personas y el archivo de índice
    dataFile = fopen("personas.dat", "rb+"); // Leer y escribir
    indexFile = fopen("indice.dat", "rb+"); // Leer y escribir

    if (dataFile == NULL || indexFile == NULL) {
        printf("Error al abrir los archivos.\n");
        return 1;
    }

    do {
        printf("\n--- Sistema de Gestión de Personas ---\n");
        printf("1. Crear índice de personas\n");
        printf("2. Buscar persona por ID\n");
        printf("3. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                crearIndice(dataFile, indexFile);
                printf("Índice creado con éxito.\n");
                break;

            case 2:
                printf("Ingrese el ID de la persona a buscar: ");
                scanf("%d", &id);
                buscarPersonaPorID(dataFile, indexFile, id);
                break;

            case 3:
                printf("Saliendo...\n");
                break;

            default:
                printf("Opción no válida.\n");
        }

    } while (opcion != 3);

    // Cerrar los archivos
    fclose(dataFile);
    fclose(indexFile);

    return 0;
}

// Función para crear el índice basado en el archivo de datos
void crearIndice(FILE *dataFile, FILE *indexFile) {
    Persona persona;
    Indice indice;
    long offset;

    // Moverse al inicio del archivo de índice
    fseek(indexFile, 0, SEEK_SET);

    // Leer el archivo de datos y generar el índice
    fseek(dataFile, 0, SEEK_SET);
    while (fread(&persona, sizeof(Persona), 1, dataFile)) {
        offset = ftell(dataFile) - sizeof(Persona);  // Obtener el desplazamiento del registro

        indice.idPersona = persona.idPersona;
        indice.offset = offset;

        // Escribir el índice en el archivo de índice
        fwrite(&indice, sizeof(Indice), 1, indexFile);
    }
}

// Función para realizar la búsqueda binaria en el archivo de índice
int buscarIndiceBinario(FILE *indexFile, int idPersona) {
    Indice indice;
    long left = 0, right, middle;
    fseek(indexFile, 0, SEEK_END);
    right = ftell(indexFile) / sizeof(Indice) - 1; // Último índice

    while (left <= right) {
        middle = (left + right) / 2;
        fseek(indexFile, middle * sizeof(Indice), SEEK_SET);
        fread(&indice, sizeof(Indice), 1, indexFile);

        if (indice.idPersona == idPersona) {
            return middle;
        } else if (indice.idPersona < idPersona) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    return -1;  // Si no se encuentra
}

// Función para buscar una persona por su ID utilizando el índice
void buscarPersonaPorID(FILE *dataFile, FILE *indexFile, int idPersona) {
    int idx = buscarIndiceBinario(indexFile, idPersona);
    if (idx == -1) {
        printf("Persona con ID %d no encontrada.\n", idPersona);
        return;
    }

    Indice indice;
    fseek(indexFile, idx * sizeof(Indice), SEEK_SET);
    fread(&indice, sizeof(Indice), 1, indexFile);

    // Leer el registro de la persona desde el archivo de datos
    Persona persona;
    fseek(dataFile, indice.offset, SEEK_SET);
    fread(&persona, sizeof(Persona), 1, dataFile);

    // Imprimir los detalles de la persona
    imprimirPersona(&persona);
}

// Función para imprimir los detalles de una persona
void imprimirPersona(Persona *persona) {
    printf("\n--- Persona Encontrada ---\n");
    printf("ID: %d\n", persona->idPersona);
    printf("Nombre: %s\n", persona->nombre);
    printf("Edad: %d\n", persona->edad);
    printf("Teléfono: %s\n", persona->telefono);
}