#include "Pixel.h"

#include <iostream>

Pixel::Pixel()
{
	X = 0;
	Y = 0;
}

Pixel::Pixel(int x, int y) throw (XYException) : X(x), Y(y)
{
	if(x < 0 && y < 0) throw XYException("X et Y trop petits !", 'd');
	if(x < 0) throw XYException("X trop petit !", 'x');
	if(Y < 0) throw XYException("Y trop petit !", 'y');
}

Pixel::Pixel(const Pixel& cpy)
{
	X = cpy.getX();
	Y = cpy.getY();
}

Pixel::~Pixel()
{

}

int Pixel::getX() const { return X; }
int Pixel::getY() const { return Y; }

void Pixel::setX(const int x) throw (XYException)
{
	if(x < 0) throw XYException("X trop petit !", 'x');
	X = x;
}

void Pixel::setY(const int y) throw (XYException)
{
	if(Y < 0) throw XYException("Y trop petit !", 'y');
	Y = y;
}
