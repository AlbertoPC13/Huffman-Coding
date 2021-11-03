#include "colaprioridad.h"
#include <string.h>
#define PESOBIT(bpos) 1<<bpos
#define CONSULTARBIT(var,bpos) (*(unsigned*)&var & PESOBIT(bpos))?1:0
#define PONE_1(var,bpos) *(unsigned*)&var |= PESOBIT(bpos)
#define PONE_0(var,bpos) *(unsigned*)&var &= ~(PESOBIT(bpos))
#define CAMBIA(var,bpos) *(unsigned*)&var ^= PESOBIT(bpos)
#define TAMMAX 60

typedef struct Codigo
{
    char* cadena;
    int longitud;
} Codigo;


nodo Huffman(nodo* nodos, TIPO tam);
void imprimirCodigos(nodo arbolHuffman, char cadenaCodigos[], TIPO posicion, Codigo *codigos);
char* Codigos(char cadenaCodigos[], TIPO n);
int adquirirNodos(nodo* nodos);


