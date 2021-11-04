#include "colaprioridad.h"
#include <string.h>

#define TAMMAX 60//tamaño maximo que puede tener cada cadena

//Se define la estructura Codigo
typedef struct Codigo
{
    //Se asigna un miembro para almacenar la cadena de bits en formato char
    char* cadena;
    //Se agrega un miembro para almacenar la longitud del codigo
    int longitud;
} Codigo;

/**
 * Función: Huffman
 * Descripcion: crea el arbol de Huffman a partir de los nodos recibidos
 * Recibe: 
 *  - arreglo de nodos
 *  - tamano del arreglo de nodos
 * Regresa:
 *  - nodo creado
 * Errores: ninguno
*/
nodo Huffman(nodo* nodos, TIPO tam);
/**
 * Función:imprimir codigos
 * Descripcion: crea los codigos apartir del arbol creado
 * Recibe: 
 *  - arbol
 *  - cadena de codigos
 *  - posicion del nodo visitado
 *  - cadena de estructuras de los codigos
 * Regresa:
 *  - void
 * Errores: ninguno
*/
void imprimirCodigos(nodo arbolHuffman, char cadenaCodigos[], TIPO posicion, Codigo *codigos);
/**
 * Función:codigos
 * Descripcion: crea la cadena con los codigos correspondientes al caracter
 * Recibe: 
 *  - cadena de los codigos
 *  - tamaño de la cadena
 * Regresa:
 *  - cadea de codigo obtenida
 * Errores: ninguno
*/
char* Codigos(char cadenaCodigos[], TIPO n);



