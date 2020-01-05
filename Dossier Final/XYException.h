#ifndef _XYEXCEPTION_
#define _XYEXCEPTION_

#include "BaseException.h"

class XYException : public BaseException
{
	private:
		char erreur;
	public:
		XYException();
		XYException(const char* erreur, const char errsrc);
		~XYException();
};

#endif
