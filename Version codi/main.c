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
  int cont = 8; //Variable para contar grupos de 8 bits
  unsigned char res = 0; // Variable para almacenar el resultado de un byte
  FILE *archcomp = fopen("codificacion.dat", "wb"); //Abre el archivo codificacion y escribe en bytes

  for (i = 0; i < tamano_archivo; i++) //For para recorrer el archivo
  {
    int tam = codigos[datos[i]].longitud; //Se obtiene el tamanio de la cadena asiganda a cada byte
    char *cadena = codigos[datos[i]].cadena; //Se obtiene la cadena

    for (j = 0; j < tam; j++)//El for se realziara hasta acabar con el tamanio de la cadena asignada
    {
      if (cadena[j] == '1') //Si encuentra un 1, se realiza un corrimiento a la izqueirda del contador - 1
        res += 1 << (cont - 1); //Se realiza el corrimiento y se guarda en la varable res

      cont--; //Se decremena el contador

      if (cont == 0) // Si el contrador llega a 0, lo inicializamos de nuevo a 8
      {
        cont = 8;//Incializamos cont a 8
        fputc(res, archcomp); //Se escribe en el archivo en forma de caracter el resultado
        res = 0; //Inicialimos de nuevo res en 0 
      }
    }
  }

  if (cont != 8) //Si no se completo el byte, se copleta con relleno 
    fputc(res, archcomp); //Se escribe en el archivo en forma de caracter el resultado

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
