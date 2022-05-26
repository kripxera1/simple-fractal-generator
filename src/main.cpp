#include <iostream>
#include <cmath>
#include <omp.h>
#include <chrono>
#include "complex_n.h"
#include "bitmap.h"
#include "color.h"

const int MAX_MODULUS = 10;

void bruteForceMandelbrot(unsigned char *** image, int iterations,
                          double pixelSize, double x, double y ,
                          int width, int height);

void optimizationMandelbrot(unsigned char *** image, int iBegin , int jBegin,
                            int iEnd, int jEnd, int iterations,
                            double pixelSize, double x, double y ,
                            int width, int height);

void MandelbrotPixel(unsigned char *** image, double imag, double real, int i,
                     int j, int iterations);

int main(){


    std::string fileName = "Mandelbrot";
    int height , width;
    height = 360;
    width = 640;
    int totalFrames = 1000;
    long iterations;
    double x = -0.77568377, y = 0.13646737; //center of the image;

    double range = 4;//range of numbers in the real number line
    double pixelSize = range/width;
    double zoomIncrement = 1.075;
    double zoom = 1000000;
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
                zoom *= zoomIncrement;
        imageRange = range * 1/zoom;
        pixelSize = imageRange/width;
        iterations = (int)(sqrt(2*sqrt(abs(1-sqrt(5*zoom))))*66.5);
        
        //optimizationMandelbrot(image,-height/2,-width/2,height/2,width/2,
        //                       iterations,pixelSize,x,y,width,height);
        
        bruteForceMandelbrot(image,iterations,pixelSize,x,y,width,height);
        generateBitmapImage(image, height, width,
                            (char *)(std::to_string(frame) + ".bmp").c_str());

    }
        
    
    return 0;
}

// useful if image size is over 1080x1920
void bruteForceMandelbrot(unsigned char *** image, int iterations,
                          double pixelSize, double x, double y ,
                          int width, int height){
        
        for(int i =- height/2; i < height/2; i++){
            #pragma omp parallel for num_threads(6)
            for(int j = -width/2; j < width/2; j++){
                MandelbrotPixel(image,pixelSize*i+y,pixelSize*j+x,
                                i+height/2,j+width/2,iterations);
            }
            #pragma omp barrier
        }
}

void optimizationMandelbrot(unsigned char *** image, int iBegin , int jBegin,
                            int iEnd, int jEnd, int iterations,
                            double pixelSize, double x, double y,
                            int width, int height){
    
    int jCenter = (jEnd - jBegin)/2 + jBegin,
        iCenter = (iEnd - iBegin)/2 + iBegin;
    //end of recursion
    if( iBegin == iEnd || jBegin == jEnd)
        return;
    //fill the vertical borders

    for(int k = iBegin; k < iEnd; k++){
        MandelbrotPixel(image, pixelSize*k+y, pixelSize*jBegin+x,
                        k+height/2, jBegin+width/2, iterations);
        MandelbrotPixel(image, pixelSize*k+y, pixelSize*(jEnd-1)+x,
                        k+height/2, jEnd-1+width/2, iterations);
    }

    // If the borders are not homgeneous, apply to each cuadrant.
    for(int k = iBegin + 1; k < iEnd; k++)
        if(image[k+height/2][jBegin+width/2][0] !=
           image[k-1+height/2][jBegin+width/2][0] ||
           image[k+height/2][jEnd-1+width/2][0] !=
           image[k-1+height/2][jEnd-1+width/2][0]){
            // first,second,third and fourth cuadrant
            optimizationMandelbrot(image,iBegin,jCenter,iCenter,jEnd,
                                   iterations,pixelSize,x,y,width,height);
            optimizationMandelbrot(image,iBegin,jBegin,iCenter,jCenter,
                                   iterations,pixelSize,x,y,width,height);
            optimizationMandelbrot(image,iCenter,jBegin,iEnd,jCenter,
                                   iterations,pixelSize,x,y,width,height);
            optimizationMandelbrot(image,iCenter,jCenter,iEnd,jEnd,
                                   iterations,pixelSize,x,y,width,height);
            return;
        }
    //fill the horizontal borders
    for(int k = jBegin; k < jEnd; k++){
        MandelbrotPixel(image,pixelSize*iBegin+y,pixelSize*k+x,
                        iBegin+height/2,k+width/2,iterations);
        MandelbrotPixel(image,pixelSize*(iEnd-1)+y,pixelSize*k+x,
                        iEnd-1+height/2,k+width/2,iterations);
    }

    // If the borders are not homgeneous, apply to each cuadrant.
    for(int k = jBegin + 1; k < jEnd; k++)
        if(image[iBegin+height/2][k+width/2][0] !=
           image[iBegin+height/2][k-1+width/2][0] ||
           image[iEnd-1+height/2][k+width/2][0] !=
           image[iEnd-1+height/2][k-1+width/2][0]){
            // first,second,third and fourth cuadrant
            optimizationMandelbrot(image,iBegin,jCenter,iCenter,jEnd,
                                   iterations,pixelSize,x,y,width,height);
            optimizationMandelbrot(image,iBegin,jBegin,iCenter,jCenter,
                                   iterations,pixelSize,x,y,width,height);
            optimizationMandelbrot(image,iCenter,jBegin,iEnd,jCenter,
                                   iterations,pixelSize,x,y,width,height);
            optimizationMandelbrot(image,iCenter,jCenter,iEnd,jEnd,
                                   iterations,pixelSize,x,y,width,height);
            return;
        }
    
    //if the borders are homogeneous, fill the rectangle
    unsigned char rAbs = image[iCenter+height/2][jBegin+width/2][2],
                  gAbs = image[iCenter+height/2][jBegin+width/2][1],
                  bAbs = image[iCenter+height/2][jBegin+width/2][0];
    #pragma omp parallel for num_threads(6)
    for(int i = iBegin; i < iEnd; i++)
        for(int j = jBegin; j < jEnd; j++){
            image[i+height/2][j+width/2][2] = rAbs;
            image[i+height/2][j+width/2][1] = gAbs;
            image[i+height/2][j+width/2][0] = bAbs;
        }
    #pragma omp barrier
}


void MandelbrotPixel(unsigned char *** image, double imag,
                     double real, int i, int j, int iterations){
    Complex z, c;
    c.setImag(imag);
    c.setReal(real);
    z.setImag(0);
    z.setReal(0);
    for(int it = 0; it < iterations; it++){
    
        z=z*z+c;
        if(z.getAlpha() < MAX_MODULUS){
            int r = 0, g = 0, b = 0;
            colorIterSeno(it,iterations,r,g,b);
            image[i][j][0] = (unsigned char) (b);
            image[i][j][1] = (unsigned char) (g);
            image[i][j][2] = (unsigned char) (r);
        }
    }
}