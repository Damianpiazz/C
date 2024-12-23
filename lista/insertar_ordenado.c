#include <stdio.h>
#include <stdlib.h>

#define STATUS_CONTINUAR 1

int ejecucion;
int id = 0;

// Estructura para almacenar los datos de cada nodo
typedef struct{
    int i;
    int valor;
} Data;

// Estructura para el nodo de una lista enlazada
typedef struct NodoEnlazado
{
    Data Dato;
    struct NodoEnlazado *siguiente;
} Nodo;

// Estructura para gestionar la lista enlazada
typedef struct ListaEnlazada {
    Nodo *cabeza;      // Primer nodo de la lista
    Nodo *final;       // Último nodo de la lista
    int longitud;      // Número de nodos en la lista
} ListaEnlazada;

// Firmas de funciones para la gestión de la lista enlazada
void inicializar_lista(ListaEnlazada *punteros_lista);
void insertar_nodo_ordenado(Data dato, ListaEnlazada *punteros_lista);
void eliminar_nodo(int id, ListaEnlazada *punteros_lista);
void modificar_nodo(int id, ListaEnlazada *punteros_lista);
Nodo* consultar_nodo(int id, ListaEnlazada *punteros_lista);

// Firmas de funciones auxiliares
int int_aleatorio();
void imprimir_lista(ListaEnlazada *punteros_lista);
void imprimir_nodo(Nodo *nodo);

// Funcion para la gestion de la consola
void menu_consola(ListaEnlazada *punteros_lista)
{
    //Locales
    int interfaz = 1;
    int seleccion;
    int size;
    int i;
    while (interfaz == STATUS_CONTINUAR)
    {
        //Limpiar consola
        system("CLS");
        printf("MENU\n\n");
        printf("1. Insertar nodo a la lista ordenada\n");
        printf("2. Eliminar nodo de la lista\n");
        printf("3. Modificar un nodo\n");
        printf("4. Consultar nodo\n");
        printf("5. Consultar longitud de lista\n");
        printf("0. Fin programa\n\n");
        printf("> Seleccione una opcion: ");
        scanf("%d", &seleccion);
        system("CLS");
        switch (seleccion)
        {
        case 1:  
            id++;
            Data dato;
            dato.i = id;
            dato.valor = int_aleatorio();
            insertar_nodo_ordenado(dato, punteros_lista);
            break;
        case 2:
            printf("> Ingrese un id: ");
            scanf("%d", &i);
            eliminar_nodo(i , punteros_lista);
            break;
        case 3:
            printf("> Ingrese un id: ");
            scanf("%d", &i);
            modificar_nodo(i , punteros_lista);
            break;
        case 4:
            printf("> Ingrese un id: ");
            scanf("%d", &i);
            Nodo* nodo = consultar_nodo(i , punteros_lista);
            imprimir_nodo(nodo);
            break;
        case 5:
            size = punteros_lista->longitud;
            printf("Tamaño de la lista enlazada: %d\n", size);
            break;
        case 0:
            printf("Fin programa ...");
            exit(0);
            break;   
        default:
            printf("Error: ingreso un valor incorrecto\n");
            break;
        }
    imprimir_lista(punteros_lista);
    system("PAUSE");
    }
}

// Hilo principal
int main()
{
    ejecucion = 1;
    srand(time(NULL));
    // Instancio los punteros de la lista
    ListaEnlazada *punteros_lista;
    // Inicializo la lista enlazada
    inicializar_lista(punteros_lista);
    while (ejecucion == STATUS_CONTINUAR)
    {
        menu_consola(punteros_lista);
    }
    return 0;
}

void inicializar_lista(ListaEnlazada *punteros_lista)
{
    punteros_lista->cabeza = NULL;
    punteros_lista->final = NULL;
    punteros_lista->longitud = 0;
}

// Función para insertar un nodo en orden
void insertar_nodo_ordenado(Data dato, ListaEnlazada *punteros_lista)
{
    Nodo *nuevo_nodo = malloc(sizeof(Nodo));
    nuevo_nodo->Dato.i = dato.i;
    nuevo_nodo->Dato.valor = dato.valor;
    nuevo_nodo->siguiente = NULL;

    // Si la lista está vacía o el valor del nuevo nodo es menor que el primer nodo
    if (punteros_lista->cabeza == NULL || punteros_lista->cabeza->Dato.valor > nuevo_nodo->Dato.valor) {
        nuevo_nodo->siguiente = punteros_lista->cabeza;
        punteros_lista->cabeza = nuevo_nodo;
    } else {
        Nodo *nodo_actual = punteros_lista->cabeza;
        // Buscar la posición correcta donde insertar el nuevo nodo
        while (nodo_actual->siguiente != NULL && nodo_actual->siguiente->Dato.valor <= nuevo_nodo->Dato.valor) {
            nodo_actual = nodo_actual->siguiente;
        }
        nuevo_nodo->siguiente = nodo_actual->siguiente;
        nodo_actual->siguiente = nuevo_nodo;
    }
    punteros_lista->longitud++;
}

// Eliminar un nodo de la lista
void eliminar_nodo(int id, ListaEnlazada *punteros_lista)
{
    Nodo *nodo_anterior = NULL;
    Nodo *nodo_actual = punteros_lista->cabeza;
    if (punteros_lista->cabeza == NULL) {
        printf("La lista está vacía\n");
        return;
    }
    
    while (nodo_actual != NULL) {
        if (nodo_actual->Dato.i == id) {
            if (nodo_anterior == NULL) {
                punteros_lista->cabeza = nodo_actual->siguiente;
            } else {
                nodo_anterior->siguiente = nodo_actual->siguiente;
            }
            if (nodo_actual == punteros_lista->final) {
                punteros_lista->final = nodo_anterior;
            }
            free(nodo_actual);
            punteros_lista->longitud--;
            return;
        }
        nodo_anterior = nodo_actual;
        nodo_actual = nodo_actual->siguiente;
    }
}

// Modificar un nodo de la lista
void modificar_nodo(int id, ListaEnlazada *punteros_lista)
{
    Nodo *nodo_actual;
    if (punteros_lista->cabeza == NULL)
    {
        printf("Vacio\n");
    }
    else
    {
        Nodo *nodo_actual = punteros_lista->cabeza;
        while (nodo_actual != NULL)
        {
            if (nodo_actual->Dato.i == id)
            {
                nodo_actual->Dato.valor = int_aleatorio();
                return;
            }
            else
            {
                nodo_actual = nodo_actual->siguiente;
            }
        }
    }
    return;
}

// Consultar un nodo por su id
Nodo *consultar_nodo(int id, ListaEnlazada *punteros_lista)
{
    Nodo *nodo_actual;
    if (punteros_lista->cabeza == NULL)
    {
        return NULL;
    }
    else
    {
        nodo_actual = punteros_lista->cabeza;
        while (nodo_actual != NULL)
        {
            if (nodo_actual->Dato.i == id)
            {
                return nodo_actual;
            }
            else
            {
                nodo_actual = nodo_actual->siguiente;
            }
        }
    }
}

int int_aleatorio()
{
    return rand()%100;
}

// Imprimir la lista
void imprimir_lista(ListaEnlazada *punteros_lista)
{
    Nodo *nodo_actual = punteros_lista->cabeza;
    printf("Contenido de la lista enlazada ordenada:\n");
    printf("--------------------------------------------------\n");
    printf("|  i  |   Valor   |     Direccion     |   Siguiente   |\n");
    printf("--------------------------------------------------\n");
    
    while (nodo_actual != NULL) {
        printf("| %3d | %9d | %p | %p |\n", 
               nodo_actual->Dato.i, 
               nodo_actual->Dato.valor, 
               (void*)nodo_actual, 
               (void*)nodo_actual->siguiente);
        nodo_actual = nodo_actual->siguiente;
    }
    printf("--------------------------------------------------\n");
}

// Imprimir detalles de un nodo
void imprimir_nodo(Nodo *nodo)
{
    if (nodo == NULL) {
        printf("El nodo es NULL. No se puede imprimir.\n");
        return;
    }
    printf("Detalles del nodo:\n");
    printf("ID: %d\n", nodo->Dato.i);
    printf("Valor: %d\n", nodo->Dato.valor);
    printf("Direccion: %p\n", (void*)nodo);
    printf("Siguiente: %p\n", (void*)nodo->siguiente);
}