#include<iostream>
#include "Complex.hpp"

using namespace std;

int main()
{
    Complex c1, c2, ans;

    cout<<"Enter 1st Complex Number"<<endl;
    cout<<"Real part: ";
    cin>>c1.real;

    cout<<"Imaginary part: ";
    cin>>c1.img;

    cout<<"\nEnter 2nd Complex Number"<<endl;
    cout<<"Real part: ";
    cin>>c2.real;

    cout<<"Imaginary part: ";
    cin>>c2.img;

    // addition
    ans = c1.add(c2);
    cout<<"\nAddition = "<<ans.real<<" + ("<<ans.img<<")i";

    // subtraction
    ans = c1.subtract(c2);
    cout<<"\nSubtraction = "<<ans.real<<" + ("<<ans.img<<")i";

    // multiplication
    ans = c1.multiply(c2);
    cout<<"\nMultiplication = "<<ans.real<<" + ("<<ans.img<<")i";

    // division
    ans = c1.divide(c2);
    cout<<"\nDivision = "<<ans.real<<" + ("<<ans.img<<")i";

    // conjugate
    Complex c3 = c1.conjugate();
    cout<<"\nConjugate of first number = "<<c3.real<<" + ("<<c3.img<<")i";

    Complex c4 = c2.conjugate();
    cout<<"\nConjugate of second number = "<<c4.real<<" + ("<<c4.img<<")i";

    // norm
    cout<<"\nNorm of first complex number = "<<c1.norm();
    cout<<"\nNorm of second complex number = "<<c2.norm();

    return 0;
}







// g++ main.cpp src/Complex.cpp -Iinclude -o complex
// ./complex