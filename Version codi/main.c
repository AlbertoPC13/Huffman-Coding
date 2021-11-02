#include "huffman.h"
#include "pila.h"

int main()
{
  nodo arbolHuffman;
  nodo *nodos;
  //apcodigos* codigos;
  TIPO posicion = 0, capacidad = 0;
  char cadenaCodigos[TAMMAX];

  FILE *archivo = fopen("inf.jpg", "rb");

  fseek(archivo, 0, SEEK_END);
  long tamano_archivo = ftell(archivo);
  fseek(archivo, 0, SEEK_SET);

  unsigned char *datos = malloc(tamano_archivo);
  memset(datos, 0, tamano_archivo);
  fread(datos, 1, tamano_archivo, archivo);
  fclose(archivo);


  int cubetas[256];
  memset(cubetas, 0, 256 * sizeof(int));
  int i,j;

  for (i = 0; i < tamano_archivo; i++)
  {
    cubetas[datos[i]]++;
  }

  Pila pila;
  pila.tope = -1;

  for (i = 0; i < 256; i++)
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
  FILE *cargar = fopen("repeticiones.txt", "w");

  int k = 0;
  fprintf(cargar,"%d ",capacidad);
  while (!esVacia(&pila))
  {
    nodos[k] = crearNodo(pila.datos[pila.tope].byte, pila.datos[pila.tope].reps);
    printf("\n%d - %d", pila.datos[pila.tope].byte, pila.datos[pila.tope].reps);
    fprintf(cargar,"%d %d ",pila.datos[pila.tope].byte,pila.datos[pila.tope].reps);
    Pop(&pila); 
    k++;
  }

  fclose(cargar);

  arbolHuffman = Huffman(nodos, capacidad);
  printf("\nCaracter  codigo \n");
  Codigo codigos[256];
  for (i = 0; i < 256; i++)
    codigos[i].longitud = -1;

  imprimirCodigos(arbolHuffman, cadenaCodigos, posicion, codigos);

  printf("\n\n");
  for (i = 0; i < 256; i++)
  {
    if(codigos[i].longitud != -1)
    {
        printf("%c - %s - %d\n",i,codigos[i].cadena,codigos[i].longitud);
    }
  }
  
  
  /*Haciendo la compresion del archivo*/
  int cont = 8;
  unsigned char res = 0;
  FILE *archcomp = fopen("archivoComprimido.bin", "wb");
  
  for(i = 0; i<tamano_archivo; i++)//For para recorrer el archivo
  {
  	
  	int tam = codigos[datos[i]].longitud;
 	char *cadena = codigos[datos[i]].cadena;
  	
  		for(j = 0; j<tam; j++)
		{
			if(cadena[j] == '1')
				res += 1<<(cont - 1);
			
			cont--;
			
			if(cont == 0)
			{
				cont = 8;
				//Se va al archivo
				fputc(res, archcomp);
				res = 0;	
			}
					
		}
  }
  
  if(cont != 8)
  	fputc(res, archcomp);
  
  fclose(archcomp);
  return 0;
  
  
  
  
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
