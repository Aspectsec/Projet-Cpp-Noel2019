#include "ListeTriee.h"

using namespace std;

template <class T>
void ListeTriee<T>::insere(const T& val)
{
	if(!this->pTete)
	{
		this->pTete = new Cellule<T>;
		this->pTete->valeur = val;
		this->pTete->suiv = NULL;
		
		return;
	}
	
	Cellule<T> *newVal = new Cellule<T>;
	newVal->valeur = val;
	newVal->suiv = NULL;
	
	Cellule<T> *pTemp = this->pTete;
	Cellule<T> *pPrec = NULL;
	
	if(!this->pTete->suiv)
	{
		if(pTemp->valeur < val)
		{
			pTemp->suiv = newVal;
		}
		else
		{
			this->pTete = newVal;
			newVal->suiv = pTemp;
		}
		
		return;
	}
	
	while(pTemp->suiv && ( val > pTemp->valeur ))
	{
		pPrec = pTemp;
		pTemp = pTemp->suiv;
	}
	
	if(!pTemp->suiv && ( val > pTemp->valeur ))
	{
		pTemp->suiv = newVal;
	}
	else
	{
		if(pPrec)
			pPrec->suiv = newVal;
		else
			this->pTete = newVal;
		
		newVal->suiv = pTemp;
	}
}

template class ListeTriee<int>;
template class ListeTriee<ImageNG>;
