#include "complex_n.h"
#include <cmath>

Complex::Complex(){this->real = 0;this->imag = 0;};
Complex::Complex(double real){this->real = real;this->imag = 0;};
Complex::Complex(double real, double imag){this->real = real;this->imag = imag;};

double Complex::getReal(){
    return real;
}

double Complex::getImag(){
    return imag;
}
double Complex::getMod(){
    return sqrt(real * real + imag * imag);
}
double Complex::getAlpha(){
    return atan2(imag, real);
}
void Complex::setReal(double real){
    this->real = real;
}
void Complex::setImag(double imag){
    this->imag = imag;
}

Complex Complex::operator * (Complex b){      
    return Complex((this->real * b.real) - (this->imag * b.imag),(this->real * b.imag) + (b.real * this->imag));
}

Complex Complex::operator + (Complex b){
    return Complex(this->real + b.real, this->imag + b.imag);
}


