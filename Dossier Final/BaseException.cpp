#include "BaseException.h"
#include <string.h>

BaseException::BaseException()
{
	msg = NULL;
}

BaseException::~BaseException()
{
	delete(msg);
}

void BaseException::setErreur(const char* erreur)
{
	if(msg) delete msg;
	msg = new char[strlen(erreur) + 1];
	if(erreur) strcpy(msg, erreur);
}
