#! /bin/bash
gcc comp.c colaprioridad.c pila.c huffman.c timpo.c -o comp.out
gcc deco.c colaprioridad.c pila.c huffman.c timpo.c -o comp.out

prueba = (Black Magic Woman.mp4
    English File Int.pdf
    IMG-20191220-WA0035.jpg
    IMG-20191223-WA0035.jpg
    Ley de Simpson.pptx 
    Libro De Redes Neuronales.pdf
    P+V 2019.rar
    Polinomio.docx
    Sonidero_mezcla.wav
    TablaChida.xlsx
    Feed Forward.png)

echo -e "Resultados de prueba" > salida.txt
for i in ${pruebas[@]}
do
./comp.out "i" >> salida.txt
./deco.out "i" >> salida.txt
done
