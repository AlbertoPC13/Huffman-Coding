#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tiempo.h"
#include "huffman.h"
#include "pila.h"

int main(int argc, char const *argv[])
{
  double sumwtime, utime0, stime0, wtime0,utime1, stime1, wtime1; //Variables para medición de tiempos
  uswtime(&utime0, &stime0, &wtime0);//Inicia el conteo
  nodo arbolHuffman;
  nodo *nodos;
  TIPO posicion = 0, capacidad = 0;
  char cadenaCodigos[TAMMAX];
  char nombre[100];

  //Se adquiere el nombre del archivo a comprimir por medio de los argumentos en la ejecucion
  strcpy(nombre, argv[1]);

  //Se abre el archivo a comprimir con modo de lectura de bytes
  FILE *archivo = fopen(nombre, "rb");
  //Se posiciona en la posicion 0 y busca el final
  fseek(archivo, 0, SEEK_END);
  long long int tamano_archivo = ftell(archivo);
  //Se posiciona de nuevo en la posicion 0
  fseek(archivo, 0, SEEK_SET);

  printf("Tamano de archivo original: %lld bytes\n\n", tamano_archivo);

  //Se crea un arreglo del tamano del archivo para almacenar sus bytes
  unsigned char *datos = malloc(tamano_archivo);
  //Se pone todo el arreglo en 0
  memset(datos, 0, tamano_archivo);
  //Se leen y almacenan los bytes del archivo en el arreglo de datos
  fread(datos, 1, tamano_archivo, archivo);
  //Se cierra el archivo a comprimir
  fclose(archivo);

  //Se crea un arreglo de enteros para guardar las recurrencias de bytes con metodo cubetas
  int cubetas[256];
  //Se inician las cubetas en 0
  memset(cubetas, 0, 256 * sizeof(int));
  int i, j;

  //Se hace el metodo cubetas para todos los bytes de los datos
  for (i = 0; i < tamano_archivo; i++)
  {
    cubetas[datos[i]]++;
  }

  //Se crea una pila y se inicializa en un tope de -1
  Pila pila;
  pila.tope = -1;

  //Se recorren las cubetas correspondientes a los bytes
  for (i = 0; i < 256; i++)
  {
    //si su frecuencia es mayor a 0, inserta a la pila
    if (cubetas[i] > 0)
    {
      //crea estructura temporal de los caracteres con sus frecuencias
      Par nuevoPar;
      nuevoPar.byte = (unsigned char)i;
      nuevoPar.reps = cubetas[i];
      //inserta en la pila la estructura
      Push(&pila, nuevoPar);
    }
  }
  //obtiene la capacidad que tendra
  capacidad = tamPila(&pila);

  nodos = (nodo *)malloc(sizeof(nodo) * capacidad);
  //abre el archivo de frecuencias
  FILE *cargar = fopen("frecuencias.txt", "w");

  int k = 0;
  fprintf(cargar, "copy-%s", nombre);
  fprintf(cargar, "\n%d ", capacidad);
  while (!esVacia(&pila))
  {
    //crea nodos con los datos obtenidos de la pila
    nodos[k] = crearNodo(pila.datos[pila.tope].byte, pila.datos[pila.tope].reps);
    fprintf(cargar, "\n%d %d", pila.datos[pila.tope].byte, pila.datos[pila.tope].reps);
    //saca el elemento del tope
    Pop(&pila);
    k++;
  }

  //cierra el archivo
  fclose(cargar);
  //crea el arbol de huffman con los nodos creados
  arbolHuffman = Huffman(nodos, capacidad);
  Codigo codigos[256];
  //inicializa las longitudes a -1
  for (i = 0; i < 256; i++)
    codigos[i].longitud = -1;
  //crea la cadena de caracteres con su respectivos codigos
  imprimirCodigos(arbolHuffman, cadenaCodigos, posicion, codigos);

  /*Haciendo la compresion del archivo*/
  int cont = 8;                                     //Variable para contar grupos de 8 bits
  unsigned char res = 0;                            // Variable para almacenar el resultado de un byte
  FILE *archcomp = fopen("codificacion.dat", "wb"); //Abre el archivo codificacion y escribe en bytes

  for (i = 0; i < tamano_archivo; i++) //For para recorrer el archivo
  {
    int tam = codigos[datos[i]].longitud;    //Se obtiene el tamanio de la cadena asiganda a cada byte
    char *cadena = codigos[datos[i]].cadena; //Se obtiene la cadena

    for (j = 0; j < tam; j++) //El for se realziara hasta acabar con el tamanio de la cadena asignada
    {
      if (cadena[j] == '1')     //Si encuentra un 1, se realiza un corrimiento a la izqueirda del contador - 1
        res += 1 << (cont - 1); //Se realiza el corrimiento y se guarda en la varable res

      cont--; //Se decremena el contador

      if (cont == 0) // Si el contrador llega a 0, lo inicializamos de nuevo a 8
      {
        cont = 8;             //Incializamos cont a 8
        fputc(res, archcomp); //Se escribe en el archivo en forma de caracter el resultado
        res = 0;              //Inicialimos de nuevo res en 0
      }
    }
  }

  if (cont != 8)          //Si no se completo el byte, se copleta con relleno
    fputc(res, archcomp); //Se escribe en el archivo en forma de caracter el resultado
  //obtiene el tamaño original del archivo
  int tam_original = tamano_archivo;
  fseek(archcomp, 0, SEEK_END);
  tamano_archivo = ftell(archcomp);
  //se imprime los datos necesarios acerca de la compresion
  printf("\nNombre\t\tTam archivo bytes\tTam comprimido bytes\tTam comprimido bits\t Porcentaje\n");
  printf("%s\t\t", nombre);
  printf("%lld bytes\t\t", tam_original);
  printf("%lld bytes\t\t", tamano_archivo);
  printf("%lld bits\t\t", tamano_archivo * 8);
  printf("%.3f %%\n", (float)(100 - ((float)tamano_archivo * 100 / (float)tam_original)));
  fclose(archcomp);

  uswtime(&utime1, &stime1, &wtime1);//Evalua los tiempos de ejecucion
  printf("\nreal (Tiempo total)\t user(Tiempo CPU)\t sys (Tiempo E/S)\t CPU/Wall\n");
	printf("%.10e\t",  wtime1 - wtime0);
	printf("%.10e\t",  utime1 - utime0);
	printf("%.10e\t",  stime1 - stime0);
	printf("%.10f %%\t\n",100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
  return 0;
}
