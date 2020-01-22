#include "ListeTriee.h"

using namespace std;

template <class T>
void ListeTriee<T>::insere(const T& val)
{
	Cellule<T> *newVal = new Cellule<T>;
	newVal->valeur = val;
	newVal->suiv = NULL;
	
	if(!this->pTete)
	{
		this->pTete = newVal;
		
		return;
	}
	
	Cellule<T> *pCur = this->pTete;
	Cellule<T> *pPrec = NULL;
	
	
	int trouve = 0;
	
	while(trouve == 0 && pCur != NULL)
	{
		if(pCur->valeur > val)
		{
			if(pPrec == NULL)
			{
				newVal->suiv = pCur;
				this->pTete = newVal;
			}
			else
			{
				pPrec->suiv = newVal;
				newVal->suiv = pCur;
			}
			
		trouve = 1;
		
		}
		else
		{
			pPrec = pCur;
			pCur = pCur->suiv;
		}
	}
	
	if(trouve == 0)
	{
		pPrec->suiv = newVal;
		newVal ->suiv = pCur;
	}
	
	
	
	
	
	
	
	
	
	
	
//	if(!this->pTete->suiv)
//	{
//		cout << "pTete->suiv" << endl;
//		if(pTemp->valeur < val)
//		{
//			pTemp->suiv = newVal;
//		}
//		else
//		{
//			this->pTete = newVal;
//			newVal->suiv = pTemp;
//		}
//		cout << "fin pTete" << endl;
//		return;
//	}
//	
//	if(this->pTete->valeur > newVal->valeur)
//	{
//		cout << "<" << endl;
//		newVal->suiv = this->pTete;
//		this->pTete = newVal;
//		cout << "Fin <" << endl;
//		return;
//	}
//	
//	cout << "Avant while" << endl;
//	while(pTemp->suiv && ( val > pTemp->valeur ))
//	{
//		pPrec = pTemp;
//		pTemp = pTemp->suiv;
//	}
//	cout << "Apres while" << endl;
//	
//	if(/*!pTemp->suiv && */( val > pTemp->valeur ))
//	{
//		pTemp->suiv = newVal;
//	}
//	else
//	{
//		if(pPrec)
//			pPrec->suiv = newVal;
//		else
//			this->pTete = newVal;
//		
//		newVal->suiv = pTemp;
//	}
//	cout << "Fin insere" << endl;
}

template class ListeTriee<int>;
template class ListeTriee<ImageNG>;
