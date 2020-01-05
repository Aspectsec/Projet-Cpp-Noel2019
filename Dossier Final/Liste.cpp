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
	
	Cellule<T> *pTemp = this->pTete;
	
	while(pTemp->suiv)
	{
		pTemp = pTemp->suiv;
	}
	
	pTemp->suiv = new Cellule<T>;
	pTemp = pTemp->suiv;
	pTemp->valeur = val;
	pTemp->suiv = NULL;
}

template class Liste<int>;
template class Liste<Couleur>;
template class Liste<ImageB>;
template class Liste<ImageRGB>;
