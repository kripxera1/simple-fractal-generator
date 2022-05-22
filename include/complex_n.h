#ifndef _COMPLEX_H
#define _COMPLEX_H
class Complex{
private:
    double real;
    double imag;
public:
    Complex();
    Complex(double real);
    Complex(double real ,double imag);
    double getReal();
    double getImag();
    double getMod();
    double getAlpha();
    void setReal(double real);
    void setImag(double imag);
    Complex operator * (Complex b);
    Complex operator + (Complex b);
};
#endif