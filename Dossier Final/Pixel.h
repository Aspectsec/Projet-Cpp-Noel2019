#ifndef _PIXEL_
#define _PIXEL_

#include <iostream>

#include "XYException.h"

class Pixel
{
	protected:
		int X;
		int Y;
	
	public:
		Pixel();
		Pixel(int x, int y) throw (XYException);
		Pixel(const Pixel& cpy);
		~Pixel();
		
		int getX() const;
		int getY() const;
		
		void setX(const int x) throw (XYException);
		void setY(const int y) throw (XYException);
};

#endif
