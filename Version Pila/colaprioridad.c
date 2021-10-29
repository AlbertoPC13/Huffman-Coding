#include "colaprioridad.h"
nodo crearNodo(unsigned char caracter, unsigned frecuencia)
{
    nodo temp = (nodo)malloc(sizeof(struct Nodo));

    temp->izquierda = temp->derecha = NULL;
    temp->caracter = caracter;
    temp->frecuencia = frecuencia;

    return temp;
}
monticulo crearMonticulo(unsigned capacidad)
{
    monticulo minHeap = (monticulo)malloc(sizeof(struct Monticulo));

    minHeap->tam = 0;

    minHeap->capacidad = capacidad;

    minHeap->nodos = (nodo *)malloc(minHeap->capacidad * sizeof(nodo));
    return minHeap;
}

void Heapify(monticulo minHeap, TIPO posicion)
{
    TIPO min = posicion;
    TIPO izquierda = 2 * posicion + 1;
    TIPO derecha = 2 * posicion + 2;

    if (izquierda < minHeap->tam && minHeap->nodos[izquierda]->frecuencia < minHeap->nodos[min]->frecuencia)
        min = izquierda;

    if (derecha < minHeap->tam && minHeap->nodos[derecha]->frecuencia < minHeap->nodos[min]->frecuencia)
        min = derecha;

    if (min != posicion)
    {
        nodo temporal = minHeap->nodos[min];
        minHeap->nodos[min] = minHeap->nodos[posicion];
        minHeap->nodos[posicion] = temporal;
        Heapify(minHeap, min);
    }
}

monticulo construirMinHeap(nodo *nodos, TIPO tam)
{
    TIPO n, i;
    monticulo minHeap = crearMonticulo(tam);
    n = minHeap->tam - 1;
    minHeap->nodos = nodos;

    minHeap->tam = tam;// 2*i+1
    for (i = (n - 1) / 2; i >= 0; i--)
        Heapify(minHeap, i);

    return minHeap;
}
/*
      
    5    4
  8     3  7
*/
nodo extractMin(monticulo minHeap) // 1
{
    nodo temp = minHeap->nodos[0];
    minHeap->nodos[0] = minHeap->nodos[minHeap->tam - 1];

    minHeap->tam--;
    Heapify(minHeap, 0);

    return temp;
}

void insertar(monticulo minHeap, nodo miniArbol)
{
    minHeap->tam++;
    TIPO i = minHeap->tam - 1;

    while (i && miniArbol->frecuencia < minHeap->nodos[(i - 1) / 2]->frecuencia)
    {
        minHeap->nodos[i] = minHeap->nodos[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->nodos[i] = miniArbol;
}
