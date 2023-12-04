#include <iostream>
#include "../image.hpp"
#include "seuillage.hpp"

using namespace std;

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

ImageGris seuillage(ImageGris img, int seuil) {
    if( img.size() == 0 )
        throw runtime_error("The image is empty!");
    if( img[0].size() == 0 )
        throw runtime_error("The image is empty!");

    ImageGris new_image = ImageGris(img.size());
    for(int i = 0; i < new_image.size(); i++){
        new_image[i] = vector<double>(img[i].size());
    }

    for(int i = 0; i < new_image.size(); i++){
        for(int j = 0; j < new_image[i].size(); j++){
            new_image[i][j] = 
                ( img[i][j] < seuil ) ? (255) : (0);
        }
    }

    return new_image;
}

bool isPixelSelected(float pixel){
    return pixel == 0;
}

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
            if(j == 0 || j == new_image[i].size()-1)
                new_image[i][j] = 255.0;
            if(i == 0 || i == new_image.size()-1)
                new_image[i][j] = 255.0;
                
            if(j == 0 || i == 0 || i == new_image.size() || j == new_image[i].size()){
                continue;
            }
            if(!isPixelSelected(imgContour[i][j])){
                new_image[i][j] = 0.0;
                continue;
            }
            if( imgIntensite[i][j] >= seuil && (
                isPixelSelected(imgContour[i][j-1]) || isPixelSelected(imgContour[i][j+1]) || 
                isPixelSelected(imgContour[i-1][j]) || isPixelSelected(imgContour[i-1][j+1]) || isPixelSelected(imgContour[i-1][j-1]) ||
                isPixelSelected(imgContour[i+1][j-1]) || isPixelSelected(imgContour[i+1][j-1]) || isPixelSelected(imgContour[i+1][j-1])
                ) )
            {
                new_image[i][j] = 0.0;
                continue;
            }
            new_image[i][j] = 255.0;
        }
    }
    // for(int i = 0; i < new_image.size(); i++){
    //     for(int j = 0; j < new_image[i].size(); j++){

    //         if(imgIntensite[i][j] < seuil){
    //             new_image[i][j] = 255.0;
    //             continue;
    //         }
    //         if( !isPixelSelected(imgContour[i][j]) ){
    //             new_image[i][j] = 0.0;
    //             continue;
    //         }
    //         if(i > 0){
    //             if( isPixelSelected(imgContour[i-1][j] ) ) {
    //                 new_image[i][j] = 0;
    //                 continue;
    //             }
    //         }
    //         if(i < new_image.size() - 1){
    //             if( isPixelSelected(imgContour[i+1][j] ) ) {
    //                 new_image[i][j] = 0;
    //                 continue;
    //             }
    //         }
    //         if(j > 0){
    //             if( isPixelSelected(imgContour[i][j-1] ) ) {
    //                 new_image[i][j] = 0;
    //                 continue;
    //             }
    //         }
    //         if(j < new_image[i].size() - 1){
    //             if( isPixelSelected(imgContour[i][j+1] ) ) {
    //                 new_image[i][j] = 0;
    //                 continue;
    //             }
    //         }

    //         if(i > 0 && j > 0 && i < new_image.size() - 1 && j < new_image[i].size()){
    //             if( isPixelSelected(imgContour[i-1][j-1]) || isPixelSelected(imgContour[i-1][j+1]) ||
    //                  isPixelSelected(imgContour[i+1][j-1]) || isPixelSelected(imgContour[i+1][j+1]) ){
    //                 new_image[i][j] = 0;
    //                 continue;
    //             }
    //         }
    //         // if(isPixelSelected(imgContour[i][j])){
    //         //     new_image[i][j] = 0;
    //         //     continue;
    //         // }

    //         new_image[i][j] = 255;
    //         continue;

    //     }
    // }
    return new_image;
}

ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, int seuilFaible, int nbAmeliorations) {
    ImageGris new_image = seuillage(imgIntensite, seuilFort);

    for(int n=0; n<nbAmeliorations; n++) {
        new_image = doubleSeuillage(imgIntensite, new_image, seuilFaible);
    }

    return new_image;
}