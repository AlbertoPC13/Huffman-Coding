#include "huffman.h"
int main()
{
    nodo arbolHuffman;
    nodo* nodos;
    //apcodigos* codigos;
    TIPO cadenaCodigos[TAMMAX], posicion = 0, capacidad = 256;
    nodos=(nodo *)malloc(sizeof(nodo)*capacidad);

    
    FILE *archivo = fopen("/home/beto-pc/Escritorio/aiura.txt","rb");

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

    for (int i = 0; i < 256; i++)
    {
      nodos[i]=crearNodo(i,cubetas[i]);
      printf("\n%c - %d",i,cubetas[i]); 
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