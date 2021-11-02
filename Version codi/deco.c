#include "huffman.h"

int main()
{
    nodo arbolHuffman;
    nodo *nodos;
    TIPO posicion = 0, capacidad = 0, reps = 0;
    char cadenaCodigos[TAMMAX];
    unsigned char byte;

    int i;

    FILE *datos = fopen("repeticiones.txt", "r");

    fscanf(datos, "%d", &capacidad);
    printf("%d\n", capacidad);

    nodos = (nodo *)malloc(sizeof(nodo) * capacidad);

    for (i = 0; !feof(datos); i++)
    {
        fscanf(datos, "%d", &byte);
        fscanf(datos, "%d", &reps);
        nodos[i] = crearNodo(byte, reps);
        printf("%d - %d\n", byte, reps);
    }

    fclose(datos);

    arbolHuffman = Huffman(nodos, capacidad);
    printf("\nCaracter  codigo \n");
    Codigo codigos[256];
    for (i = 0; i < 256; i++)
        codigos[i].longitud = -1;

    imprimirCodigos(arbolHuffman, cadenaCodigos, posicion, codigos);

    printf("\n\n");
    for (i = 0; i < 256; i++)
    {
        if (codigos[i].longitud != -1)
        {
            printf("%c - %s - %d\n", i, codigos[i].cadena, codigos[i].longitud);
        }
    }

    return 0;
}