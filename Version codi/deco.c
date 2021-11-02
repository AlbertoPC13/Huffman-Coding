#include "huffman.h"

int main()
{
    nodo arbolHuffman;
    nodo *nodos;
    TIPO posicion = 0, capacidad = 0;
    char cadenaCodigos[TAMMAX];
    int i;

    FILE *datos = fopen("repeticiones.txt","rb");
    int numero, tam, byte, reps;

    fscanf(datos,"%d",&tam);
    printf("%d\n",tam);

    nodos = (nodo *)malloc(sizeof(nodo) * tam);

    i = 0;
    while (!feof(datos))
    {
        fscanf(datos,"%d",&byte);
        nodos[i]->caracter = (unsigned char)byte;
        fscanf(datos,"%d",&reps);
        nodos[i]->frecuencia = reps;
        printf("%d - %d\n",byte,reps);
        i++;
    }
    fclose(datos);

    //arbolHuffman = Huffman(nodos, tam);
    /*printf("\nCaracter  codigo \n");
    Codigo codigos[256];
    for (i = 0; i < 256; i++)
        codigos[i].longitud = -1;

    imprimirCodigos(arbolHuffman, cadenaCodigos, posicion, codigos);

    printf("\n\n");
    for (i = 0; i < 256; i++)
    {
        if (codigos[i].longitud != -1)
        {
            printf("%c - %s - %d\n", i, codigos[i].cadena, codigos[i].longitud);
        }
    }*/

    return 0;
}