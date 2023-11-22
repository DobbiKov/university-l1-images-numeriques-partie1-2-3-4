#include <stdexcept>
/** @file
 * Lecture et ecriture d'images en niveau de gris au format PGM
 **/
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

/// BEGIN ImageGris

/** Structure de donnees pour representer une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;

double inverseGreyPixel(double pixel);
/// END ImageGris

/// BEGIN lirePGM

/** Construire une image en teintes de gris depuis un fichier PGM
 * @param source le nom d'un fichier PGM
 * @return une image en teintes de gris
 **/
ImageGris lirePGM(string source) {
    ifstream file;
    file.open(source);
    if(!file)
        throw runtime_error("The file doesn't exist.");
        
    string temp;
    file >> temp;
    
    int width, height, colors;
    file >> width;
    file >> height;
    file >> colors;

    ImageGris tab = ImageGris(height);
    for(int i = 0; i < height; i++){
        tab[i] = vector<double>(width);
    }
    
    double value;
    int ligne, colonne;
    ligne = 0;
    colonne = 0;
    while(file >> value){

        tab[ligne][colonne] = value;

        colonne++;
        if(colonne >= width){
            colonne = 0;
            ligne++;
        }
    }

    return tab;
}

/// BEGIN ecrirePGM

/** Ecrit une image en teintes de gris dans un fichier PGM
 * @param img une image en teintes de gris
 * @param cible le nom d'un fichier PGM
 **/
void ecrirePGM(ImageGris img, string cible) {
    ofstream file;
    file.open(cible);
    if(!file)
        throw runtime_error("The problem was occurd while opening or creating the file: " + cible);
    
    if(img.size() == 0)
        throw runtime_error("The array is empty");
    if(img[0].size() == 0)
        throw runtime_error("The array is empty");
    int heigth = img.size();
    int width = img[0].size();
    file << "P2\n";
    file << width << " " << heigth << endl;
    file << "255\n";
    for(vector<double> ligne : img){
        for(double elem : ligne){
            file << (int)elem << " ";
        }
        file << endl;
    }
}

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

