#include <iostream>

#include "image.hpp"
#include "iopgm/iopgm.hpp"
#include "intensite/intensite.hpp"
#include "seuillage_lib/seuillage.hpp"

#include "image-test.hpp"

using namespace std;



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
    ecrirePGM(seuillage(intensite( lissage(lirePGM("images/Billes.256.pgm")) ), 80), "seuillage/Billes.256.pgm");
    ecrirePGM(seuillage(intensite( lissage(lirePGM("images/Willis.512.pgm")) ), 110), "seuillage/Willis.512.pgm");
    cout << "\tProposer des seuils pour Embryos.512.pgm et House.256.pgm" << endl;


    // Remplacez cette ligne et la suivante par le code adéquat
    // throw runtime_error("code non implanté ligne 198");

}

void doubleSeuillageTest(){
    cout << "Vérifier que les images obtenues dans 'seuillage_double/' sont semblables à celles fournies dans 'seuillage_double/correction/'" << endl;
    ecrirePGM(doubleSeuillage(lirePGM("images/Willis.512.pgm"), seuillage(intensite( lissage(lirePGM("images/Willis.512.pgm")) ), 100), 80), "seuillage_double/Willis.512.pgm");
    ecrirePGM(doubleSeuillage(lirePGM("images/Billes.256.pgm"), seuillage(intensite( lissage(lirePGM("images/Billes.256.pgm")) ), 100), 80), "seuillage_double/Billes.256.pgm");
    cout << "\tProposer des seuils pour Embryos.512.pgm et House.256.pgm" << endl;
}

void doubleSeuillageIteratifTest() {
    //il n'y a pas d'yeux quand on utlisie la fonction lissage avec doubleSeuillageIteratif
    cout << "Vérifier que les images obtenues dans 'seuillage_double/' sont semblables à celles fournies dans 'seuillage_double/correction/'" << endl;
    ecrirePGM(doubleSeuillage(intensite( lissage(lirePGM("images/Willis.512.pgm")) ), 500, 80, 100), "seuillage_double/iteratif_Willis.512.pgm");

    cout << "\tProposer des seuils pour Billes.256.pgm, Embryos.512.pgm et House.256.pgm" << endl;
    
}


int main(){
    // Ajouter les appels aux fonctions de test nécessaire
    // ecrirePGM(
    //     renormalise(intensite(lirePGM("images/Willis.512.pgm" ))), 
    //     "sobel/Willis.512.renornalise.pgm");
    renormaliseTest();
    seuillageTest();
    doubleSeuillageTest();
    doubleSeuillageIteratifTest();


    return 0;
}