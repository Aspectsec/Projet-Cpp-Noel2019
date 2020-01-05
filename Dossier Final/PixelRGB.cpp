#include "PixelRGB.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

PixelRGB::PixelRGB()
{
	setX(0);
	setY(0);
	color.setRouge(0);
	color.setVert(0);
	color.setBleu(0);
}

PixelRGB::PixelRGB(const PixelRGB& cpy)
{
	color = cpy.color;;
	X = cpy.getX();
	Y = cpy.getY();
}

PixelRGB::PixelRGB(const int x, const int y, const Couleur& col) {setX(x); setY(y); color = col;}

PixelRGB::~PixelRGB()
{

}

void PixelRGB::setValeur(const Couleur& col)
{
	color = col;
}

Couleur PixelRGB::getValeur() const
{
	return color;
}

ostream& operator<<(ostream& s, PixelRGB& cpy)
{
	s << endl << "X : " << cpy.getX() << endl << "Y : " << cpy.getY() << endl << "Couleur : " << cpy.getValeur() << endl;
	
	return s;
}
