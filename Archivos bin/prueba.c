#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    FILE *f = fopen("/home/beto-pc/Escritorio/recurrencias.bin", "rb");

    fseek(f, 0, SEEK_END);
    long tamano_archivo = ftell(f);
    fseek(f, 0, SEEK_SET);
    unsigned char *datos = malloc(tamano_archivo);

    fread(datos, 1, tamano_archivo, f);
    fclose(f);

    int fg = 0;
    printf("\n\nRecurrencias: \n\n");
    for (int i = 0; i < tamano_archivo; i++)
    {
        if (fg == 0)
        {
            printf("%d - ", datos[i]);
            fg = 1;
        }
        else if (fg == 2)
        {
            printf("%d\n", datos[i]);
            i++;
            fg = 0;
        }
        else
            fg = 2;
    }

    printf("\n\n");
    return 0;
}
