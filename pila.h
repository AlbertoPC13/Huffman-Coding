#include <stdio.h>
#define PILAMAX 256 //Se define como 256 el maximo de elementos por los bytes posibles

//Se define la estructura Par para los elementos de la pila
typedef struct Par
{
    //Se asigna un miembro para almacenar un byte
    unsigned char byte;
    //Se asigna un miembro para almacenar sus repeticiones
    int reps;
} Par;

//Se declara un apuntador de tipo Par
typedef Par *apPar;

//Se define la estructura Pila
typedef struct Pila
{
    //Se asigna un miembro para almacenar el tope
    int tope;
    //Se asigna un arreglo de tipo par para almacenar los elementos de la pila
    Par datos[PILAMAX];
} Pila;

//Se define un apuntador de tipo pila
typedef Pila *apPila;

/*
 * Funcion: Push
 * Descripcion: Se realiza la insercion de un elemento en el tope de la pila. Al llamar a la funcion se aumenta el tope de la pila
 *  y se inserta el elemento en el arreglo de la pila indexado con el nuevo tope    
 * Recibe:
 *  - Apuntador a pila
 *  - Estructura Par
 * Regresa:
 *  - void
 * Errores: ninguno
*/
void Push(apPila pila, Par par);

/*
 * Funcion: Pop
 * Descripcion: Se saca un elemento del tope de la pila, para ello se disminuye en una unidad el tope de la pila   
 * Recibe:
 *  - Apuntador a pila
 * Regresa:
 *  - void
 * Errores: ninguno
*/
void Pop(apPila pila);

/*
 * Funcion: tamPila
 * Descripcion: Se indica el tamano de la pila al devolver el tope de la pila mas una unidad debido al arreglo cero-indexado   
 * Recibe:
 *  - Apuntador a pila
 * Regresa:
 *  - Valor entero del tamano de pila (int)
 * Errores: ninguno
*/
int tamPila(apPila pila);

/*
 * Funcion: esVacia
 * Descripcion: Se indica si la pila se encuentra vacia al consultar si el valor del tope es menor que 0    
 * Recibe:
 *  - Apuntador a pila
 * Regresa:
 *  - Valor entero 0 si la pila no se encuentra vacia
 *  - Valor entero 1 si la pila se encuentra vacia
 * Errores: ninguno
*/
int esVacia(apPila pila);