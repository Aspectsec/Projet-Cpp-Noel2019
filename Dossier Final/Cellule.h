#ifndef _CELLULEH_
#define _CELLULEH_

template <class T> struct Cellule
{
	T valeur;
	Cellule<T> *suiv;
};

template class Cellule<int>;
template class Cellule<Couleur>;
template class Cellule<ImageNG>;
template class Cellule<ImageB>;

#endif
