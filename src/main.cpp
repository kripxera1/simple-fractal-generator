#include <iostream>
#include <cmath>

#include "complex_n.h"
#include "bitmap.h"
#include "color.h"


int main(){

    const int MAX_MODULUS = 10;
    char* imageFileName = (char*) "Mandelbrot.bmp";
    int height , width;
    height = 4000;
    width = 4000;
    
    int iterations = 100;
    double x = 0, y = 0; //center of the image;
    double range = 4;//range of numbers in the real number line that will be taken into account;
    double pixelSize = range/width;
    Complex z, c;
    int r, g, b;    

    //reservamos memoria para la imagen
    unsigned char *** image = new unsigned char **[height];
    for(int i = 0; i < height; i++){
        image[i] = new unsigned char * [width];
        for(int j = 0; j < width; j++){
            image[i][j] = new unsigned char[BYTES_PER_PIXEL];
        }
    }


    for(int i =- height/2; i < height/2; i++){
        for(int j = -width/2; j < width/2; j++){

            c.setImag(pixelSize*i+y);
            c.setReal(pixelSize*j+x);
            z.setImag(0);
            z.setReal(0);

            for(int k = 0; k < iterations; k++){
                z=z*z+c;
                if(z.getAlpha() < MAX_MODULUS){
                    r=g=b=0;
                    colorAnguloSeno(((double)k/iterations)*M_PI,r,g,b);
                    image[i+height/2][j+width/2][0] = (unsigned char) (b);
                    image[i+height/2][j+width/2][1] = (unsigned char) (g);
                    image[i+height/2][j+width/2][2] = (unsigned char) (r);
                }
            }
        }
    }
    
    generateBitmapImage(image, height, width, imageFileName);

    return 0;
}

