#include "huffman.h"
#include "pila.h"

int main()
{
  nodo arbolHuffman;
  nodo *nodos;
  //apcodigos* codigos;
  TIPO posicion = 0, capacidad = 0;
  char cadenaCodigos[TAMMAX];

  FILE *archivo = fopen("/home/beto-pc/Escritorio/hola.txt", "rb");

  fseek(archivo, 0, SEEK_END);
  long tamano_archivo = ftell(archivo);
  fseek(archivo, 0, SEEK_SET);

  unsigned char *datos = malloc(tamano_archivo);
  memset(datos, 0, tamano_archivo);
  fread(datos, 1, tamano_archivo, archivo);
  fclose(archivo);


  int cubetas[256];
  memset(cubetas, 0, 256 * sizeof(int));

  for (int i = 0; i < tamano_archivo; i++)
  {
    cubetas[datos[i]]++;
  }

  Pila pila;
  pila.tope = -1;

  for (int i = 0; i < 256; i++)
  {
    if (cubetas[i] > 0)
    {
      Par nuevoPar;
      nuevoPar.byte = (unsigned char)i;
      nuevoPar.reps = cubetas[i];
      Push(&pila, nuevoPar);
    }
  }

  capacidad = tamPila(&pila);

  nodos = (nodo *)malloc(sizeof(nodo) * capacidad);
  FILE *cargar = fopen("/home/beto-pc/Escritorio/recurrencias.bin", "wb");

  int k = 0;
  fprintf(cargar,"%d\n",capacidad);
  while (!esVacia(&pila))
  {
    nodos[k] = crearNodo(pila.datos[pila.tope].byte, pila.datos[pila.tope].reps);
    printf("\n%d - %d", pila.datos[pila.tope].byte, pila.datos[pila.tope].reps);
    fprintf(cargar,"%d-%d\n",pila.datos[pila.tope].byte,pila.datos[pila.tope].reps);
    Pop(&pila); 
    k++;
  }

  fclose(cargar);

  arbolHuffman = Huffman(nodos, capacidad);
  printf("\nCaracter  codigo \n");
  Codigo codigos[256];
  for (int i = 0; i < 256; i++)
    codigos[i].longitud = -1;

  imprimirCodigos(arbolHuffman, cadenaCodigos, posicion, codigos);

  printf("\n\n");
  for (int i = 0; i < 256; i++)
  {
    if(codigos[i].longitud != -1)
    {
        printf("%c - %s - %d\n",i,codigos[i].cadena,codigos[i].longitud);
    }
  }
  
  /* HuffmanCodes(arbolHuffman, codigos);

    printf("\n%c",codigos[1]->caracter); */
  /*
  a   0
  c   100
  b   101
  f   1100        
  e   1101        
  d   111

  char [255]   
 */
}