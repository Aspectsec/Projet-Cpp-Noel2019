#ifndef _PIXELB_
#define _PIXELB_

#include "Pixel.h"
#include "XYException.h"

class PixelB : public Pixel
{
	private:
		bool Valeur;
		
	public:
		PixelB();
		PixelB(const int x, const int y, const bool val) throw (XYException);
		~PixelB();
		
		void setValeur(const bool val);
		bool getValeur() const;
		
		friend std::ostream& operator<<(std::ostream& s, const PixelB& cpy);
};


#endif
