#include "PixelB.h"

#include <stdlib.h>
#include <iostream>


using namespace std;

PixelB::PixelB()
{
	setX(0);
	setY(0);
	setValeur(0);
}

PixelB::PixelB(const int x, const int y, const bool val) throw (XYException)
{
	if(x < 0  && y < 0) throw XYException("Coordonnees incorrecte ! (< 0)", 'd');
	
	if(x < 0) throw XYException("X trop petit !", 'x');
	else
		setX(x);
	
	if(y < 0) throw XYException("Y trop petit !", 'y');
	else
		setY(y);
	
	setValeur(val);
}

PixelB::~PixelB()
{

}

ostream& operator<<(ostream& s, const PixelB& cpy)
{
	s << endl << "X : " << cpy.getX() << endl << "Y : " << cpy.getY() << endl << "Valeur : " << cpy.getValeur() << endl;
	
	return s;
}

bool PixelB::getValeur() const
{
	return Valeur;
}

void PixelB::setValeur(const bool val)
{
	Valeur = val;
}
