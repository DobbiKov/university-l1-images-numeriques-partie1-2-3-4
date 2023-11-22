#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/
#include <cmath>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
using namespace std;

/** Structure de donnee pour representer une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;



/** Infrastructure minimale de test **/
#define CHECK(test) if (!(test)) cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl


/** Une image 4x4 en teintes de gris pour faire des tests **/
ImageGris imgGrisTest = {
    {0, 255, 54.213, 236.589},
    {18.411, 182.376, 200.787, 120},
    {139.583, 172.841, 94.0878, 88.4974},
    {158.278, 172.841, 89.0236, 80.0384}
};



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








/** Teste si deux images en teintes de gris sont égales modulo imprécision numérique
 * En cas de différence un message est affiché
 * @param a une image en teintes de gris
 * @param b une image en teintes de gris
 * @param precision un flottant positif: la précision souhaitée; typiquement 0.001
 * @return vrai si les images sont égales et faux sinon
 **/
bool ImageGrisEgal(ImageGris a, ImageGris b, float precision) {
    if (a.size() != b.size())  {
        cout << "Nombre de lignes différent" << endl;
        return false;
    }
    for (int i=0; i<a[0].size(); i++)
        if (a[0].size() != b[i].size()) {
            cout << "Nombre de colonnes différent" << endl;
            return false;
        }
    for (int i=0; i<a.size(); i++)
        for (int j=0; j<a[0].size(); j++)
            if (abs(a[i][j] - b[i][j]) > precision) {
                cout << "Valeur differentes en position " << i << "," << j
             << ": " << a[i][j] << " au lieu de " << b[i][j] << endl;
                return false;
            }
    return true;
}

/// BEGIN intensiteH

/** filtre de Sobel horizontal
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite horizontale de img
 **/
ImageGris intensiteH(ImageGris img) {
    if(img.size() == 0)
        throw runtime_error("The array is empty!");
    if(img[0].size() == 0)
        throw runtime_error("The array is empty!");
    int width = img.size();
    int heigth = img[0].size();
    ImageGris newImg = ImageGris(heigth);
    for(int i = 0; i < heigth; i++){
        newImg[i] = vector<double>(width);
    }

    for(int i = 1; i < heigth - 1; i++){
        for(int j = 1; j < width - 1; j++){
            newImg[i][j] = img[i-1][j-1] + 2*img[i][j-1] + img[i+1][j-1] - img[i-1][j+1] - 2*img[i][j+1] - img[i+1][j+1];
        }
    }
    return newImg;


}


/// BEGIN intensiteV

/** filtre de Sobel vertical
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite verticale de img
 **/
ImageGris intensiteV(ImageGris img) {
    if(img.size() == 0)
        throw runtime_error("The array is empty!");
    if(img[0].size() == 0)
        throw runtime_error("The array is empty!");
    int width = img.size();
    int heigth = img[0].size();
    ImageGris newImg = ImageGris(heigth);
    for(int i = 0; i < heigth; i++){
        newImg[i] = vector<double>(width);
    }

    for(int i = 1; i < heigth - 1; i++){
        for(int j = 1; j < width - 1; j++){
            newImg[i][j] = img[i-1][j-1] + 2*img[i-1][j] + img[i-1][j+1] - img[i+1][j-1] - 2*img[i+1][j] - img[i+1][j+1];
        }
    }
    return newImg;
}


/// BEGIN intensiteHV

/** filtre de Sobel
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite de img
 **/
ImageGris intensite(ImageGris img) {
    if(img.size() == 0)
        throw runtime_error("The array is empty!");
    if(img[0].size() == 0)
        throw runtime_error("The array is empty!");
    
    ImageGris newImg = ImageGris(img.size());
    for(int i = 0; i < newImg.size(); i++){
        newImg[i] = vector<double>(img[i].size());
    }

    ImageGris inverse_h = intensiteH(img);
    ImageGris inverse_v = intensiteV(img);

    for(int i = 0; i < img.size(); i++){
        for(int j = 0; j < img[i].size(); j++){
            newImg[i][j] = sqrt(
                (inverse_h[i][j] * inverse_h[i][j]) + (inverse_v[i][j] * inverse_v[i][j])
            );
        }
    }
    return newImg;
}


void testSobel() {
    CHECK( ImageGrisEgal(intensiteH(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, -373.47, 227.507, 0},
                  {0, -22.1312, 323.866, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(intensiteV(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, -15.1398, 150.501, 0},
                  {0, -9.0336, 273.023, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(intensite(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, 373.777, 272.782, 0},
                  {0, 23.9039, 423.593, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );

    cout << "Vérifier que les images obtenues dans 'sobel/' sont semblables à celles fournies dans 'sobel/correction/'" << endl;
    ecrirePGM(intensite(lirePGM("images/Willis.512.pgm" )), "sobel/Willis.512.pgm");
    ecrirePGM(intensite(lirePGM("images/Baboon.512.pgm" )), "sobel/Baboon.512.pgm");
    ecrirePGM(intensite(lirePGM("images/Billes.256.pgm" )), "sobel/Billes.256.pgm");
    ecrirePGM(intensite(lirePGM("images/Embryos.512.pgm")), "sobel/Embryos.512.pgm");
    ecrirePGM(intensite(lirePGM("images/House.256.pgm"  )), "sobel/House.256.pgm");
}



int main(){

    testSobel();
    return 0 ;
}

