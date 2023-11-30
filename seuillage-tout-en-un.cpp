#include <stdexcept>
/** @file
 * Filtres de seuillage
 **/

#include <cmath>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>

#include "iopgm/iopgm.hpp"
#include "intensite/intensite.hpp"
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

/** Une image 4x4 en teintes de gris pour les tests de renormalisation **/
ImageGris imgGrisRenorm = {
    {0, 50, 0, 50},
    {0, 50, 0, 50},
    {0, 50, 0, 50},
    {0, 50, 0, 50},
};

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

double findTheBiggestNumber(ImageGris img){
    if( img.size() == 0 )
        throw runtime_error("The image is empty!");
    if( img[0].size() == 0 )
        throw runtime_error("The image is empty!");

    double biggest = img[0][0];
    for(vector<double> ligne: img){
        for(double element: ligne){
            if( element > biggest )
                biggest = element;
        }
    }
    return biggest;
}

/// BEGIN renormalise

/** Renormalize une image en teinte de gris, les ramenant dans l'intervalle [0,255]
 * @param img un image en teintes de gris
 * @return une image en teintes de gris
 **/
ImageGris renormalise(ImageGris img) {
    if( img.size() == 0 )
        throw runtime_error("The image is empty!");
    if( img[0].size() == 0 )
        throw runtime_error("The image is empty!");

    ImageGris new_image = ImageGris(img.size());
    for(int i = 0; i < new_image.size(); i++){
        new_image[i] = vector<double>(img[i].size());
    }

    double biggest_number  = findTheBiggestNumber(img);
    for(int i = 0; i < new_image.size(); i++){
        for(int j = 0; j < new_image[i].size(); j++){
            new_image[i][j] = ( (img[i][j] / biggest_number) * 255 );
        }
    }

    return new_image;
}


void renormaliseTest() {
    CHECK( ImageGrisEgal(renormalise( imgGrisRenorm),
              ImageGris( {
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
              }),
              0.001) );

}
/// BEGIN seuillage

/** Filtre de seuillage
 * @param img
 * @param seuil un entier dans l'intervalle [0,255]
 * @return image en noir et blanc obtenue en remplacant la teinte de
 *  chaque pixel par
 *  - du blanc si teinte < seuil
 *  - du noir  si teinte > seuil
 **/
ImageGris seuillage(ImageGris img, int seuil) {
    if( img.size() == 0 )
        throw runtime_error("The image is empty!");
    if( img[0].size() == 0 )
        throw runtime_error("The image is empty!");

    ImageGris new_image = ImageGris(img.size());
    for(int i = 0; i < new_image.size(); i++){
        new_image[i] = vector<double>(img[i].size());
    }

    double biggest_number  = findTheBiggestNumber(img);
    for(int i = 0; i < new_image.size(); i++){
        for(int j = 0; j < new_image[i].size(); j++){
            new_image[i][j] = 
                ( img[i][j] < seuil ) ? (255) : (0);
        }
    }

    return new_image;
}

/// BEGIN doubleSeuillage

bool isPixelSelected(float pixel){
    return pixel == 0;
}

/** Filtre de double seuillage
 * @param imgIntensite image d'intensite
 * @param imgContour image codant un ensemble de pixels selectionnes
 * @param seuil un entier de l'intervalle [0,255]
 * @return une copie d'imgIntensite modifiee de sorte que:
 *  -si teinte > seuil et voisin d'un pixel de imgContour, alors pixel noir
 *  -sinon pixel blanc
 **/
ImageGris doubleSeuillage(ImageGris imgIntensite, ImageGris imgContour, int seuil) {
    if( imgIntensite.size() == 0 || imgContour.size() == 0)
        throw runtime_error("The image is empty!");
    if( imgIntensite[0].size() == 0 || imgContour[0].size() == 0)
        throw runtime_error("The image is empty!");
    if(imgIntensite.size() != imgContour.size() || imgIntensite[0].size() != imgContour[0].size())
        throw runtime_error("Two different images are given!");
    ImageGris new_image = ImageGris(imgIntensite.size());
    for(int i = 0; i < new_image.size(); i++){
        new_image[i] = vector<double>(imgIntensite[i].size());
    }

    for(int i = 0; i < new_image.size(); i++){
        for(int j = 0; j < new_image[i].size(); j++){

            if(imgIntensite[i][j] < seuil){
                new_image[i][j] = 255.0;
                continue;
            }
            if(i > 0){
                if( isPixelSelected(imgContour[i-1][j] ) ) {
                    new_image[i][j] = 0;
                    continue;
                }
            }
            if(i < new_image.size() - 1){
                if( isPixelSelected(imgContour[i+1][j] ) ) {
                    new_image[i][j] = 0;
                    continue;
                }
            }
            if(j > 0){
                if( isPixelSelected(imgContour[i][j-1] ) ) {
                    new_image[i][j] = 0;
                    continue;
                }
            }
            if(j < new_image[i].size() - 1){
                if( isPixelSelected(imgContour[i][j+1] ) ) {
                    new_image[i][j] = 0;
                    continue;
                }
            }

            if(i > 0 && j > 0 && i < new_image.size() - 1 && j < new_image[i].size()){
                if( isPixelSelected(imgContour[i-1][j-1]) || isPixelSelected(imgContour[i-1][j+1]) ||
                     isPixelSelected(imgContour[i+1][j-1]) || isPixelSelected(imgContour[i+1][j+1]) ){
                    new_image[i][j] = 0;
                    continue;
                }
            }

            new_image[i][j] = 255;
            continue;

        }
    }
    return new_image;
}

/// BEGIN doubleSeuillageIteratif

/** Filtre de double seuillage iteratif
 * @param imgIntensite image d'intensité
 * @param seuilFort un entier de l'intervalle [0,255]
 * @param seuilFaible un entier de l'intervalle [0,255]
 * @param nbAmeliorations un entier non negatif: le nombre d'itérations
 * @return le double seuillage de img
 **/
ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, int seuilFaible, int nbAmeliorations) {
    ImageGris new_image = seuillage(imgIntensite, seuilFort);

    for(int n=0; n<nbAmeliorations; n++) {
        new_image = doubleSeuillage(imgIntensite, new_image, seuilFaible);
    }

    return new_image;
}


void seuillageTest() {
    CHECK( ImageGrisEgal(seuillage( imgGrisTest, 80),
              ImageGris( {
                  {255, 0, 255, 0},
                  {255, 0, 0, 0},
                  {0, 0, 0, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(seuillage( intensite(imgGrisTest), 80),
              ImageGris( {
                  {255, 255, 255, 255},
                  {255, 0, 0, 255},
                  {255, 255, 0, 255},
                  {255, 255, 255, 255}
              }),
              0.001) );

    CHECK( ImageGrisEgal(doubleSeuillage(intensite(imgGrisTest), 400, 80, 4 ),
                          ImageGris( {
                              {255, 255, 255, 255},
                              {255, 0, 0, 255},
                              {255, 255, 0, 255},
                              {255, 255, 255, 255}
                          }),
                          0.001) );


    cout << "Vérifier que les images obtenues dans 'seuillage/' sont semblables à celles fournies dans 'seuillage/correction/'" << endl;
    ecrirePGM(seuillage(intensite(lirePGM("images/Billes.256.pgm")), 80), "seuillage/Billes.256.pgm");
    ecrirePGM(seuillage(intensite(lirePGM("images/Willis.512.pgm"  )), 110), "seuillage/Willis.512.pgm");
    cout << "\tProposer des seuils pour Embryos.512.pgm et House.256.pgm" << endl;


    // Remplacez cette ligne et la suivante par le code adéquat
    // throw runtime_error("code non implanté ligne 198");

}

void doubleSeuillageTest(){
    cout << "Vérifier que les images obtenues dans 'seuillage_double/' sont semblables à celles fournies dans 'seuillage_double/correction/'" << endl;
    ecrirePGM(doubleSeuillage(lirePGM("images/Willis.512.pgm"), seuillage(intensite(lirePGM("images/Willis.512.pgm")), 100), 80), "seuillage_double/Willis.512.pgm");
    ecrirePGM(doubleSeuillage(lirePGM("images/Billes.256.pgm"), seuillage(intensite(lirePGM("images/Billes.256.pgm")), 100), 80), "seuillage_double/Billes.256.pgm");
    cout << "\tProposer des seuils pour Embryos.512.pgm et House.256.pgm" << endl;
}

void doubleSeuillageIteratifTest() {
    cout << "Vérifier que les images obtenues dans 'seuillage_double/' sont semblables à celles fournies dans 'seuillage_double/correction/'" << endl;
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Willis.512.pgm")), 500, 80, 100), "seuillage_double/iteratif_Willis.512.pgm");

    cout << "\tProposer des seuils pour Billes.256.pgm, Embryos.512.pgm et House.256.pgm" << endl;
    
}


int main(){
    // Ajouter les appels aux fonctions de test nécessaire
    // ecrirePGM(
    //     renormalise(intensite(lirePGM("images/Willis.512.pgm" ))), 
    //     "sobel/Willis.512.renornalise.pgm");
    // renormaliseTest();
    seuillageTest();
    doubleSeuillageTest();
    doubleSeuillageIteratifTest();
    // Remplacez cette ligne et la suivante par le code adéquat
    // throw runtime_error("code non implanté ligne 221");


    return 0;
}

