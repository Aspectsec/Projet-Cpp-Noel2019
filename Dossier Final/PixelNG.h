#ifndef _PIXELNG_
#define _PIXELNG_

#include "Pixel.h"
#include "RGBException.h"
#include "XYException.h"

class PixelNG : public Pixel
{
	private:
		int Valeur;
		
	public:
		PixelNG();
		PixelNG(const int x, const int y, const int val) throw (RGBException, XYException);
		
		void setValeur(const int val) throw (RGBException);
		int getValeur() const;
		
		friend std::ostream& operator<<(std::ostream& s, const PixelNG& cpy);
};


#endif
