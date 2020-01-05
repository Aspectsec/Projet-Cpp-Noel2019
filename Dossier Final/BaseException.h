#ifndef _BASEEXCEPTION_
#define _BASEEXCEPTION_

class BaseException
{
	protected:
		char* msg;
	public:
		BaseException();
		~BaseException();
		
		void setErreur(const char* erreur);
};

#endif
