#ifndef _ITERATEURH_
#define _ITERATEURH_

#include <iostream>
using namespace std;
#include "ListeBase.h"

template <class type> class Liste;

template <class T> class Iterateur
{
	private:
		ListeBase<T>& liste;
		Cellule<T> *pData;
		
	public:
		Iterateur(ListeBase<T>& liste);
		~Iterateur();
		
		bool end() const;
		
		void reset();
		
		T remove();
		T* getValeur();
		
		bool operator++();
		bool operator++(int);
		
		operator T() const;
		
		T& operator&();
};

#endif
