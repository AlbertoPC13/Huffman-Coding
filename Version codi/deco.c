#include "huffman.h"
#define PESOBIT(bpos) 1<<bpos
#define CONSULTARBIT(var,bpos) (*(unsigned*)&var & PESOBIT(bpos))?1:0
#define PONE_1(var,bpos) *(unsigned*)&var |= PESOBIT(bpos)
#define PONE_0(var,bpos) *(unsigned*)&var &= ~(PESOBIT(bpos))
#define CAMBIA(var,bpos) *(unsigned*)&var ^= PESOBIT(bpos)

/*
Funcion Decodificacion
Resumen: Descomprime el archivo comprimido
Errores: Ninguno
Parametros: Ninguno
*/
int main()
{
    //Declaracion e inicializacion de variables
    nodo arbolHuffman;
    nodo *nodos;
    TIPO posicion = 0, capacidad = 0, reps = 0;
    char cadenaCodigos[TAMMAX];
    char *nombre;
    unsigned char byte;
    long long int tamProb = 0;

    int i;

    nombre = (char *)malloc(100 * sizeof(char)); //Reservamos memoria para la cadena del nombre del archivo
    FILE *datos = fopen("frecuencias.txt", "rb"); //Se abre el archivo frecuencias.txt en forma de bytes
    fscanf(datos,"%s",nombre); //Se lee el nombre del archivo y se guarda en la variable nombre
    fscanf(datos, "%d", &capacidad); //Se lee la cantidad de nodos y se guarda en la variable capacidad

    nodos = (nodo *)malloc(sizeof(nodo) * capacidad); /*Reserva memoria para la cantidad de nodos encontrados en frecuencias.txt*/

    for (i = 0; i < capacidad; i++)//For para recorrer el archivo de frecuencas
    {
        fscanf(datos, "%d", &byte); //Se lee el caracter
        fscanf(datos, "%d", &reps); //Se lee las frecuencias del caracter
        tamProb += reps; //Aumentamos la variable del tamanio del problema
        nodos[i] = crearNodo(byte, reps); //Creamos nodos con el caracter y la frecuencia
    }

    fclose(datos);//Cerramos el archivo

    printf("Nombre\t\t\tTam archivo\n");//Se da formato a la impresion de pantalla
    printf("%-20s\t\t",nombre);
    printf("%10d bytes\n",tamProb);
    arbolHuffman = Huffman(nodos, capacidad);//Creamos el arbol de huffman
    FILE *archivo = fopen("codificacion.dat", "rb");//Abrimos el archivo codificacion.dat y lo leemos en bytes
    FILE *nuevo = fopen(nombre, "wb");//Creamos un archivo nuevo donde recuperaremos el archivo original
    nodo temp=arbolHuffman; //Creamos un nodo temporal que apunta a la raiz del arbol
    while(tamProb){ //Mientras no hayamos recuperado el tamanio original del archivo 
        unsigned char aux = fgetc(archivo);//Le asignamos un caracter a aux
        for(i=7; i>=0;i--){ //Se realiza un for para analizar cada bit
            if(CONSULTARBIT(aux,i)) // Consultamos si el bit es 1
            {
                temp = temp->derecha; //Se va por la derecha
            }
            else if(!CONSULTARBIT(aux,i)) //Consultamos si el bit es 0
            {
                temp = temp->izquierda; //Se va por la izquierda
            } 
            if(esHoja(temp->izquierda,temp->derecha)) //Revisa si ya llegamos a una hoja o caracter
            {
                fwrite(&(temp->caracter),1,sizeof(temp->caracter),nuevo);//Escribe en el archivo el caracter encontrado
                tamProb--;//Disminuye el tamanio de problema
                temp = arbolHuffman;//Se le asigna a temp la raiz del arbol
            }
        }
    }

    return 0;
}