#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "intensite.hpp"

using namespace std;

typedef vector< vector<double> > ImageGris;

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