#include "MoteurException.h"

MoteurException::MoteurException(const char* erreur)
{
	setErreur(erreur);
}

MoteurException::~MoteurException()
{
	delete(msg);
}
