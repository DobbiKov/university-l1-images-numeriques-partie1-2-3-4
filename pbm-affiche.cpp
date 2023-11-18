#include <stdexcept>
/** @file
 * Affichage d'une image PBM
 **/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/// BEGIN affichePBM

/** Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param source le nom d'un fichier PBM
 **/
void affichePBM(string source)  {
    ifstream file;
    file.open(source);
    string temp;
    //we don't wanna use first 2 lines with the information we don't need
    for(int i = 0; i < 8; i++){
        file >> temp;
        // cout << temp << " ";
    }
    cout << endl;

    //we get width and heigth 10 10
    int width, height;
    width = 0;
    height = 0;
    file >> width;
    file >> height;

    int compte = 0; //we wanna count how many numbers we passed
    int pbm_num;
    while(file >> pbm_num){
        cout << ((pbm_num) ? ("@") : (" ")); //if we get 1 we print @, in other case we print ' '
        ++compte; //each iteration we increas our number
        if(compte >= width){ //if we passed as many numbers as our width contains
            cout << endl; // we go to the next line
            compte = 0; //and we start counting from 0
        }
    }
    file.close();
}

/** Echange le noir et le blanc dans une image PBM
 * @param source le nom du fichier PBM à lire
 * @param cible le nom du nouveau fichier PMB créé
 **/
void inversePBM(string source, string cible) {
    ifstream file;
    ofstream new_file;
    file.open(source);
    new_file.open(cible);
    string temp;

    file >> temp;
    new_file << temp << endl; //we write P1

    for(int i = 0; i < 7; i++){ //we write a comment (second line)
        file >> temp;
        new_file << temp << " ";
        // cout << temp << " ";
    }
    new_file << endl;

    //we get width and heigth 10 10
    int width, height;
    width = 0;
    height = 0;
    file >> width;
    file >> height;

    new_file << width << " " << height << endl; // we write width and heigth

    int compte = 0; //we wanna count how many numbers we passed
    int pbm_num;
    while(file >> pbm_num){ //write all the image numbers but iverse them
        new_file << ((pbm_num) ? ("0") : ("1")) << " "; //if we get 1 we write 0, in other case we write 1
        ++compte; //each iteration we increase our number
        if(compte >= width){ //if we passed as many numbers as our width contains
            new_file << endl; // we write endl so in the file we could write on th next line
            compte = 0; //and we start counting from 0
        }
    }
}


void pbm_affiche_tests(){
    cout << "Affichage du smiley " << endl;
    affichePBM("./images/smiley.pbm");
    cout << "Fabrication du smiley inversé (vérifiez que le nouveau fichier a été créé dans le dossier pbm/smiley-inverse.pbm" << endl;
    inversePBM("./images/smiley.pbm","./pbm/smiley-inverse.pbm");
    cout << "Affichage du smiley inversé" << endl;
    affichePBM("./pbm/smiley-inverse.pbm");
}

