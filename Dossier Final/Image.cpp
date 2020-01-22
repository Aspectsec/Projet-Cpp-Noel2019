#include "Image.h"

#include <string.h>

using namespace std;

Image::Image()
{
	nom = NULL;
	id = 0;
	setDimension(dim);
}

Image::Image(int val, const char* name) : id(val)
{
	nom = NULL;
	setDimension(dim);
	setId(val);
	setNom(name);
}

Image::Image(int nid, const char* unom, const Dimension& d) : id(nid)
{
	nom = NULL;
	setDimension(d);
	setNom(unom);
}

Image::~Image()
{
	if (nom) delete nom;
}

int Image::getLargeur() const
{
	return dim.getLargeur();
}

int Image::getHauteur() const
{
	return dim.getHauteur();
}

void Image::Save(ofstream &fichier) const
{
	if(!fichier)
	{
		perror("Erreur d'ouverture");
		return;
	}
	
	int len = strlen(nom) + 1;
	
	fichier.write((char*)&id, sizeof(int));
	fichier.write((char*)&len, sizeof(int));
	fichier.write(nom, len);
	dim.Save(fichier);
}

void Image::Load(ifstream &fichier)
{
	if(!fichier)
	{
		perror("Erreur d'ouverture");
		return;
	}
	
	int len;
	char yeet[30];
	
	fichier.read((char*)&id, sizeof(int));
	fichier.read((char*)&len, sizeof(int));
	fichier.read(&yeet[0], len);
	setNom(yeet);
	dim.Load(fichier);
}

void Image::setId(const int inid) { id = inid; }
int Image::getId() const { return id; }

char* Image::getNom() const { return nom; }
void Image::setNom(const char* str)
{
	if(nom) delete[] nom;
	nom = new char[strlen(str) + 1];
	if(nom) strcpy(nom, str);
}

void Image::setDimension(const Dimension& d)
{
	dim.setLargeur(d.getLargeur());
	dim.setHauteur(d.getHauteur());
}

Dimension Image::getDimension() { return dim; }
