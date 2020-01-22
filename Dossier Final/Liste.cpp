#include "Liste.h"

using namespace std;

template <class T>
void Liste<T>::insere(const T& val)
{
	if(!this->pTete)
	{
		this->pTete = new Cellule<T>;
		this->pTete->valeur = val;
		this->pTete->suiv = NULL;
		return;
	}
	
	Cellule<T>* pNew = new Cellule<T>;
	pNew->valeur = val;
	pNew->suiv = this->pTete;
	this->pTete = pNew; 
}

template class Liste<int>;
template class Liste<Couleur>;
template class Liste<ImageB>;
template class Liste<ImageRGB>;
