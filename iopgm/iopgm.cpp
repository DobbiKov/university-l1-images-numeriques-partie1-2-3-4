#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "iopgm.hpp"

using namespace std;

typedef vector< vector<double> > ImageGris;


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