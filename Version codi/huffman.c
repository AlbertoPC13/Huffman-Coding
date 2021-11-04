#include "huffman.h"
nodo Huffman(nodo *nodos, TIPO tam)
{
    //verifica si los nodos no son nulos
    if(!nodos){
        perror("Recibe nodos NULL o vacios Huffman(2)");
        exit(-2);
    }
    //inicializa sus ramas
    nodo izquierda, derecha, nuevoNodo;
    //crea la cola de prioridad (implementacion con Heaps)
    monticulo colaprioridad = construirMinHeap(nodos, tam);
    
    //mientras el tamaño no sea uno (ultimo arbol creado)
    while (colaprioridad->tam != 1)  
    {
        //obtiene el primer elemento de la cola
        izquierda = extractMin(colaprioridad);
        //obtiene el segundo elemento de la cola
        derecha = extractMin(colaprioridad);
        //crea el nodo con las frecuencas de los elementos obtenidos (su caracter es vacio)
        nuevoNodo = crearNodo('\0', izquierda->frecuencia + derecha->frecuencia);
        //le asigna como hijos (hojas) los elementos obtenidos
        nuevoNodo->izquierda = izquierda;
        nuevoNodo->derecha = derecha;
        //el mini arbol creado, se inserta a la cola de prioridad
        insertar(colaprioridad, nuevoNodo);
    }
    //obtiene el elemento mas pequeño
    return extractMin(colaprioridad);
}
char* Codigos(char cadenaCodigos[], TIPO n)
{
    int i;
    //solicita memoria para la cadena nueva
    char* cadena=malloc(sizeof(char*)*n);
    //crea la cadena hasta la posicion ingresada
    for (i = 0; i < n; ++i)
        cadena[i]= cadenaCodigos[i];
        //se le asigna al final el caracter vacio
    cadena[i]='\0';
    //retorna la cadena creada
    return cadena;
}
void imprimirCodigos(nodo arbolHuffman, char cadenaCodigos[], TIPO posicion, Codigo *codigos)
{
    //Valida si el arbol no es nulo
    if(!arbolHuffman){
        perror("Recibe un nodo NULL o vacio imprimirCodigos(3)");
        exit(-2);
    }
    //Valida si el arbol tiene una rama izquierda
    if (arbolHuffman->izquierda)
    {
        //Asigna a la cadena de codigo un bit '0'
        cadenaCodigos[posicion] = '0';
        //Se llama recursivamente a la funcion imprimirCodigos mandando el nodo izquierdo y aumentando la posicion en una unidad
        imprimirCodigos(arbolHuffman->izquierda, cadenaCodigos, posicion + 1, codigos);
    }
    //Valida si el arbol tiene una rama derecha
    if (arbolHuffman->derecha)
    {
        //Asigna a la cadena de codigo un bit '1'
        cadenaCodigos[posicion] = '1';
        //Se llama recursivamente a la funcion imprimirCodigos mandando el nodo derecho y aumentando la posicion en una unidad 
        imprimirCodigos(arbolHuffman->derecha, cadenaCodigos, posicion + 1, codigos);
    }
    //Valida si la posicion actual correspone a un nodo hoja
    if (esHoja(arbolHuffman->izquierda, arbolHuffman->derecha))
    {
        //Se reserva memoria dinamica para el codigo del byte que se encuentra en la hoja
        codigos[arbolHuffman->caracter].cadena = (char *)malloc(sizeof(posicion));
        //Se almacena el codigo del byte en la hoja
        codigos[arbolHuffman->caracter].cadena = Codigos(cadenaCodigos, posicion);
        // se almacena la longitud del codigo del byte correspondiente
        codigos[arbolHuffman->caracter].longitud = posicion;
    }
}
