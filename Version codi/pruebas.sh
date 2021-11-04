#! /bin/bash
gcc comp.c colaprioridad.c pila.c huffman.c tiempo.c -o comp.out
gcc deco.c colaprioridad.c huffman.c tiempo.c -o deco.out

pruebas=(
    "EnglishFileInt.pdf"
    "IMG-20191220-WA0035.jpg"
    "IMG-20191223-WA0035.jpg"
    "LeydeSimpson.pptx"
    "LibroDeRedesNeuronales.pdf"
    "P+V2019.rar"
    "Polinomio.docx"
    "TablaChida.xlsx"
    "FeedForward.png"
    "Sonidero_mezcla.wav"
    "BlackMagicWoman.mp4")

echo -e "Resultados de prueba" > salida.txt
for i in ${pruebas[@]}
do
echo -e "Compresión" >> salida.txt
./comp.out $i >> salida.txt
echo -e "Descompresión" >> salida.txt
./deco.out $i >> salida.txt
done
