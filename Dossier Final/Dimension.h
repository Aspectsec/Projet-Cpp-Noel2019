#ifndef _DIMENSION_
#define _DIMENSION_

#include <fstream>
#include <iostream>

#include "XYException.h"

class Dimension
{
	private:
		int largeur;
		int hauteur;

	public:
		Dimension();
		Dimension(int l, int h) throw (XYException);
		Dimension(const Dimension& cpy) throw (XYException);
		~Dimension();
		
		void Save(std::ofstream &fichier) const;
		void Load(std::ifstream &fichier);
		
		int  getHauteur() const; 
		int  getLargeur() const;

		void setLargeur(int const l) throw (XYException);
		void setHauteur(int const h) throw (XYException);

		void  Affiche() const;

		const static Dimension VGA;
		const static Dimension HD;
		const static Dimension FULL_HD;
		
		bool operator==(const Dimension& d);
		bool operator!=(const Dimension& d);
		
		friend std::istream& operator>>(std::istream& s, Dimension& cpy);
		friend std::ostream& operator<<(std::ostream& s, const Dimension& cpy);
};

#endif
