#include "pila.h"

int main(int argc, char const *argv[])
{
    Pila pila;

    pila.tope = -1; 

    unsigned char arr[10] = {'a','b','c','d','e','f','g','h','j','r'};

    for (int i = 0; i < 10; i++)
    {
        Par nuevoPar;
        nuevoPar.byte = arr[i];
        Push(&pila,nuevoPar);
    }

    printf("\nTamano de pila: %d\n\n",tamPila(&pila));
    
    imprimir(&pila);
    printf("\n\n");
    return 0;
}
