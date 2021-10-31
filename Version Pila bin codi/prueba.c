#include "pila.h"

int main(int argc, char const *argv[])
{
    Pila pila;

    pila.tope = -1; 

    char letra = (char)199;
    unsigned char byte;

    byte = (unsigned char)letra;
    printf("\nLetra: %d\n\nByte: %d",letra,byte);

    printf("\n\n");
    return 0;
}
