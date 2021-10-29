#include "pila.h"

void Push(apPila pila, Par par)
{
    pila->tope++;
    pila->datos[pila->tope] = par;
}

void Pop(apPila pila)
{
    pila->tope--;
}

int tamPila(apPila pila)
{
    return pila->tope + 1;
}

void imprimir(apPila pila)
{
    if (!esVacia(pila))
    {
        for (int i = 0; i <= pila->tope; i++)
        {
            printf("%c - ", pila->datos[i].byte);
        }
    }
    else
        printf("La pila esta vacia");
}

int esVacia(apPila pila)
{
    if (pila->tope >= 0)
        return 0;
    return 1;
}