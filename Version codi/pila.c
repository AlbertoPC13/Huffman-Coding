#include "pila.h"

void Push(apPila pila, Par par)
{
    //Se aumenta el tope de la pila
    pila->tope++;
    //Se asigna a la posicion tope el nuevo elemento 
    pila->datos[pila->tope] = par;
}

void Pop(apPila pila)
{
    //Se disminuye el tope de la pila
    pila->tope--;
}

int tamPila(apPila pila)
{
    //Se retorna el tope de la pila mas una unidad por el cero-indexado
    return pila->tope + 1;
}

int esVacia(apPila pila)
{
    //Se comprueba si el tope de pila es 0 o positivo
    if (pila->tope >= 0)
        //Retorna 0 si la pila no es vacia
        return 0;
    //Retorna 1 al ser vacia
    return 1;
}