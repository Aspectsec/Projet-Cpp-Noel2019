#ifndef _IMAGE_
#define _IMAGE_

#include <fstream> 

#include "Dimension.h"

using namespace std;

class Image
{
	protected:
		int id;
		char* nom;
		Dimension dim;

	public:
		Image();
		Image(int nid, const char* unom, const Dimension& d);
		Image(int val, const char* name);
		~Image();
		
		void Save(ofstream &fichier) const;
		void Load(ifstream &fichier);
		
		void setId(const int inid);
		int getId() const;
		
		void setNom(const char* str);
		char* getNom() const;
		
		void setDimension(const Dimension& d);
		Dimension getDimension();
		
		int getHauteur() const;
		int getLargeur() const;
		
		virtual void Affiche(void) const = 0;
		virtual void Dessine(void) = 0;
		virtual void Dessine(const int x, const int y) = 0;
		virtual void exportToBMP(const char* name) = 0;
};

#endif
