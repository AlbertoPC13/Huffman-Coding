#include "huffman.h"
nodo Huffman(nodo *nodos, TIPO tam)
{
    if(!nodos){
        perror("Recibe nodos NULL o vacios Huffman(2)");
        exit(-2);
    }
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
char* Codigos(char cadenaCodigos[], TIPO n)
{
    int i;
    char* cadena=malloc(sizeof(char*)*n);
    for (i = 0; i < n; ++i)
        cadena[i]= cadenaCodigos[i];
    cadena[i]='\0';
    return cadena;
}
void imprimirCodigos(nodo arbolHuffman, char cadenaCodigos[], TIPO posicion, Codigo *codigos)
{
    if(!arbolHuffman){
        perror("Recibe un nodo NULL o vacio imprimirCodigos(3)");
        exit(-2);
    }
    if (arbolHuffman->izquierda)
    {
        cadenaCodigos[posicion] = '0';
        imprimirCodigos(arbolHuffman->izquierda, cadenaCodigos, posicion + 1, codigos);
    }
    if (arbolHuffman->derecha)
    {
        cadenaCodigos[posicion] = '1'; // 11001
        imprimirCodigos(arbolHuffman->derecha, cadenaCodigos, posicion + 1, codigos);
    }
    if (esHoja(arbolHuffman->izquierda, arbolHuffman->derecha))
    {
        //11001
        codigos[arbolHuffman->caracter].cadena = (char *)malloc(sizeof(posicion));
        codigos[arbolHuffman->caracter].cadena = Codigos(cadenaCodigos, posicion);
        codigos[arbolHuffman->caracter].longitud = posicion;
        printf("%c %s\n", arbolHuffman->caracter,Codigos(cadenaCodigos, posicion));
        //Codigos(cadenaCodigos, posicion);
    }
}
/*
    int adquirirNodos(nodo* nodos){
    FILE *datos = fopen("repeticiones.txt", "r");
    int tam, reps, i;
    unsigned char byte;

    fscanf(datos, "%d", &tam);
    printf("%d\n", tam);

    nodos = (nodo *)malloc(sizeof(nodo) * tam);

    for (i = 0; !feof(datos); i++)
    {
        fscanf(datos, "%d", &byte);
        fscanf(datos, "%d", &reps);
        nodos[i] = crearNodo(byte,reps);
        printf("%d - %d\n", byte, reps);
    }

    fclose(datos);

    return tam;
}
*/
