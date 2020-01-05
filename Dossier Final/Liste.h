#ifndef _LISTEH_
#define _LISTEH_

#include <iostream>
using namespace std;
#include "ListeBase.h"
#include "Couleur.h"
#include "ImageB.h"
#include "ImageRGB.h"
#include "Iterateur.h"

template <class T> class Liste : public ListeBase<T>
{
	public:
		void insere(const T& val);
};

#endif
