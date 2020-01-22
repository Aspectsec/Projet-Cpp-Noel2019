#include "Iterateur.h"

template <class T>
Iterateur<T>::Iterateur(ListeBase<T>& s) : liste(s), pData(s.pTete)
{
	
}

template <class T>
Iterateur<T>::~Iterateur()
{
	
}

template <class T>
bool Iterateur<T>::end() const
{
	return pData == 0;
}

template <class T>
void Iterateur<T>::reset()
{
	pData = liste.pTete;
}

template <class T>
bool Iterateur<T>::operator++()
{
	if(!end())
	{
		pData = pData->suiv;
		return true;
	}
	else
		return false; 
}

template <class T>
bool Iterateur<T>::operator++(int)
{
	return operator++();
}

template <class T>
T Iterateur<T>::remove()
{
	Cellule<T> *pPrec = liste.pTete;
	T temp = pData->valeur;
	
	if(pData == liste.pTete)
	{
		liste.pTete = liste.pTete->suiv;
		return temp;
	}
	
	while(pPrec->suiv && pData != pPrec->suiv)
	{
		pPrec = pPrec->suiv;
	}
	
	if(pData->suiv)
		pPrec->suiv = pData->suiv;
	else
		pPrec->suiv = NULL;
	
	delete pData;
	
	pData = liste.pTete;
	
	return temp;
}

template <class T>
Iterateur<T>::operator T() const
{
	return pData->valeur;
}


template <class T>
T* Iterateur<T>::getValeur()
{
	return &pData->valeur;
}

template <class T>
T& Iterateur<T>::operator&()
{
	return pData->valeur;
}

template class Iterateur<int>;
template class Iterateur<Couleur>;
template class Iterateur<ImageRGB>;
template class Iterateur<ImageNG>;
template class Iterateur<ImageB>;
