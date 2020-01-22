#include "ImageRGB.h"
#include "WindowSDLimage.h"
#include "WindowSDL.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

ImageRGB::ImageRGB()
{
	nom = NULL;
	matrice = NULL;
	setDimension(Dimension::VGA);
	setNom("default");
	setId(1);
}

ImageRGB::ImageRGB(int val, const char* name)
{
	nom = NULL;
	matrice = NULL;
	setDimension(Dimension::VGA);
	setNom(name);
	setId(val);
}

ImageRGB::ImageRGB(const ImageRGB& image)
{
	nom = NULL;
	matrice = NULL;
	setDimension(image.dim);
	setNom(image.getNom());
	setId(image.getId());
	
	for(int x = 0; x < dim.getLargeur(); x++)
		for(int y = 0; y < dim.getHauteur(); y++)
			matrice[x][y] = image.matrice[x][y];
}	

ImageRGB::ImageRGB(int nid, const char* unom, const Dimension& d)
{
	nom = NULL;
	matrice = NULL;
	setDimension(d);
	setId(nid);
	setNom(unom);
}

ImageRGB::ImageRGB(const char* path)
{
	nom = NULL;
	matrice = NULL;
	setDimension(Dimension::VGA);
	setNom(path);
	setId(1);

	importFromBMP(path);
}

ImageRGB::~ImageRGB()
{
	if (nom) delete nom;
	FreeMatrix();
}

void ImageRGB::Save(ofstream &fichier) const 
{
	if(!fichier)
	{
		perror("Erreur d'ouverture");
		return;
	}
	
	Image::Save(fichier);
	
	Couleur val;
	
	for(int x = 0; x < dim.getLargeur(); x++)
		for(int y = 0; y < dim.getHauteur(); y++)
		{
			val = matrice[x][y];
			
			fichier.write((char*)&val, sizeof(Couleur));
		}
}

void ImageRGB::Load(ifstream &fichier)
{
	if(!fichier)
	{
		perror("Erreur d'ouverture");
		return;
	}
	
	Image::Load(fichier);
	
	Couleur val;
	
	for(int x = 0; x < dim.getLargeur(); x++)
		for(int y = 0; y < dim.getHauteur(); y++)
		{
			fichier.read((char*)&val, sizeof(Couleur));
			matrice[x][y] = val;
		}
}

ImageNG ImageRGB::getRouge() const
{
	ImageNG rouge(this->getId(), this->getNom(),this->dim);
	
	for(int x = 0; x < dim.getLargeur(); x++)
		for(int y = 0; y < dim.getHauteur(); y++)
			rouge.setPixel(x, y, matrice[x][y].getRouge());
	
	return rouge;
}

ImageNG ImageRGB::getVert() const
{
	ImageNG vert(this->getId(), this->getNom(),this->dim);
	
	for(int x = 0; x < dim.getLargeur(); x++)
		for(int y = 0; y < dim.getHauteur(); y++)
			vert.setPixel(x, y, matrice[x][y].getVert());
	
	return vert;
}

ImageNG ImageRGB::getBleu() const
{
	ImageNG bleu(this->getId(), this->getNom(),this->dim);
	
	for(int x = 0; x < dim.getLargeur(); x++)
		for(int y = 0; y < dim.getHauteur(); y++)
			bleu.setPixel(x, y, matrice[x][y].getBleu());
	
	return bleu;
}

void ImageRGB::setRGB(const ImageNG& r, const ImageNG& g, const ImageNG& b)
{
	ImageNG tempR(r);
	ImageNG tempG(g);
	ImageNG tempB(b);
	
	for(int x = 0; x < dim.getLargeur(); x++)
		for(int y = 0; y < dim.getHauteur(); y++)
		{
			matrice[x][y].setRouge(tempR.getPixel(x, y));
			matrice[x][y].setVert(tempG.getPixel(x, y));
			matrice[x][y].setBleu(tempB.getPixel(x, y));
		}
}

ImageRGB& ImageRGB::operator=(const ImageRGB& cpy)
{
	ImageRGB temp(cpy);
	setNom(cpy.getNom());
	setDimension(cpy.dim);
	setId(cpy.getId());
	
	for(int x = 0; x < dim.getLargeur(); x++)
		for(int y = 0; y < dim.getHauteur(); y++)
			matrice[x][y] = temp.getPixel(x, y);
	
	return (*this);
}

ImageRGB operator+(const ImageRGB& image, const PixelRGB& pix) throw (XYException)
{
	if((pix.getX() > image.dim.getLargeur() || pix.getX() < 0) || (pix.getY() > image.dim.getHauteur() || pix.getY() < 0)) throw XYException("Coordonnees est hors de l'image !", 'd');
	if(pix.getX() > image.dim.getLargeur() || pix.getX() < 0) throw XYException("X est hors de l'image !", 'x');
	if(pix.getY() > image.dim.getHauteur() || pix.getY() < 0) throw XYException("Y est hors de l'image !", 'y');
	
	ImageRGB itemp(image);
	PixelRGB temp(pix);
	
	Couleur ctempi = itemp.getPixel(pix.getX(), pix.getY());
	Couleur ctempp = temp.getValeur();
	
	if((ctempi.getRouge() + ctempp.getRouge()) < 255)
		ctempi.setRouge(ctempi.getRouge() + ctempp.getRouge());
	else
		ctempi.setRouge(255);
	
	if((ctempi.getVert() + ctempp.getVert()) < 255)
		ctempi.setVert(ctempi.getVert() + ctempp.getVert());
	else
		ctempi.setVert(255);
	
	if((ctempi.getBleu() + ctempp.getBleu()) < 255)
		ctempi.setBleu(ctempi.getBleu() + ctempp.getBleu());
	else
		ctempi.setBleu(255);
	
	itemp.setPixel(pix.getX(), pix.getY(), ctempi);
	
	return itemp;
}

ImageRGB operator+(const PixelRGB& pix, const ImageRGB& image)
{
	return image + pix;
}

ostream& operator<<(ostream& s, const ImageRGB& cpy)
{
	s << "[]ImageRGB " << cpy.getNom() << " : " << "ID=" << cpy.getId() << " " << cpy.getLargeur() << "x" << cpy.getHauteur() << endl;
	
	return s;
}

void ImageRGB::setDimension(const Dimension& d)
{
	Couleur** temp = AllocMatrix(d.getLargeur(), d.getHauteur());
	
	for(int x = 0; x < d.getLargeur(); x++)
		for(int y = 0; y < d.getHauteur(); y++)
		{
			temp[x][y].setRouge(0);
			temp[x][y].setVert(0);
			temp[x][y].setBleu(0);
		}
	
	if(matrice)
		for(int x = 0; x < dim.getLargeur(); x++)
			for(int y = 0; y < dim.getHauteur(); y++)
				if(x < d.getLargeur() && y < d.getHauteur())
				{
					temp[x][y].setRouge(matrice[x][y].getRouge());
					temp[x][y].setVert(matrice[x][y].getVert());
					temp[x][y].setBleu(matrice[x][y].getBleu());
				}
	
	if(matrice) FreeMatrix();
	
	dim.setLargeur(d.getLargeur());
	dim.setHauteur(d.getHauteur());
	
	matrice = temp;
}

void ImageRGB::setPixel(const int x, const int y, const Couleur& color) throw (XYException)
{
	if((x < 0 || x > dim.getLargeur()) || (y < 0 || y > dim.getHauteur())) throw XYException("X et Y en dehors de l'image !", 'd');
	if(x < 0 || x > dim.getLargeur()) throw XYException("X en dehors de l'image !", 'x');
	if(y < 0 || y > dim.getHauteur()) throw XYException("Y en dehors de l'image !", 'y');
	
	matrice[x][y].setRouge(color.getRouge());
	matrice[x][y].setVert(color.getVert());
	matrice[x][y].setBleu(color.getBleu());
}

Couleur ImageRGB::getPixel(const int x, const int y) throw (XYException)
{
	if((x < 0 || x > dim.getLargeur()) || (y < 0 || y > dim.getHauteur())) throw XYException("X et Y en dehors de l'image !", 'd');
	if(x < 0 || x > dim.getLargeur()) throw XYException("X en dehors de l'image !", 'x');
	if(y < 0 || y > dim.getHauteur()) throw XYException("Y en dehors de l'image !", 'y');
	
	Couleur temp;
	
	temp.setRouge(matrice[x][y].getRouge());
	temp.setVert(matrice[x][y].getVert());
	temp.setBleu(matrice[x][y].getBleu());
	
	return temp;
}

void ImageRGB::setBackground(const Couleur& color)
{
	for(int x = 0; x < dim.getLargeur(); x++) 
		for(int y = 0; y < dim.getHauteur(); y++)
			setPixel(x, y, color);
}

void ImageRGB::importFromBMP(const char* name)
{
	WindowSDLimage temp(name);
	Couleur color;
	int r, g, b;
	
	Dimension d(temp.getWidth(),temp.getHeight());
	setDimension(d);
	
	for(int x = 0; x < dim.getLargeur(); x++)
		for(int y = 0; y < dim.getHauteur(); y++)
		{
			temp.getPixel(x, y, &r, &g, &b);
			color.setRouge(r);
			color.setVert(g);
			color.setBleu(b);
			setPixel(x, y, color);
		}
}

void ImageRGB::exportToBMP(const char* name)
{
	WindowSDLimage temp(dim.getLargeur(), dim.getHauteur());
	
	for(int x = 0; x < temp.getWidth(); x++)
		for(int y = 0; y < temp.getHeight(); y++)
			temp.setPixel(x, y, matrice[x][y].getRouge(), matrice[x][y].getVert(), matrice[x][y].getBleu());
	
	temp.exportToBMP(name);
}

void ImageRGB::Affiche() const
{
	cout << "[]ImageRGB " << getNom() << " : " << "ID=" << getId() << " " << dim.getLargeur() << "x" << dim.getHauteur() << endl;
}

Couleur** ImageRGB::AllocMatrix(int Largeur, int Hauteur)
{
	Couleur** temp = new Couleur*[Largeur];
	
	for(int x = 0; x < Largeur; x++)
		temp[x] = new Couleur[Hauteur];
		
	return temp;
}

void ImageRGB::FreeMatrix()
{
	for(int x = 0; x < dim.getLargeur() && matrice[x] != NULL; x++)
		delete[] matrice[x];
		
	delete matrice;
}

void ImageRGB::Dessine()
{
	WindowSDLimage temp(dim.getLargeur(), dim.getHauteur());
	
	for(int x = 0; x < temp.getWidth(); x++)
		for(int y = 0; y < temp.getHeight(); y++)
			temp.setPixel(x, y, matrice[x][y].getRouge(), matrice[x][y].getVert(), matrice[x][y].getBleu());
	
	
	WindowSDL::open(temp.getWidth(), temp.getHeight());
	
	WindowSDL::drawImage(temp, 0, 0);
	
	WindowSDL::waitClick();
	
	WindowSDL::close();
}

void ImageRGB::Dessine(const int x, const int y)
{
	WindowSDLimage temp(dim.getLargeur(), dim.getHauteur());
	
	for(int x = 0; x < temp.getWidth(); x++)
		for(int y = 0; y < temp.getHeight(); y++)
			temp.setPixel(x, y, matrice[x][y].getRouge(), matrice[x][y].getVert(), matrice[x][y].getBleu());
	
	WindowSDL::drawImage(temp, x, y);
}
