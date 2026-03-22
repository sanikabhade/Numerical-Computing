#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include<iostream>
#include<cmath>

class Complex
{
public:
    float real, img;

    // default constructor
    Complex();

    // parameterized constructor
    Complex(float r, float i);

    // operations
    Complex add(Complex &c);
    Complex subtract(Complex &c);
    Complex multiply(Complex &c);
    Complex divide(Complex &c);

    Complex conjugate();
    float norm();
};

#endif