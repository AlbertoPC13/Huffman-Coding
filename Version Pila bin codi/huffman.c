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
    TIPO i;
    char* cadena=malloc(sizeof(char*)*n);
    for (i = 0; i < n; ++i)
        cadena[i]= cadenaCodigos[i];
    cadena[i]='\0';
    return cadena;
}
void imprimirCodigos(nodo arbolHuffman, char cadenaCodigos[], TIPO posicion, Codigo *codigos,unsigned int* tam_archivo)
{
    if(!arbolHuffman){
        perror("Recibe un nodo NULL o vacio imprimirCodigos(3)");
        exit(-2);
    }
    if (arbolHuffman->izquierda)
    {
        cadenaCodigos[posicion] = '0';
        imprimirCodigos(arbolHuffman->izquierda, cadenaCodigos, posicion + 1, codigos,tam_archivo);
    }
    if (arbolHuffman->derecha)
    {
        cadenaCodigos[posicion] = '1'; // 11001
        imprimirCodigos(arbolHuffman->derecha, cadenaCodigos, posicion + 1, codigos,tam_archivo);
    }
    if (esHoja(arbolHuffman->izquierda, arbolHuffman->derecha))
    {
        //11001
        printf("\n\ttamaa1: %d\t",*tam_archivo);
        codigos[arbolHuffman->caracter].cadena = (char *)malloc(sizeof(char)*posicion);
        codigos[arbolHuffman->caracter].cadena = Codigos(cadenaCodigos, posicion);
        codigos[arbolHuffman->caracter].longitud = posicion; 
        *tam_archivo+=arbolHuffman->frecuencia * posicion;
        printf("\n\ttamaa: %d\t",*tam_archivo);
        printf("%c %s\n", arbolHuffman->caracter,Codigos(cadenaCodigos, posicion));
        //Codigos(cadenaCodigos, posicion);
    }
}

/* void crearCadenaCodigos(nodo arbolHuffman,char* cadenaCodigos[TAMMAX],char codigos[], TIPO posicion)
{
    if(!arbolHuffman){
        perror("Recibe un nodo NULL o vacio crearCadenaCodigos(3)");
        exit(-2);
    }
    if (arbolHuffman->izquierda)
    {
        codigos[posicion] = '0';
        crearCadenaCodigos(arbolHuffman->izquierda, cadenaCodigos, codigos,posicion + 1);
    }
    if (arbolHuffman->derecha)
    {
        codigos[posicion] = '1';
        crearCadenaCodigos(arbolHuffman->derecha, cadenaCodigos, codigos, posicion + 1);
    }
    if (esHoja(arbolHuffman->izquierda, arbolHuffman->derecha))
    {
       strcpy(cadenaCodigos[arbolHuffman->caracter],codigos);
    }
} */