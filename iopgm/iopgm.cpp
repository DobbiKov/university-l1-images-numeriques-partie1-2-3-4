#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "iopgm.hpp"
#include "../image.hpp"

using namespace std;


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

        tab[ligne][colonne] = (value / colors) * 255;

        colonne++;
        if(colonne >= width){
            colonne = 0;
            ligne++;
        }
    }

    return tab;
}

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
            file << (int)(elem) << " ";
        }
        file << endl;
    }
}

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