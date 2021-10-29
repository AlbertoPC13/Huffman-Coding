#include "colaprioridad.h"
#include <string.h>
#define TAMMAX 256
/* typedef struct HuffmanCodigos
{
    char caracter;
    TIPO frecuencia;
    char* codigo;
} HuffmanCodigos; 
typedef HuffmanCodigos* apcodigos;*/

nodo Huffman(nodo* nodos, TIPO tam);
void imprimirCodigos(nodo arbolHuffman, TIPO cadenaCodigos[], TIPO posicion);
void codigos(TIPO cadenaCodigos[], TIPO n);
/* void HuffmanCodes(nodo arbolHuffman,apcodigos* codiguitos); */
