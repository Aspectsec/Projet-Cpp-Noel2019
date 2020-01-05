#ifndef _PIXELRGB_
#define _PIXELRGB_

#include "Pixel.h"
#include "Couleur.h"
#include <iostream>

class PixelRGB : public Pixel
{
	private:
		Couleur color;
		
	public:
		PixelRGB();
		PixelRGB(const int x, const int y, const Couleur& col);
		PixelRGB(const PixelRGB& cpy);
		~PixelRGB();
		
		void setValeur(const Couleur& col);
		Couleur getValeur() const;
		
		friend std::ostream& operator<<(std::ostream& s, PixelRGB& cpy);
};

#endif
