#include <stdio.h>
#include <stdlib.h>

#define TIPO int//tipo de dato
#define esHoja(izquierda, derecha) (!(izquierda) && !(derecha))//verifica si el nodo visitado es una hoja
//estructura nodo (miniarboles)
typedef struct Nodo
{
    unsigned char caracter;
    TIPO frecuencia;
    struct Nodo *izquierda;
    struct Nodo *derecha;
} Nodo;
//aputnador a nodo
typedef Nodo *nodo;

//estructura Monticulo
typedef struct Monticulo
{
    unsigned tam; //tamaño
    unsigned capacidad;//capacidad
    nodo *nodos;
} Monticulo;
//apuntador a monticulo
typedef Monticulo *monticulo;

/**
 * Función:crea nodo, que contiene el caracter y su frecuencia
 * Descripcion: con los datos ingresados, crea los nodos para despues ser utilizados en las otra funciones
 * Recibe: 
 *  - caracter
 *  - frecuencia del caracter
 * Regresa:
 *  - nodo creado
 * Errores: ninguno
*/
nodo crearNodo(unsigned char caracter, unsigned frecuencia);
/**
 * Función:crear Monticulo
 * Descripcion: inicializa la estructura monticulo (heap)
 * Recibe: 
 *  - la capacidad
 * Regresa:
 *  - monticulo creado creado
 * Errores: ninguno
*/
monticulo crearMonticulo(unsigned capacidad);
/**
 * Función:heapyfy
 * Descripcion: restaura la propiedad de los monticulos al borrar un elemento
 * Recibe: 
 *  - monticulo
 *  - la posicion
 * Regresa:
 *  - void
 * Errores: ninguno
*/
void Heapify(monticulo minHeap, TIPO posicion);
/**
 * Función:extractMin
 * Descripcion: extrae el elemento minimo de la cola de prioridad (pop) y lo elimina de la cola
 * Recibe: 
 *  - monticulo
 * Regresa:
 *  - nodo extraido
 * Errores: ninguno
*/
nodo extractMin(monticulo minHeap);
/**
 * Función:insertar
 * Descripcion: inserta un nodo (un mini arbol) a la estrucutra del monticulo (cola de prioridad)
 * Recibe: 
 *  - monticulo
 *  - miniarbol (nodo)
 * Regresa:
 *  - void
 * Errores: ninguno
*/
void insertar(monticulo minHeap, nodo miniArbol);
/**
 * Función:constri MinHeap
 * Descripcion: construye la estructura monticulo min (cola de prioridad) con los nodos y el tamaño ingresados
 * Recibe: 
 *  - nodos
 *  - tamaño
 * Regresa:
 *  - monticulo construido
 * Errores: ninguno
*/
monticulo construirMinHeap(nodo *nodos, TIPO tam);
