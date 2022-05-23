#include <iostream>
#include <cmath>
#include <omp.h>
#include "complex_n.h"
#include "bitmap.h"
#include "color.h"


int main(){

    const int MAX_MODULUS = 10;
    std::string fileName = "Mandelbrot";
    int height , width;
    height = 1080;
    width = 1920;
    int totalFrames = 350;
    int iterations;
    double x = -0.77568377, y = 0.13646737; //center of the image;
    double range = 4;//range of numbers in the real number line
    double pixelSize = range/width;
    double zoomIncrement = 1.1;
    double zoom = 1;
    double imageRange;

    //reservamos memoria para la imagen
    unsigned char *** image = new unsigned char **[height];
    for(int i = 0; i < height; i++){
        image[i] = new unsigned char * [width];
        for(int j = 0; j < width; j++){
            image[i][j] = new unsigned char[BYTES_PER_PIXEL];
        }
    }
    
    for(int frame = 0; frame < totalFrames; frame++){
        iterations = (int)(sqrt(2*sqrt(abs(1-sqrt(5*zoom))))*66.5);
        for(int i =- height/2; i < height/2; i++){
            #pragma omp parallel for num_threads(omp_get_num_threads()*3/4)
            for(int j = -width/2; j < width/2; j++){

                Complex z, c;
                c.setImag(pixelSize*i+y);
                c.setReal(pixelSize*j+x);
                z.setImag(0);
                z.setReal(0);

                
                for(int k = 0; k < iterations; k++){
                    
                    z=z*z+c;
                    if(z.getAlpha() < MAX_MODULUS){
                        int r = 0, g = 0, b = 0;
                        colorIterSeno(k,iterations,r,g,b);
                        image[i+height/2][j+width/2][0] = (unsigned char) (b);
                        image[i+height/2][j+width/2][1] = (unsigned char) (g);
                        image[i+height/2][j+width/2][2] = (unsigned char) (r);
                    }
                }
                
            }
            #pragma omp barrier
        }
        generateBitmapImage(image, height, width, (char *)(std::to_string(frame) + ".bmp").c_str());
        zoom *= zoomIncrement;
        imageRange = range * 1/zoom;
        pixelSize = imageRange/width;
    }
        
    
    

    return 0;
}

