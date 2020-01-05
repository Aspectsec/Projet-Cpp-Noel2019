#include "BaseException.h"

class MoteurException : public BaseException
{
	public:
		MoteurException(const char * erreur);
		~MoteurException();
};
