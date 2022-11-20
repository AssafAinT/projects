/****************************************************
* C++ complex                                       *
* Assaf Ainhoren                                    *
* Reviewer: Herscho the king                        *
* date: 11.09.2022                                  *
****************************************************/
/********************************libraries includes****************************/
#ifndef __ILRD_RD127_128_COMPLEX_H__
#define __ILRD_RD127_128_COMPLEX_H__
#include <iostream> // ostream, istream&
#include <cstdlib> 

namespace ilrd
{
class Complex
{
public:
    Complex(const double real = 0.0, const double imaginary = 0.0); //DEF ctor

    double GetReal() const;
    double GetImaginary() const;
    void SetReal(double real);
    void SetImaginary(double imaginary);
    
    Complex& operator+=(const Complex& comp);
    Complex& operator-=(const Complex& comp);
    Complex& operator*=(const Complex& comp);
    Complex& operator/=(const Complex& comp);
private:
    double m_real;
    double m_imaginary;
};

    inline std::ostream& operator<<(std::ostream &os, const Complex& comp)
    {
        double imaginary = comp.GetImaginary();
        return(os << comp.GetReal() << (imaginary >= 0? " + ": " - ")
               << abs(imaginary) << "i");
    }
    inline std::istream& operator>>(std::istream &is, Complex& comp)
    {
        char buff[1024] = {0};
        is >> buff;
        char *buffer = buff;
        comp.SetReal(strtod(buffer, &buffer));
        comp.SetImaginary(strtod(buffer, &buffer));
        
        return is;
    }
    inline const Complex operator+(const Complex& comp1, const Complex& comp2)
    {
        return Complex((comp1.GetReal() + comp2.GetReal()),
                (comp1.GetImaginary() + comp2.GetImaginary()));
    }
    inline const Complex operator-(const Complex& comp1, const Complex& comp2)
    {
        return Complex((comp1.GetReal() - comp2.GetReal()),
               (comp1.GetImaginary() - comp2.GetImaginary()));
    }
    inline const Complex operator/(const Complex& comp1, const Complex& comp2)
    {   
        Complex temp_comp(comp1);

        temp_comp /= comp2;

        return temp_comp;

    }
    inline const Complex operator*(const Complex& comp1, const Complex& comp2)
    {
        Complex temp_comp(comp1);

        temp_comp *= comp2;

        return temp_comp;
    }

    inline bool operator==(const Complex& comp1, const Complex& comp2)
    {
        return (comp1.GetImaginary() == comp2.GetImaginary() &&
                comp1.GetReal() == comp2.GetReal());
    }

    inline bool operator!=(const Complex& comp1, const Complex& comp2)
    {
        return !(comp1 == comp2);
    }

    inline double Complex::GetReal() const
    {
        return m_real;
    }

    inline double Complex::GetImaginary() const
    {
        return m_imaginary;
    }

    inline void Complex::SetReal(double real)
    {
        m_real = real;
    }

    inline void Complex::SetImaginary(double imaginary)
    {
        m_imaginary = imaginary;
    }

    inline Complex& Complex::operator+=(const Complex& num2)     // Append operator
    {
        m_real += num2.m_real;
        m_imaginary += num2.m_imaginary;

        return *this;
    }

    inline Complex& Complex::operator-=(const Complex& num2)     // Subtract operator
    {
        m_real -= num2.m_real;
        m_imaginary -= num2.m_imaginary;

        return *this;
    }

    inline Complex& Complex::operator*=(const Complex& num2)     // Multi append operator
    {
        double copy_m_real = (m_real * num2.m_real) -(m_imaginary * num2.m_imaginary);
        m_imaginary = (m_imaginary * num2.m_real) + (m_real * num2.m_imaginary);
        m_real = copy_m_real;
        return *this;
    }

    inline Complex& Complex::operator/=(const Complex& num2)     // Divide operator
    {
        m_real = (m_real / num2.m_real) -(m_imaginary / num2.m_imaginary);
        m_imaginary = 2 * (m_imaginary / num2.m_real);
        return *this;
    }
}
#endif // __ILRD_RD127_128_COMPLEX_H__