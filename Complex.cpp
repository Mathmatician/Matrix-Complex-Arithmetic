#include "Complex.h"


COMPLEX::COMPLEX()
{
	real = 0;
	imaginary = 0;
}

COMPLEX::COMPLEX(double rl, double img)
{
	real = rl;
	imaginary = img;
}

COMPLEX::COMPLEX(double rl)
{
	real = rl;
	imaginary = 0;
}

COMPLEX COMPLEX::getComplexValue()
{
	COMPLEX result(this->real, this->imaginary);
	return result;
}

double COMPLEX::getReal()
{
	return real;
}

double COMPLEX::getImaginary()
{
	return imaginary;
}

COMPLEX COMPLEX::operator+(const COMPLEX& obj)
{
	COMPLEX result;
	result.real = this->real + obj.real;
	result.imaginary = this->imaginary + obj.imaginary;
	return result;
}

COMPLEX COMPLEX::operator-(const COMPLEX& obj)
{
	COMPLEX result;
	result.real = this->real - obj.real;
	result.imaginary = this->imaginary - obj.imaginary;
	return result;
}

COMPLEX COMPLEX::operator*(const COMPLEX& obj)
{
	COMPLEX result;
	result.real = (this->real * obj.real) - (this->imaginary * obj.imaginary);
	result.imaginary = (this->real * obj.imaginary) + (this->imaginary * obj.real);
	return result;
}


COMPLEX COMPLEX::operator+=(const COMPLEX& obj)
{
	this->real += obj.real;
	this->imaginary += obj.imaginary;
	return *this;
}

COMPLEX COMPLEX::operator-=(const COMPLEX& obj)
{
	this->real -= obj.real;
	this->imaginary -= obj.imaginary;
	return *this;
}

COMPLEX COMPLEX::operator*=(const COMPLEX& obj)
{
	this->real *= obj.real;
	this->imaginary *= obj.imaginary;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const COMPLEX& obj)
{
	char sign = '+';
	double img = obj.imaginary;

	if (img < 0)
	{
		sign = '-';
		img *= -1;
	}
	os << obj.real << " " << sign << " " << img << "i";
	return os;
}

void COMPLEX::display()
{
	char sign = '+';
	double img = imaginary;

	if (img < 0)
	{
		sign = '-';
		img *= -1;
	}

	std::cout << real << " " << sign << " " << img << "i" << std::endl;
}

