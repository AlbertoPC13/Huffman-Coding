#include "huffman.h"
#include "pila.h"

int main()
{
    nodo arbolHuffman;
    nodo* nodos;
    //apcodigos* codigos;
    TIPO cadenaCodigos[TAMMAX], posicion = 0, capacidad = 0;
    
    FILE *archivo = fopen("/home/beto-pc/Escritorio/tux.jpg","rb");

    fseek(archivo,0,SEEK_END);
    long tamano_archivo = ftell(archivo);
    fseek(archivo,0,SEEK_SET);

    unsigned char *datos = malloc(tamano_archivo);
    memset(datos,0,tamano_archivo);
    fread(datos,1,tamano_archivo,archivo);

    int cubetas[256];
    memset(cubetas,0,256*sizeof(int));

    for (int i = 0; i < tamano_archivo; i++)
    {
      cubetas[datos[i]]++;
    }

    Pila pila;
    pila.tope = -1; 

    for (int i = 0; i < 256; i++)
    {
      if(cubetas[i] > 0)
      {
        Par nuevoPar;
        nuevoPar.byte = (unsigned char) i;
        nuevoPar.reps = cubetas[i];
        Push(&pila,nuevoPar);
      }
    }

    capacidad = tamPila(&pila);

    nodos=(nodo *)malloc(sizeof(nodo)*capacidad);

    int k = 0;

    while (!esVacia(&pila))
    {
      nodos[k] = crearNodo(pila.datos[pila.tope].byte,pila.datos[pila.tope].reps);
      printf("\n%d - %d",pila.datos[pila.tope].byte,pila.datos[pila.tope].reps);
      Pop(&pila);
      k++;
    }
  
    arbolHuffman = Huffman(nodos, capacidad);
    printf("\nCaracter  codigo \n");
    imprimirCodigos(arbolHuffman, cadenaCodigos, posicion);
    fclose(archivo);
    /* HuffmanCodes(arbolHuffman, codigos);

    printf("\n%c",codigos[1]->caracter); */
    /*
  a   0
  c   100
  b   101
  f   1100        
  e   1101        
  d   111
 */
}