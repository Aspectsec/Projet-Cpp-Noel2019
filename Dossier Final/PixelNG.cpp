#include "PixelNG.h"

#include <stdlib.h>
#include <iostream>

using namespace std;

PixelNG::PixelNG() : Pixel()
{
	setValeur(255);
}

PixelNG::PixelNG(const int x, const int y, const int val) throw (RGBException, XYException) :  Pixel(x, y)
{
	if(x < 0 & y < 0) throw XYException("X et Y trop petit !", 'd');
	if(x < 0) throw XYException("X trop petit !", 'x');
	if(y < 0) throw XYException("Y trop petit !", 'y');
	
	if(val > 255 || val < 0) throw RGBException("Valeur de gris invalide !", val);
	else Valeur = val;
}

ostream& operator<<(ostream& s, const PixelNG& cpy)
{
	s << endl << "X : " << cpy.getX() << endl << "Y : " << cpy.getY() << endl << "Valeur : " << cpy.getValeur() << endl;
	
	return s;
}

int PixelNG::getValeur() const
{
	return Valeur;
}

void PixelNG::setValeur(const int val) throw (RGBException)
{
	if(val > 255 || val < 0) throw RGBException("Valeur de gris invalide !", val);
	else Valeur = val;
}
