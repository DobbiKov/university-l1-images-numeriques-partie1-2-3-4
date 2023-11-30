#include <stdexcept>
/** @file
 * Lecture et ecriture d'images en niveau de gris au format PGM
 **/
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

#include "iopgm/iopgm.hpp"
using namespace std;

/// BEGIN ImageGris

/** Structure de donnees pour representer une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;

double inverseGreyPixel(double pixel);
/// END ImageGris

/// BEGIN lirePGM

/** Construit une image cliché d'une image en niveau de gris
 * @param img une image en niveau de gris
 * @return l'image cliché qui inverse les niveaux de gris
 **/
ImageGris inversePGM(ImageGris img) {
    if(img.size() == 0)
        throw runtime_error("The array is empty.");
    if(img[0].size() == 0)
        throw runtime_error("The array is empty.");
    int heigth = img.size();
    int width = img[0].size();
    ImageGris newImg = ImageGris(heigth);
    for(int i = 0; i < heigth; i++){
        newImg[i] = vector<double>(width);
    }

    for(int i = 0; i < heigth; i++){
        for(int j = 0; j < width; j++){
            newImg[i][j] = inverseGreyPixel(img[i][j]);
        }
    }

    return newImg;
    

}

double inverseGreyPixel(double pixel) { return 255 - pixel; }

void lirePGMTest(){
    cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
    ecrirePGM(lirePGM("images/brain.pgm"),  "pgm/brain.pgm");
    ecrirePGM(lirePGM("images/illusion.pgm"),  "pgm/illusion.pgm");
}

void inversePGMTest() {
    ImageGris imageOriginale;
    cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
    imageOriginale = lirePGM("images/brain.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "pgm/brain-inverse.pgm");
    imageOriginale = lirePGM("images/illusion.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "pgm/illusion-inverse.pgm");
}

int main() {
    lirePGMTest();
    inversePGMTest();
    return 0;
}

