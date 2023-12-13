#include "image.hpp"

/** Infrastructure minimale de test **/
#define CHECK(test) if (!(test)) cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

/** Teste si lirePGM fonction correctement
 * 
*/
void lirePGMTest();
void inversePGMTest();

/** Une image 4x4 en teintes de gris pour faire des tests **/
ImageGris imgGrisTest = {
    {0, 255, 54.213, 236.589},
    {18.411, 182.376, 200.787, 120},
    {139.583, 172.841, 94.0878, 88.4974},
    {158.278, 172.841, 89.0236, 80.0384}
};
/** Test si les fonction intensite marche correctement
 * 
*/
void testSobel();


/** Une image 4x4 en teintes de gris pour les tests de renormalisation **/
ImageGris imgGrisRenorm = {
    {0, 50, 0, 50},
    {0, 50, 0, 50},
    {0, 50, 0, 50},
    {0, 50, 0, 50},
};

/** Teste si renormalise fonction correctement
 * 
*/
void renormaliseTest();

/** Teste si seuillage fonction correctement
 * 
*/
void seuillageTest();

/** Teste si doubleSeuillage fonction correctement
 * 
*/
void doubleSeuillageTest();

/** Teste si doubleSeuillage (deuxieme version (iterative) ) fonction correctement
 * 
*/
void doubleSeuillageIteratifTest();