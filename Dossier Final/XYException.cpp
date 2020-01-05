#include <iostream>

#include "XYException.h"

using namespace std;

XYException::XYException()
{
	
}

XYException::XYException(const char* erreur, const char errsrc) : erreur(errsrc)
{
	setErreur(erreur);
	cout << msg << endl;
}

XYException::~XYException()
{
	if(msg) delete msg;
}
