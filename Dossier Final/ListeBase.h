#ifndef _LISTEBASEH_
#define _LISTEBASEH_

#include <iostream>
using namespace std;
#include "Couleur.h"
#include "ImageRGB.h"
#include "ImageNG.h"
#include "ImageB.h"
#include "Cellule.h"

template <class type> class Iterateur;

template<class T> class ListeBase
{
	protected:
		Cellule<T> *pTete;
		
	public:
		ListeBase();
		ListeBase(const ListeBase& cpy);
		~ListeBase();
		
		friend class Iterateur<T>;
		
		bool estVide();
		
		int getNombreElements();
		
		void reset();
		void Affiche() const;
		virtual void insere(const T& val) = 0;
		
		ListeBase<T>& operator=(const ListeBase<T>& liste2);
};

#endif
