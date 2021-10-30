#include <stdio.h>
#include <stdlib.h>

#define TIPO int
#define esHoja(izquierda, derecha) (!(izquierda) && !(derecha))

typedef struct Nodo
{
    unsigned char caracter;
    TIPO frecuencia;
    struct Nodo *izquierda;
    struct Nodo *derecha;
} Nodo;

typedef Nodo *nodo;

typedef struct Monticulo
{
    unsigned tam;
    unsigned capacidad;
    nodo *nodos;
} Monticulo;
typedef Monticulo *monticulo;

nodo crearNodo(unsigned char caracter, unsigned frecuencia);
monticulo crearMonticulo(unsigned capacidad);//inicializa
void Heapify(monticulo minHeap, TIPO posicion);
nodo extractMin(monticulo minHeap);//pop
void insertar(monticulo minHeap, nodo miniArbol);
monticulo construirMinHeap(nodo *nodos, TIPO tam);//construye con datos
