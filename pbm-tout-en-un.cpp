#include <stdexcept>
/** @file
 * Lecture et ecriture d'images binaires au format PBM
 **/
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

/// BEGIN ImageNB
/** Structure de données pour représenter une image binaire **/
typedef vector<vector<int> > ImageNB;
/// END ImageNB

/// BEGIN lirePBM

/** Construire une image binaire depuis un fichier PBM
 * @param source le nom d'un fichier PBM
 * @return une image binaire (0/1)
 **/
ImageNB lirePBM(string source) {
    ifstream file;
    file.open(source);
    if(!file)
        throw runtime_error("The file wan't found: " + source);
    
    string temp;
    //we don't wanna use first 2 lines with the information we don't need
    for(int i = 0; i < 8; i++){
        file >> temp;
    }

    int width, height;
    width = 0;
    height = 0;
    file >> width;
    file >> height;

    ImageNB arr = vector< vector<int> >(height); //Initialisation
    for(int i = 0; i < height; i++){
        arr[i] = vector<int>(width);
    }

    int colonne = 0; //we wanna count how many numbers we passed
    int ligne = 0;
    int pbm_num;
    while(file >> pbm_num){
        arr[ligne][colonne] = pbm_num;
        ++colonne; //each iteration we increas our number
        if(colonne >= width){ //if we passed as many numbers as our width contains
            cout << endl; // we go to the next line
            colonne = 0; //and we start counting from 0
            ligne++;
        }
    }
    file.close();
    return arr;
}

/// BEGIN ecrirePBM

/** Ecrit une image binaire dans un fichier PBM
 * @param img une image binaire (0/1)
 * @param cible le nom d'un fichier PBM
 **/
void ecrirePBM(ImageNB img, string cible) {
    int width = img.size();
    if(width == 0)
        throw runtime_error("The vector is empty!");
    int height = img[0].size();
    if(height == 0)
        throw runtime_error("The vector is empty!");

    ofstream file;
    file.open(cible);

    file << "P1" << endl;
    file << "# CREATOR: GIMP PNM Filter Version 1.1 " << endl;
    file << width << " " << height << endl;
    for(vector<int> ligne: img){
        for(int elem: ligne){
            file << elem << " ";
        }
        file << endl;
    }
    file.close();
}


/// BEGIN affichePBM

/** Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param img une image binaire (0/1)
 **/
void affichePBM(ImageNB img) {
    for(vector<int> ligne: img){
        for(int elem: ligne){
            cout << (elem ? "@" : " ") << " ";
        }
        cout << endl;
    }
}

/// BEGIN inversePBM

/** Echange le noir et le blanc dans une image PBM
 * @param img une image binaire (0/1)
 * @return l'image où le blanc et le noir ont été inversés
 **/
ImageNB inversePBM(ImageNB img) {
    for(int ligne = 0; ligne < img.size(); ligne++){
        for(int colonne = 0; colonne < img[ligne].size(); colonne++){
            img[ligne][colonne] = !img[ligne][colonne];
        }
    }
    return img;
}

void testLirePBM(){
    cout << "Vérifier que les images obtenues dans 'pbm/' sont semblables à celles fournies dans 'pbm/correction/'" << endl;
    ecrirePBM(lirePBM("./images/smiley.pbm"),  "./pbm/smiley.pbm");
    // ecrirePBM(lirePBM("./images/cercle.pbm"),  "./pbm/cercle.pbm");
    // ecrirePBM(lirePBM("./images/code.pbm"), "./pbm/code.pbm");
    // ecrirePBM(lirePBM("./images/damier.pbm"), "./pbm/damier.pbm");
}

void pbm_tout_en_un_test(){
    ImageNB smiley = lirePBM("./images/smiley.pbm");
    ImageNB smiley_inversed = inversePBM(smiley);

    affichePBM(smiley);
    cout << endl << endl;
    affichePBM(smiley_inversed);

    ecrirePBM(smiley_inversed,  "./pbm/inversed_smiley.pbm");

    cout << "{" << endl;
    for(auto ligne: smiley_inversed){
        cout << "{";
        for(int elem: ligne){
            cout << elem << ", ";
        }
        cout << "},\n";
    }
    cout << "}" << endl;
}


