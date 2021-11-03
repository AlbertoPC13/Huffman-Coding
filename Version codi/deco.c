#include "huffman.h"
#define PESOBIT(bpos) 1<<bpos
#define CONSULTARBIT(var,bpos) (*(unsigned*)&var & PESOBIT(bpos))?1:0
#define PONE_1(var,bpos) *(unsigned*)&var |= PESOBIT(bpos)
#define PONE_0(var,bpos) *(unsigned*)&var &= ~(PESOBIT(bpos))
#define CAMBIA(var,bpos) *(unsigned*)&var ^= PESOBIT(bpos)

int main()
{
    nodo arbolHuffman;
    nodo *nodos;
    TIPO posicion = 0, capacidad = 0, reps = 0;
    char cadenaCodigos[TAMMAX];
    unsigned char byte;
    long long int tamProb = 0;

    int i;

    FILE *datos = fopen("repeticiones.txt", "r");

    fscanf(datos, "%d", &capacidad);
    printf("%d\n", capacidad);

    nodos = (nodo *)malloc(sizeof(nodo) * capacidad);

    for (i = 0; !feof(datos); i++)
    {
        fscanf(datos, "%d", &byte);
        fscanf(datos, "%d", &reps);
        tamProb += reps;
        nodos[i] = crearNodo(byte, reps);
        //printf("%d - %d\n", byte, reps);
    }

    fclose(datos);

    arbolHuffman = Huffman(nodos, capacidad);
    
    FILE *archivo = fopen("archivoComprimido.bin", "rb");
    FILE *nuevo = fopen("nuevo.wav", "wb");
    nodo temp=arbolHuffman;
    
    while(tamProb){
        unsigned char aux = fgetc(archivo);
        for(i=7; i>=0;i--){
            if(CONSULTARBIT(aux,i))
            {
                temp = temp->derecha;
            }
            else if(!CONSULTARBIT(aux,i))
            {
                temp = temp->izquierda;
            }
            if(esHoja(temp->izquierda,temp->derecha))
            {
                fwrite(&(temp->caracter),1,sizeof(temp->caracter),nuevo);
                tamProb--;
                temp = arbolHuffman;
                //fwrite(&cadena, 1, sizeof(cadena), archivo);
            }
        }
    }

    printf("\nArchivo descomprimido uwu");

    return 0;
}