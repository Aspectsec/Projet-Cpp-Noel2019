#ifndef _RGBEXCEPTION_
#define _RGBEXCEPTION_

#include "BaseException.h"

class RGBException : public BaseException
{
	private:
		int valeur;

	public:
		RGBException();
		RGBException(const char* erreur);
		RGBException(const char* erreur, const int val);
		~RGBException();
		
		int getValeur() const;
};

#endif
