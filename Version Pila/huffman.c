#include "huffman.h"
nodo Huffman(nodo *nodos, TIPO tam)
{
    nodo izquierda, derecha, nuevoNodo;
    monticulo colaprioridad = construirMinHeap(nodos, tam);

    while (colaprioridad->tam != 1)
    {
        izquierda = extractMin(colaprioridad);
        derecha = extractMin(colaprioridad);

        nuevoNodo = crearNodo('\0', izquierda->frecuencia + derecha->frecuencia);

        nuevoNodo->izquierda = izquierda;
        nuevoNodo->derecha = derecha;

        insertar(colaprioridad, nuevoNodo);
    }
    return extractMin(colaprioridad);
}
void codigos(TIPO cadenaCodigos[], TIPO n)
{
    TIPO i;
    for (i = 0; i < n; ++i)
        printf("%d", cadenaCodigos[i]);
    printf("\n");
}
void imprimirCodigos(nodo arbolHuffman, TIPO cadenaCodigos[], TIPO posicion)
{
    if (arbolHuffman->izquierda)
    {
        cadenaCodigos[posicion] = 0;
        imprimirCodigos(arbolHuffman->izquierda, cadenaCodigos, posicion + 1);
    }
    if (arbolHuffman->derecha)
    {
        cadenaCodigos[posicion] = 1;
        imprimirCodigos(arbolHuffman->derecha, cadenaCodigos, posicion + 1);
    }
    if (esHoja(arbolHuffman->izquierda, arbolHuffman->derecha))
    {
        printf("%c ", arbolHuffman->caracter);
        codigos(cadenaCodigos, posicion);
    }
}
/* void HuffmanCodes(nodo arbolHuffman, apcodigos* codiguitos)
{
    nodo temporal;
    TIPO posicion=0,i=0;
    char  cadenaCodigos[TAMMAX];
    temporal=arbolHuffman;
    strcpy(cadenaCodigos,"");
    while (temporal)
    {
        
        if (temporal->izquierda)
        {
            cadenaCodigos[posicion++] = '0';
            temporal->izquierda=temporal->izquierda->izquierda;
        }
        if (temporal->derecha)
        {
            cadenaCodigos[posicion++] = '1';
            temporal->derecha=temporal->derecha->derecha;
        }
        if (esHoja(temporal->izquierda, temporal->derecha))
        {
            codiguitos[i]->caracter=temporal->caracter;
            codiguitos[i]->codigo=cadenaCodigos;
            codiguitos[i]->frecuencia=temporal->frecuencia;
            strcpy(cadenaCodigos,"");
            posicion=0;
            i++;
        }
    } 
}*/