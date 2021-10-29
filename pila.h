#include<stdio.h>
#define PILAMAX 256

typedef struct Par
{
    unsigned char byte;
    int reps;
} Par;

typedef Par *apPar;

typedef struct Pila
{
    int tope;
    Par datos[PILAMAX];
} Pila;


typedef Pila *apPila;

void Push(apPila pila,Par par);
void Pop(apPila pila);
int tamPila(apPila pila);
void imprimir(apPila pila);
int esVacia(apPila pila);