#include "Couleur.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

const Couleur Couleur::ROUGE(255, 0, 0);
const Couleur Couleur::VERT(0, 255, 0);
const Couleur Couleur::BLEU(0, 0, 255);
const Couleur Couleur::BLANC(255, 255, 255);
const Couleur Couleur::NOIR(0, 0, 0);

Couleur::Couleur()
{
	R = 0;
	G = 0;
	B = 0;
}

Couleur::Couleur(const Couleur& cpy)
{
	setRouge(cpy.getRouge());
	setVert(cpy.getVert());
	setBleu(cpy.getBleu());
}

Couleur::Couleur(const int r, const int g, const int b) throw (RGBException)
{
	if(r > 255 || r < 0) throw RGBException("Valeur du rouge invalide !", r);
	else setRouge(r);
	
	if(g > 255 || g < 0) throw RGBException("Valeur du vert invalide !", g);
	else setVert(g);
	
	if(b > 255 || b < 0) throw RGBException("Valeur du bleu invalide !", b);
	else setBleu(b);
}

Couleur::~Couleur()
{
	
}

void Couleur::Save(ofstream &fichier) const 
{
	if(!fichier)
	{
		perror("Erreur d'ouverture");
		return;
	}
	
	fichier.write((char*)&R, sizeof(int));
	fichier.write((char*)&G, sizeof(int));
	fichier.write((char*)&B, sizeof(int));
}

void Couleur::Load(ifstream &fichier)
{
	if(!fichier)
	{
		perror("Erreur d'ouverture");
		return;
	}
	
	fichier.read((char*)&R, sizeof(int));
	fichier.read((char*)&G, sizeof(int));
	fichier.read((char*)&B, sizeof(int));
}

Couleur& Couleur::operator=(const Couleur& cpy)
{
	setRouge(cpy.getRouge());
	setVert(cpy.getVert());
	setBleu(cpy.getBleu());
}

void Couleur::setRouge(const int r)
{
	if(r < 0) R = 0;
	if(r > 255) R = 255;
	if(r >= 0 && r <= 255) R = r;
}

void Couleur::setVert(const int g)
{
	if(g < 0) G = 0;
	if(g > 255) G = 255;
	if(g >= 0 && g <= 255) G = g;
}

void Couleur::setBleu(const int b)
{
	if(b < 0) B = 0;
	if(b > 255) B = 255;
	if(b >= 0 && b <= 255) B = b;
}

int Couleur::getRouge() const
{
	return R;
}

int Couleur::getVert() const
{
	return G;
}

int Couleur::getBleu() const
{
	return B;
}

void Couleur::Affiche() const
{
	cout << endl;
	cout << "Rouge : " << getRouge() << endl;
	cout << "Vert : " << getVert() << endl;
	cout << "Bleu : " << getBleu() << endl;
}

ostream& operator<<(ostream& s, const Couleur& cpy)
{
	s << "( " << cpy.getRouge() << ", " << cpy.getVert() << ", " << cpy.getBleu() << " )";
	
	return s;
}

istream& operator>>(istream& s, Couleur& cpy)
{
	int r, g, b;
	
	cout << "Rouge : "; cin >> r; cpy.setRouge(r);
	cout << endl;
	
	cout << "Vert : "; cin >> g; cpy.setVert(g);
	cout << endl;
	
	cout << "Bleu : "; cin >> b; cpy.setRouge(b);
	cout << endl;
	
	return s;
}
