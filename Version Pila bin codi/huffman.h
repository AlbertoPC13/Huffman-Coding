#include "colaprioridad.h"
#include <string.h>
#define TAMMAX 60

typedef struct Codigo
{
    char* cadena;
    int longitud;
} Codigo;


nodo Huffman(nodo* nodos, TIPO tam);
void imprimirCodigos(nodo arbolHuffman, char cadenaCodigos[], TIPO posicion, Codigo *codigos,unsigned int* tam_archivo);
char* Codigos(char cadenaCodigos[], TIPO n);
/* void crearCadenaCodigos(nodo arbolHuffman,char* cadenaCodigos[TAMMAX],char codigos[], TIPO posicion); */