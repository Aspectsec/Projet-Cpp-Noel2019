#ifndef _LISTETRIEEH_
#define _LISTETRIEEH_

#include <iostream>
using namespace std;
#include "ListeBase.h"
#include "ImageNG.h"
#include "Iterateur.h"

template <class T> class ListeTriee : public ListeBase<T>
{
	public:
		void insere(const T& val);
};

#endif
