#ifndef _COULEUR_
#define _COULEUR_

#include <iostream>
#include <fstream>

#include "RGBException.h"

class Couleur
{
	private:
		int R;
		int G;
		int B;
		
	public:
		Couleur();
		Couleur(const int r, const int g, const int b) throw (RGBException);
		Couleur(const Couleur& cpy);
		~Couleur();
		
		void Save(std::ofstream &fichier) const;
		void Load(std::ifstream &fichier);
		
		const static Couleur ROUGE;
		const static Couleur VERT;
		const static Couleur BLEU;
		const static Couleur BLANC;
		const static Couleur NOIR;
		
		int getRouge() const;
		int getVert() const;
		int getBleu() const;
		
		void setRouge(const int r) throw (RGBException);
		void setVert(const int g) throw (RGBException);
		void setBleu(const int b) throw (RGBException);
		
		void Affiche() const;
		
		friend std::ostream& operator<<(std::ostream& s, const Couleur& cpy);
		friend std::istream& operator>>(std::istream& s, Couleur& cpy);
		
		Couleur& operator=(const Couleur& cpy);
};

#endif
