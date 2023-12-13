#include <stdexcept>
/** @file
 * Lecture et ecriture d'images binaires au format PBM
 **/
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

#include "image.hpp"
#include "./iopbm/iopbm.hpp"
using namespace std;

void testLirePBM(){
    cout << "Vérifier que les images obtenues dans 'pbm/' sont semblables à celles fournies dans 'pbm/correction/'" << endl;
    ecrirePBM(lirePBM("./images/smiley.pbm"),  "./pbm/smiley.pbm");
    ecrirePBM(lirePBM("./images/cercle.pbm"),  "./pbm/cercle.pbm");
    ecrirePBM(lirePBM("./images/code.pbm"), "./pbm/code.pbm");
    ecrirePBM(lirePBM("./images/damier.pbm"), "./pbm/damier.pbm");
}

void pbm_affiche_tests(){
    cout << "Affichage du smiley " << endl;
    affichePBM(lirePBM("./images/smiley.pbm"));
    cout << "Affichage du smiley inversé" << endl;
    affichePBM(inversePBM(lirePBM("./images/smiley.pbm")));
}

int main()
{
    ImageNB smiley = lirePBM("./images/smiley.pbm");
    ImageNB smiley_inversed = inversePBM(smiley);

    affichePBM(smiley);
    cout << endl << endl;
    affichePBM(smiley_inversed);

    ecrirePBM(smiley_inversed,  "./pbm/inversed_smiley.pbm");

    testLirePBM();

    cout << "PBM Affiche test \n";
    pbm_affiche_tests();
    return 0;
}


