#include <stdlib.h>

#include "Dimension.h"

using namespace std;

const Dimension Dimension::VGA(640, 480);
const Dimension Dimension::HD(1280, 720);
const Dimension Dimension::FULL_HD(1920, 1080);

Dimension::Dimension()
{
	setLargeur(100);
	setHauteur(100);
}

Dimension::Dimension(int l, int h) throw (XYException) : largeur(l), hauteur(h)
{
	if(h < 1 && l < 1) throw XYException("Dimension trop petite !", 'd');
	
	if(l < 1) throw XYException("Largeur trop petite !", 'x');
	
	if(h < 1) throw XYException("Hauteur trop petite !", 'y');
}

Dimension::Dimension(const Dimension& cpy) throw (XYException)
{
	if(cpy.getLargeur() < 1) throw XYException("Largeur de l'objet image trop petite !", 'x');
	else
		setLargeur(cpy.getLargeur());
	
	if(cpy.getHauteur() < 1) throw XYException("Hauteur de l'objet image trop petite !", 'y');
	else
		setHauteur(cpy.getHauteur());
	
	if(cpy.getHauteur() < 1 && cpy.getLargeur() < 1) throw XYException("Dimension de l'objet image trop petite !", 'd');
}

void Dimension::Save(ofstream &fichier) const
{
	if(!fichier)
	{
		perror("Erreur d'ouverture");
		return;
	}
	
	fichier.write((char*)&largeur, sizeof(int));
	fichier.write((char*)&hauteur, sizeof(int));
}

void Dimension::Load(ifstream &fichier)
{
	if(!fichier)
	{
		perror("Erreur d'ouverture");
		return;
	}
	
	fichier.read((char*)&largeur, sizeof(int));
	fichier.read((char*)&hauteur, sizeof(int));
}

int Dimension::getHauteur() const {return hauteur;} 
int Dimension::getLargeur() const {return largeur;}

void Dimension::setLargeur(int const l) throw (XYException)
{
	if(l < 1) throw XYException("Largeur trop petite !", 'x');
	else
		largeur = l;
}
void Dimension::setHauteur(int const h) throw (XYException)
{
	if(h < 1) throw XYException("Hauteur trop petite !", 'y');
	else
		hauteur = h;
}

Dimension::~Dimension()
{
	
}

bool Dimension::operator==(const Dimension& d)
{
	return getHauteur() == d.getHauteur() && getLargeur() == d.getLargeur();
}

bool Dimension::operator!=(const Dimension& d)
{
	return !(*this == d);
}

istream& operator>>(istream& s, Dimension& cpy)
{
	int l, h;
	
	cout << "Largeur : ";
	cin >> l;
	cpy.setLargeur(l);
	
	cout << "Hauteur : ";
	cin >> h;
	cpy.setHauteur(h);
	cout << endl;
	
	return s;
}

ostream& operator<<(ostream& s, const Dimension& cpy)
{
	s << cpy.getLargeur() << "x" << cpy.getHauteur();
	
	return s;
}

void Dimension::Affiche() const 
{
	cout << endl;
	cout << "Hauteur : " << this->getHauteur() << endl;
	cout << "Largeur : " << this->getLargeur() << endl;
}
