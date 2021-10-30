#include "colaprioridad.h"
nodo crearNodo(unsigned char caracter, unsigned frecuencia)
{
    nodo temp = (nodo)malloc(sizeof(Nodo));

    if(!temp){
        perror("No se pudo solictar memoria temp crearNodo(2)");
        exit(-1);
    }
    temp->izquierda = temp->derecha = NULL;
    temp->caracter = caracter;
    temp->frecuencia = frecuencia;

    return temp;
}
monticulo crearMonticulo(unsigned capacidad)
{
    monticulo minHeap = (monticulo)malloc(sizeof(Monticulo));
    if(!minHeap){
        perror("No se pudo solictar memoria minHeap crearMonticulo(1)");
        exit(-1);
    }
    minHeap->tam = 0;

    minHeap->capacidad = capacidad;

    minHeap->nodos = (nodo *)malloc(minHeap->capacidad * sizeof(nodo));
    return minHeap;
}

void Heapify(monticulo minHeap, TIPO posicion)
{
    if(!minHeap){
        perror("Recibe un monticulo NULL Heapify(2)");
        exit(-2);
    }
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
    if(!nodos){
        perror("Recibe nodos NULL o vacios monticulo(2)");
        exit(-2);
    }
    TIPO n, i;
    monticulo minHeap = crearMonticulo(tam);
    minHeap->tam = tam;// 2*i+1
    n = minHeap->tam - 1;
    minHeap->nodos = NULL;

     minHeap->nodos = nodos;

    minHeap->tam = tam;// 2*i+1
    for (i = (n - 1) / 2; i >= 0; i--)
        Heapify(minHeap, i); 

    return minHeap;
}

nodo extractMin(monticulo minHeap) // 1
{
    if(!minHeap){
        perror("Recibe un monticulo NULL extractMin(1)");
        exit(-2);
    }
    nodo temp = minHeap->nodos[0];
    minHeap->nodos[0] = minHeap->nodos[minHeap->tam - 1];

    minHeap->tam--;
    Heapify(minHeap, 0);

    return temp;
}

void insertar(monticulo minHeap, nodo miniArbol)
{
    if(!minHeap){
        perror("Recibe un monticulo NULL insertar(2)");
        exit(-2);
    }
    if(!miniArbol){
        perror("Recibe un nodo NULL insertar(2)");
        exit(-2);
    }
    minHeap->tam++;
    TIPO i = minHeap->tam - 1;

    while (i && miniArbol->frecuencia < minHeap->nodos[(i - 1) / 2]->frecuencia)
    {
        minHeap->nodos[i] = minHeap->nodos[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->nodos[i] = miniArbol;
}
