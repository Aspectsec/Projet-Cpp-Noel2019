#include "ListeBase.h"

using namespace std;

template <class T>
ListeBase<T>::ListeBase()
{
	this->pTete = NULL;
}

template <class T>
ListeBase<T>::ListeBase(const ListeBase &cpy)
{
	Cellule<T> *pTempCpy = cpy.pTete;
	
	if(!pTempCpy)
	{
		this->pTete = NULL;
		return;
	}

	pTete = new Cellule<T>;
	Cellule<T> *pTempCur = this->pTete;
	
	pTempCur->valeur = pTempCpy->valeur;
	pTempCur->suiv = new Cellule<T>;

	while(pTempCpy->suiv)
	{
		pTempCur = pTempCur->suiv;
		pTempCpy = pTempCpy->suiv;
		
		pTempCur->valeur = pTempCpy->valeur;
		
		if(pTempCpy->suiv)
			pTempCur->suiv = new Cellule<T>;
	}
}

template <class T>
ListeBase<T>::~ListeBase()
{
	Cellule<T> *pPrec, *pCur;
	
	pCur = pTete;
	
	while(pCur)
	{
		pPrec = pCur;
		pCur = pCur->suiv;
		
		delete pPrec;
	}
}

template <class T>
void ListeBase<T>::reset()
{
	pTete = NULL;
}

template <class T>
void ListeBase<T>::Affiche() const
{
	if(!pTete)
		return;
	
	Cellule<T> *pTemp = this->pTete;
	
	while(pTemp != NULL)
	{
		if(pTemp->suiv)
			cout << pTemp->valeur << ", ";
		
		if(!pTemp->suiv)
			cout << pTemp->valeur;
			
		pTemp = pTemp->suiv;
		
		cout << endl;
	}
}

template <class T>
bool ListeBase<T>::estVide()
{
	return pTete ? true : false;
}

template <class T>
int ListeBase<T>::getNombreElements()
{
	if(!pTete) return 0;
	
	Cellule<T> *pTemp = pTete;
	
	int i = 1;
	
	while(pTemp->suiv)
	{
		pTemp = pTemp->suiv;
		
		i++;
	}
	
	return i;
}

template <class T>
ListeBase<T>& ListeBase<T>::operator=(const ListeBase<T>& liste2)
{
	Cellule<T> *pTempCpy = liste2.pTete;
	
	if(!this->pTete)
		this->pTete = new Cellule<T>;
		
	Cellule<T> *pTempCur = this->pTete;
	
	pTempCur->valeur = pTempCpy->valeur;
	
	if(!pTempCur->suiv)
		pTempCur->suiv = new Cellule<T>;

	while(pTempCpy->suiv)
	{
		pTempCur = pTempCur->suiv;
		pTempCpy = pTempCpy->suiv;
		
		pTempCur->valeur = pTempCpy->valeur;
		
		if(pTempCpy->suiv)
			pTempCur->suiv = new Cellule<T>;
		else
			pTempCur->suiv = NULL;
	}
	
	return (*this);
}

template class ListeBase<int>;
template class ListeBase<Couleur>;
template class ListeBase<ImageRGB>;
template class ListeBase<ImageNG>;
template class ListeBase<ImageB>;
