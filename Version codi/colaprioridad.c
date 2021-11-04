#include "colaprioridad.h"
nodo crearNodo(unsigned char caracter, unsigned frecuencia)
{
    //solicita memoria
    nodo temp = (nodo)malloc(sizeof(Nodo));
    //verifica si se solicito memoria correctamente
    if (!temp)
    {
        perror("No se pudo solictar memoria temp crearNodo(2)");
        exit(-1);
    }
    //inicializa cada elemento de la estructura nodo
    temp->izquierda = temp->derecha = NULL;
    temp->caracter = caracter;
    temp->frecuencia = frecuencia;

    return temp;
}
monticulo crearMonticulo(unsigned capacidad)
{
    //crea monticulo solicitando memoria
    monticulo minHeap = (monticulo)malloc(sizeof(Monticulo));
    //verifica si se hizo correctamente
    if (!minHeap)
    {
        perror("No se pudo solictar memoria minHeap crearMonticulo(1)");
        exit(-1);
    }
    //inicializa sus elementos con los datos ingresados
    minHeap->tam = 0;
    minHeap->capacidad = capacidad;
    minHeap->nodos = (nodo *)malloc(minHeap->capacidad * sizeof(nodo));
    //retorna el monticulo creado
    return minHeap;
}

void Heapify(monticulo minHeap, TIPO posicion)
{
    //verifica si el monticulo no es nulo
    if (!minHeap)
    {
        perror("Recibe un monticulo NULL Heapify(2)");
        exit(-2);
    }
    // toma el minimo como la primera posicion
    TIPO min = posicion;
    //posicion del padre
    TIPO izquierda = 2 * posicion + 1;
    //posicon del hijo
    TIPO derecha = 2 * posicion + 2;
    // si la posicion del hijo es menor al tamaño y la frecuencia es menor al minimmo propuesto, se convierte ahora en el minimo
    if (izquierda < minHeap->tam && minHeap->nodos[izquierda]->frecuencia < minHeap->nodos[min]->frecuencia)
        min = izquierda;
    // si la posicion del padre es menor al tamaño y la frecuencia es menor al minimmo propuesto, se convierte ahora en el minimo
    if (derecha < minHeap->tam && minHeap->nodos[derecha]->frecuencia < minHeap->nodos[min]->frecuencia)
        min = derecha;
    //si el minimo obtenido es diferente a la posicion donde deberia, se hace un intercambio para posicionarlo en el lugar correcto
    if (min != posicion)
    {
        nodo temporal = minHeap->nodos[min];
        minHeap->nodos[min] = minHeap->nodos[posicion];
        minHeap->nodos[posicion] = temporal;
        //restaura la propiedad de monticulo en la posicion donde se insertó
        Heapify(minHeap, min);
    }
}

monticulo construirMinHeap(nodo *nodos, TIPO tam)
{
    //verifica si el nodo es nulo
    if (!nodos)
    {
        perror("Recibe nodos NULL o vacios monticulo(2)");
        exit(-2);
    }
    TIPO n, i;
    //se crea el monticulo
    monticulo minHeap = crearMonticulo(tam);
    //inicializa sus elementos
    minHeap->tam = tam;
    n = minHeap->tam - 1;
    minHeap->nodos = nodos;
    minHeap->tam = tam;
    //restaura la propiedad de monticulo por la insercion de todos los elementos
    for (i = (n - 1) / 2; i >= 0; i--)
        Heapify(minHeap, i);
    //retorna el monticulo creado
    return minHeap;
}

nodo extractMin(monticulo minHeap) 
{
    //verifica que no sea nulo
    if (!minHeap)
    {
        perror("Recibe un monticulo NULL extractMin(1)");
        exit(-2);
    }
    //extrae el primer elemento (que es el minimo)
    nodo temp = minHeap->nodos[0];
    //lo sustituye por el siguiente mas pequeño (elimina)
    minHeap->nodos[0] = minHeap->nodos[minHeap->tam - 1];
    //reduce el tamaño
    minHeap->tam--;
    //restaura la propiedad de monticulo desde la posicion 0
    Heapify(minHeap, 0);
    //retorna el elemento eliminado
    return temp;
}

void insertar(monticulo minHeap, nodo miniArbol)
{
    //verifica que no sea nulo
    if (!minHeap)
    {
        perror("Recibe un monticulo NULL insertar(2)");
        exit(-2);
    }
    //verifica que el arbol no sea nulo
    if (!miniArbol)
    {
        perror("Recibe un nodo NULL insertar(2)");
        exit(-2);
    }
    //Se aumenta el tamano de la cola
    minHeap->tam++;
    TIPO i = minHeap->tam - 1;
    //va insertando en el lugar donde le corresponde al elemento ingresado
    while (i && miniArbol->frecuencia < minHeap->nodos[(i - 1) / 2]->frecuencia)
    {
        //sustituye en la posicion (i-1)/2
        minHeap->nodos[i] = minHeap->nodos[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    //inserta el nuevo miniarbol
    minHeap->nodos[i] = miniArbol;
}
