#include "RGBException.h"
#include <iostream>

using namespace std;

RGBException::RGBException() : BaseException()
{

}

RGBException::RGBException(const char* erreur)
{
	setErreur(erreur);
}

RGBException::RGBException(const char* erreur, const int val) : valeur(val)
{
	setErreur(erreur);
}

RGBException::~RGBException()
{
	if(msg) delete(msg);
}

int RGBException::getValeur() const
{
	return valeur;
}
