#include "huffman.h"
#include "pila.h"
#define PESOBIT(bpos) (1 << bpos)
#define CONSULTARBIT(var, bpos) ((*(unsigned *)&var & PESOBIT(bpos)) ? 1 : 0)
#define PONE_1(var, bpos) (*(unsigned *)&var |= PESOBIT(bpos))
#define PONE_0(var, bpos) (*(unsigned *)&var &= ~(PESOBIT(bpos)))
#define CAMBIA(var, bpos) (*(unsigned *)&var ^= PESOBIT(bpos))

int main()
{
  nodo arbolHuffman;
  nodo *nodos;
  unsigned tam_archivo = 0;
  TIPO posicion = 0, capacidad = 0;
  char cadenaCodigos[TAMMAX];

  FILE *archivo = fopen("Sonidero_mezcla.wav", "rb");

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
  FILE *cargar = fopen("recurrencias.bin", "wb");

  int k = 0;
  fprintf(cargar, "%d\n", capacidad);
  while (!esVacia(&pila))
  {
    nodos[k] = crearNodo(pila.datos[pila.tope].byte, pila.datos[pila.tope].reps);
    printf("\n%c - %d", pila.datos[pila.tope].byte, pila.datos[pila.tope].reps);
    fprintf(cargar, "%d-%d\n", pila.datos[pila.tope].byte, pila.datos[pila.tope].reps);
    Pop(&pila);
    k++;
  }

  fclose(cargar);

  arbolHuffman = Huffman(nodos, capacidad);
  printf("\nCaracter  codigo \n");
  Codigo codigos[256];
  for (int i = 0; i < 256; i++)
    codigos[i].longitud = -1;

  imprimirCodigos(arbolHuffman, cadenaCodigos, posicion, codigos, &tam_archivo);

  printf("\n\n");
  for (int i = 0; i < 256; i++)
  {
    if (codigos[i].longitud != -1)
    {
      printf("%c - %s - %d\n", i, codigos[i].cadena, codigos[i].longitud);
    }
  }
  printf("\ntam total: %d\n", tam_archivo);
  
  cargar = fopen("recurrencias.bin", "rb+");
  fseek(archivo, 0, SEEK_END);
  fprintf(cargar, "%d\n",tam_archivo);
  fclose(cargar);

  archivo = fopen("Sonidero_mezcla.wav", "rb");

  FILE *codi = fopen("binario.dat", "wb");

  //char* cadena_cerosunos=(char*)malloc(sizeof(char)*tam_archivo);
  unsigned char c;
  int i = 0;
  k = 0;
  unsigned char cadena_cerosunos = 0; //00000000
  
  fseek(archivo, 0, SEEK_END);
  tamano_archivo = ftell(archivo);
  fseek(archivo, 0, SEEK_SET);

  for(int l = 0; l < tamano_archivo; l++)
  {
    c = fgetc(archivo);
    /// frecuencia*cadena   1000
    /// 10100=20    fputc a= 101  b=111 c=1 d=0
    // 00000
    //printf("letra: %c\t", c);
    //printf("cadena: %s\t", codigos[c].cadena);

    for (i = 0; i < codigos[c].longitud; i++, k++) //10011111  
    {
      //printf("bit: %c\t", codigos[c].cadena[i]);
      if (codigos[c].cadena[i] == '1')
      {
        PONE_1(cadena_cerosunos, 7 - k);
      }
      if (k == 7)
      {
        k = -1;
        fputc(cadena_cerosunos,codi);
        cadena_cerosunos = 0;
      }
    }
  }

  if(k != 0)
    fputc(cadena_cerosunos,codi);

  //printf("\t%c-%s\n",c,codigos[c].cadena);
  fclose(codi);
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

  char [255]   
 */
}