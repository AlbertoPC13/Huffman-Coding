#include "huffman.h"
#include "pila.h"

int main(int argc, char const *argv[])
{
  nodo arbolHuffman;
  nodo *nodos;
  TIPO posicion = 0, capacidad = 0;
  char cadenaCodigos[TAMMAX];
  char nombre[100];

  strcpy(nombre, argv[1]);

  FILE *archivo = fopen(nombre, "rb");

  fseek(archivo, 0, SEEK_END);
  long long int tamano_archivo = ftell(archivo);
  fseek(archivo, 0, SEEK_SET);

  printf("Tamano de archivo original: %lld bytes\n\n", tamano_archivo);

  unsigned char *datos = malloc(tamano_archivo);
  memset(datos, 0, tamano_archivo);
  fread(datos, 1, tamano_archivo, archivo);
  fclose(archivo);

  int cubetas[256];
  memset(cubetas, 0, 256 * sizeof(int));
  int i, j;

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
  FILE *cargar = fopen("frecuencias.txt", "w");

  int k = 0;
  fprintf(cargar, "copy-%s", nombre);
  fprintf(cargar, "\n%d ", capacidad);
  while (!esVacia(&pila))
  {
    nodos[k] = crearNodo(pila.datos[pila.tope].byte, pila.datos[pila.tope].reps);
    fprintf(cargar, "\n%d %d", pila.datos[pila.tope].byte, pila.datos[pila.tope].reps);
    Pop(&pila);
    k++;
  }

  fclose(cargar);

  arbolHuffman = Huffman(nodos, capacidad);
  Codigo codigos[256];
  for (i = 0; i < 256; i++)
    codigos[i].longitud = -1;

  imprimirCodigos(arbolHuffman, cadenaCodigos, posicion, codigos);

  /*Haciendo la compresion del archivo*/
  int cont = 8;
  unsigned char res = 0;
  FILE *archcomp = fopen("codificacion.dat", "wb");

  for (i = 0; i < tamano_archivo; i++) //For para recorrer el archivo
  {

    int tam = codigos[datos[i]].longitud;
    char *cadena = codigos[datos[i]].cadena;

    for (j = 0; j < tam; j++)
    {
      if (cadena[j] == '1')
        res += 1 << (cont - 1);

      cont--;

      if (cont == 0)
      {
        cont = 8;
        //Se va al archivo
        fputc(res, archcomp);
        res = 0;
      }
    }
  }

  if (cont != 8)
    fputc(res, archcomp);

  int tam_original=tamano_archivo;
  fseek(archcomp, 0, SEEK_END);
  tamano_archivo = ftell(archcomp);

  printf("\nNombre\t\tTam archivo bytes\tTam comprimido bytes\tTam comprimido bits\t Porcentaje\n");
  printf("%s\t\t", nombre);
  printf("%lld bytes\t\t", tam_original);
  printf("%lld bytes\t\t", tamano_archivo);
  printf("%lld bits\t\t", tamano_archivo * 8);
  printf("%.3f %%\n",(float)(100-((float)tamano_archivo*100/(float)tam_original)));
  fclose(archcomp);
  return 0;
}
