#include "color.h"
#include <cmath>

void colorAnguloSeno(double alpha, int& r, int& g, int& b){
    double alphaGrad = alpha * 180.0/M_PI;
    
    //r
    if(-120.0 <= alphaGrad && alphaGrad <= 120){
        r = 127.5*(sin((alpha+M_PI/3)*180/120)+1);
    }
    //g
    if(0 <= alphaGrad && alphaGrad <=180){
        g = 127.5*(sin((alpha-M_PI/3)*180/120)+1);
    }
    if(-180 <= alphaGrad && alphaGrad <= -120){
        g = 127.5*(sin((alpha+M_PI/3)*180/120)+1);
    }
    //b
    if(0 >= alphaGrad && alphaGrad >=-180){
        b = 127.5*(sin((alpha-M_PI/3)*180/120)+1);
    }
    if(180 >= alphaGrad && alphaGrad >= 120){
        b = 127.5*(sin((alpha+M_PI/3)*180/120)+1);
    }
}

void colorAnguloRectas(double alpha, int& r, int& g, int& b){
    double alphaGrad = alpha * 180.0/M_PI;
    //r
    if(0.0 <= alphaGrad && alphaGrad <= 120.0){
        r = (-255.0/120) * alphaGrad + 255;
    }
    else if(-120.0 <= alphaGrad && alphaGrad <= 0.0){//
        r =  alphaGrad * (255.0/120) + 255;
    }
    //g
    if(0.0 <= alphaGrad && alphaGrad <= 120.0){
        g=(alphaGrad-120)*(255.0/120)+255;
    }
    if(120 <= alphaGrad && alphaGrad < 180){ 
        g = (-255.0/120)*(alphaGrad-120)+255;
    }
    if(-180 <= alphaGrad && alphaGrad <= -120){
        g = (-255.0/120)*(alphaGrad+240)+255;
    }
    //b
    if(0.0 >= alphaGrad && alphaGrad >= -120.0){
        b=(alphaGrad+120)*(-255.0/120)+255;
    }
    if(-120 >= alphaGrad && alphaGrad > -180){ 
        b = (255.0/120)*(alphaGrad+120)+255;
    }
    if(180 >= alphaGrad && alphaGrad >= 120){
        b = (255.0/120)*(alphaGrad-240)+255;
    }
}

void colorIterSeno(int iter, int maxIter, int& r, int& g, int& b){
    colorAnguloSeno(2*M_PI*iter/maxIter-M_PI, r, g, b);
}