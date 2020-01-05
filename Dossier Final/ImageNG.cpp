#include "ImageNG.h"
#include "PixelNG.h"
#include "WindowSDLimage.h"
#include "WindowSDL.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

int ImageNG::comparaison = 0;
const int ImageNG::LUMINANCE = 0;
const int ImageNG::PIXEL_A_PIXEL = 1;

ImageNG::ImageNG()
{
	nom = NULL;
	matrice = NULL;
	setNom("default");
	setDimension(dim);
	setId(0);
}

ImageNG::ImageNG(int val, const char* name) : Image(val, name)
{
	matrice = NULL;
}

ImageNG::ImageNG(const ImageNG& image)
{
	nom = NULL;
	matrice = NULL;
	setDimension(image.dim);
	setNom(image.getNom());
	
	for(int x = 0; x < dim.getLargeur(); x++)
		for(int y = 0; y < dim.getHauteur(); y++)
			matrice[x][y] = image.matrice[x][y];
}

ImageNG::ImageNG(int nid, const char* unom, const Dimension& d)
{
	matrice = NULL;
	nom = NULL;
	setId(nid);
	setNom(unom);
	setDimension(d);
}

ImageNG::ImageNG(const char* path)
{
	nom = NULL;
	matrice = NULL;
	setDimension(dim);
	setNom("default");
	setId(0);

	importFromBMP(path);
}

ImageNG::~ImageNG()
{
	if (nom) delete nom;
	FreeMatrix();
}

void ImageNG::Save(ofstream &fichier) const 
{
	if(!fichier)
	{
		perror("Erreur d'ouverture");
		return;
	}
	
	Image::Save(fichier);
	
	int val;
	
	for(int x = 0; x < dim.getLargeur(); x++)
		for(int y = 0; y < dim.getHauteur(); y++)
		{
			val = matrice[x][y];
			
			fichier.write((char*)&val, sizeof(int));
		}
}

void ImageNG::Load(ifstream &fichier)
{
	if(!fichier)
	{
		perror("Erreur d'ouverture");
		return;
	}
	
	Image::Load(fichier);
	
	int val;
	
	for(int x = 0; x < dim.getLargeur(); x++)
		for(int y = 0; y < dim.getHauteur(); y++)
		{
			fichier.read((char*)&val, sizeof(int));
			
			matrice[x][y] = val;
		}
}

void ImageNG::setComparaison(int mode)
{
	comparaison = mode;
}

int ImageNG::getComparaison()
{
	return comparaison;
}

void ImageNG::addToPix(const int num)
{
	for(int x = 0; x < dim.getLargeur(); x++)
		for(int y = 0; y < dim.getHauteur(); y++)
		{
			if((matrice[x][y] + num) > 255)
				matrice[x][y] = 255;
			
			if((matrice[x][y] + num) < 255)
				matrice[x][y] += num;
		}
}

void ImageNG::removeFromPix(const int num)
{
	for(int x = 0; x < dim.getLargeur(); x++)
		for(int y = 0; y < dim.getHauteur(); y++)
		{
			if((matrice[x][y] - num) < 0)
				matrice[x][y] = 0;
			
			if((matrice[x][y] - num) > 0)
				matrice[x][y] -= num;
		}
}

void ImageNG::removeFromPixImageNG(ImageNG i2)
{
	for(int x = 0; x < this->dim.getLargeur(); x++)
		for(int y = 0; y < this->dim.getHauteur(); y++)
		{
			if((this->matrice[x][y] - i2.getPixel(x, y)) < 0)
				this->matrice[x][y] = 0;
			else
				this->matrice[x][y] -= i2.getPixel(x, y);
		}
}

ImageNG& ImageNG::operator=(const ImageNG& cpy)
{
	setNom(cpy.getNom());
	setId(cpy.getId());
	setDimension(cpy.dim);
	
	for(int x = 0; x < dim.getLargeur(); x++)
		for(int y = 0; y < dim.getHauteur(); y++)
			matrice[x][y] = cpy.matrice[x][y];
	
	return (*this);
}

ImageNG operator+(const ImageNG& cpy, const int num)
{
	ImageNG temp(cpy);
	
	temp.addToPix(num);
	
	return temp;
}

ImageNG operator+(const int num, const ImageNG& cpy)
{
	return cpy + num;
}

ImageNG operator+(const ImageNG& cpy, const PixelNG& pix) throw (XYException)
{
	ImageNG temp(cpy);
	
	if((pix.getX() > temp.getLargeur() || pix.getX() < 0) || (pix.getY() > temp.getHauteur() || pix.getY() < 0)) throw XYException("Coordonnees est hors de l'image !", 'd');
	if(pix.getX() > temp.getLargeur() || pix.getX() < 0) throw XYException("X est hors de l'image !", 'x');
	if(pix.getY() > temp.getHauteur() || pix.getY() < 0) throw XYException("Y est hors de l'image !", 'y');
	
	temp.setPixel(pix.getX(), pix.getY(), pix.getValeur());
	
	return temp;
}

ImageNG operator+(const PixelNG& pix, const ImageNG& cpy)
{
	return cpy + pix;
}

ImageNG& ImageNG::operator++()
{
	addToPix(20);
	
	return (*this);
}

ImageNG ImageNG::operator++(int)
{
	ImageNG temp(*this);
	
	++(*this);
	
	return temp;
}

ImageNG& ImageNG::operator--()
{
	removeFromPix(20);
	
	return (*this);
}

ImageNG ImageNG::operator--(int)
{
	ImageNG temp(*this);
	
	--(*this);
	
	return temp;
}

ImageNG operator-(const ImageNG& cpy, const int num)
{
	ImageNG temp(cpy);
	
	temp.removeFromPix(num);
	
	return temp;
}

ImageNG operator-(const int num, const ImageNG& cpy)
{
	return cpy - num;
}

ImageNG operator-(const ImageNG& i1, const ImageNG& i2)
{
	ImageNG temp(i1);
	ImageNG i(i2);
	
	temp.removeFromPixImageNG(i);
	
	return temp;
}

bool operator<(const ImageNG& i1, const ImageNG& i2) throw (XYException)
{
	ImageNG temp(i1);
	
	if(i1.dim.getLargeur() != i2.dim.getLargeur() || i1.dim.getHauteur() != i2.dim.getHauteur()) throw XYException("Largeur et Hauteur des deux images est diffente !", 'd');
	
	if(i1.dim.getLargeur() != i2.dim.getLargeur()) throw XYException("Largeur des deux images est diffente !", 'x');
	if(i1.dim.getHauteur() != i2.dim.getHauteur()) throw XYException("Hauteur des deux images est diffente !", 'y');
	
	if(ImageNG::getComparaison() == 0)
		return temp.compLum(i2) == -1;
	if(ImageNG::getComparaison() == 1)
		return temp.compPixel(i2, -1) == -1;
}

bool operator>(const ImageNG& i1, const ImageNG& i2) throw (XYException)
{
	ImageNG temp(i1);
	
	if(i1.dim.getLargeur() != i2.dim.getLargeur() || i1.dim.getHauteur() != i2.dim.getHauteur()) throw XYException("Largeur et Hauteur des deux images est diffente !", 'd');
	
	if(i1.dim.getLargeur() != i2.dim.getLargeur()) throw XYException("Largeur des deux images est diffente !", 'x');
	if(i1.dim.getHauteur() != i2.dim.getHauteur()) throw XYException("Hauteur des deux images est diffente !", 'y');
	
	if(ImageNG::getComparaison() == 0)
		return temp.compLum(i2) == 1;
	if(ImageNG::getComparaison() == 1)
		return temp.compPixel(i2, 1) == 1;
}

bool ImageNG::operator==(const ImageNG& i) throw (XYException)
{
	if(dim.getLargeur() != i.dim.getLargeur() || dim.getHauteur() != i.dim.getHauteur()) throw XYException("Largeur et Hauteur des deux images est diffente !", 'd');
	
	if(dim.getLargeur() != i.dim.getLargeur()) throw XYException("Largeur des deux images est diffente !", 'x');
	if(dim.getHauteur() != i.dim.getHauteur()) throw XYException("Hauteur des deux images est diffente !", 'y');
	
	if(ImageNG::getComparaison() == 0)
		return compLum(i) == 0;
	else
		return compPixel(i, 0) == 0;
}

ostream& operator<<(ostream& s, const ImageNG& cpy)
{
	s << endl << "ID : " << cpy.id << endl << "Nom : " << cpy.getNom() << endl << "Dimension : "<< cpy.dim.getLargeur() << "x" << cpy.dim.getHauteur() << endl << "Luminance : " << cpy.getLuminance() << endl << "Contraste : " << cpy.getContraste();
	
	return s;
}

int ImageNG::compLum(ImageNG i)
{
	if(getLuminance() < i.getLuminance())
		return -1;
	
	if(getLuminance() > i.getLuminance())
		return 1;
	
	if(getLuminance() == i.getLuminance())
		return 0;
}

int ImageNG::compPixel(ImageNG i, const int cmp)
{
	if(cmp == 1)
	{
		if(getPixel(0, 0) > i.getPixel(0, 0))
		{
			for(int x = 1; x < dim.getLargeur(); x++)
				for(int y = 1; y < dim.getHauteur(); y++)
				{
					if(getPixel(x, y) < i.getPixel(x, y))
						return 0;
				}
			
				return 1;
		}
		
		return 0;
	}
	
	if(cmp == -1)
	{
		if(getPixel(0, 0) < i.getPixel(0, 0))
		{
			for(int x = 1; x < dim.getLargeur(); x++)
				for(int y = 1; y < dim.getHauteur(); y++)
				{
					if(getPixel(x, y) > i.getPixel(x, y))
						return 0;
				}
			
				return -1;
		}
		
		return 0;
	}
	
	if(cmp == 0)
	{
		if(getPixel(0, 0) == i.getPixel(0, 0))
		{
			for(int x = 1; x < dim.getLargeur(); x++)
				for(int y = 1; y < dim.getHauteur(); y++)
				{
					if(getPixel(x, y) != i.getPixel(x, y))
						return -1;
				}
			
				return 0;
		}
		
		return -1;
	}
}

void ImageNG::setDimension(const Dimension& d)
{
	int** temp = AllocMatrix(d.getLargeur(), d.getHauteur());
	
	for(int x = 0; x < d.getLargeur(); x++)
		for(int y = 0; y < d.getHauteur(); y++)
			temp[x][y] = 0;
	
	if(matrice)
		for(int x = 0; x < dim.getLargeur(); x++)
			for(int y = 0; y < dim.getHauteur(); y++)
				if(x < d.getLargeur() && y < d.getHauteur()) temp[x][y] = matrice[x][y];
	
	if(matrice) FreeMatrix();
	
	dim.setLargeur(d.getLargeur());
	dim.setHauteur(d.getHauteur());
	
	matrice = temp;
}

void ImageNG::setPixel(int x, int y, int val) throw (RGBException, XYException)
{
	if(val > 255) throw RGBException("Valeur trop grande !", val);
	if(val < 0) throw RGBException("Valeur trop petite !", val);
	
	if((x < 0 || x > dim.getLargeur()) && (y < 0 || y > dim.getHauteur())) throw XYException("X et Y en dehors de l'image !", 'd');
	if(x < 0 || x > dim.getLargeur()) throw XYException("X en dehors de l'image !", 'x');
	if(y < 0 || y > dim.getHauteur()) throw XYException("Y en dehors de l'image !", 'y');
	
	matrice[x][y] = val;
}

int ImageNG::getPixel(int x, int y) throw (XYException)
{
	if((x < 0 || x > dim.getLargeur()) && (y < 0 || y > dim.getHauteur())) throw XYException("X et Y en dehors de l'image !", 'd');
	if(x < 0 || x > dim.getLargeur()) throw XYException("X en dehors de l'image !", 'x');
	if(y < 0 || y > dim.getHauteur()) throw XYException("Y en dehors de l'image !", 'y');
	
	return this->matrice[x][y];
}

int ImageNG::getLuminance() const
{
	int lum = 0;
	
	for(int x = 0; x < dim.getLargeur(); x++)
		for(int y = 0; y < dim.getHauteur(); y++)
			lum += matrice[x][y];
	
	return lum / (dim.getLargeur() * dim.getHauteur());
}

int ImageNG::getMaximum() const
{
	int max = 0;
	
	for(int x = 0; x < dim.getLargeur(); x++)
		for(int y = 0; y < dim.getHauteur(); y++)
			if(matrice[x][y] > max) max = matrice[x][y];
			
	return max;
}

int ImageNG::getMinimum() const
{
	int min = 255;
	
	for(int x = 0; x < dim.getLargeur(); x++)
		for(int y = 0; y < dim.getHauteur(); y++)
			if(matrice[x][y] < min) min = matrice[x][y];
			
	return min;
}

void ImageNG::setBackground(int val) throw (RGBException)
{
	if(val < 0 || val > 255) throw RGBException("Valeur incorecte !", val);
	
	for(int x = 0; x < dim.getLargeur(); x++) 
	{
		for(int y = 0; y < dim.getHauteur(); y++)
			setPixel(x, y, val);
	}
}

float ImageNG::getContraste() const
{
	int max = getMaximum(), min = getMinimum();
	
	float constraste = ((float)max - (float)min) / ((float)max + (float)min);

	return constraste;
}

void ImageNG::Affiche() const
{
	cout << "[]ImageNG" << getNom() << " : " << "ID=" << getId() << dim.getLargeur() << "x" << dim.getHauteur() << "luminance=" << this->getLuminance() << "contraste=" << this->getContraste() << endl;
}

void ImageNG::Dessine()
{
	WindowSDLimage temp(dim.getLargeur(), dim.getHauteur());
	
	for(int x = 0; x < temp.getWidth(); x++)
		for(int y = 0; y < temp.getHeight(); y++)
			temp.setPixel(x, y, matrice[x][y], matrice[x][y], matrice[x][y]);
	
	
	WindowSDL::open(temp.getWidth(), temp.getHeight());
	
	WindowSDL::drawImage(temp, 0, 0);
	
	WindowSDL::waitClick();
	
	WindowSDL::close();
}

void ImageNG::Dessine(const int x, const int y)
{
	WindowSDLimage temp(dim.getLargeur(), dim.getHauteur());
	
	for(int x = 0; x < temp.getWidth(); x++)
		for(int y = 0; y < temp.getHeight(); y++)
			temp.setPixel(x, y, matrice[x][y], matrice[x][y], matrice[x][y]);
	
	WindowSDL::drawImage(temp, x, y);
}

int** ImageNG::AllocMatrix(int Largeur, int Hauteur)
{
	int** temp = new int*[Largeur];
	
	for(int x = 0; x < Largeur; x++)
		temp[x] = new int[Hauteur];
		
	return temp;
}

void ImageNG::FreeMatrix()
{
	for(int x = 0; x < dim.getLargeur(); x++)
		delete[] matrice[x];
		
	delete[] matrice;
}

void ImageNG::importFromBMP(const char* name)
{
	WindowSDLimage temp(name);
	int r, g, b;
	
	Dimension d(temp.getWidth(),temp.getHeight());
	setDimension(d);
	
	for(int x = 0; x < temp.getWidth(); x++)
		for(int y = 0; y < temp.getHeight(); y++)
		{
			temp.getPixel(x, y, &r, &g, &b);
			setPixel(x, y, ((r + g + b) / 3));
		}
}

void ImageNG::exportToBMP(const char* name)
{
	WindowSDLimage temp(dim.getLargeur(), dim.getHauteur());
	
	for(int x = 0; x < temp.getWidth(); x++)
		for(int y = 0; y < temp.getHeight(); y++)
			temp.setPixel(x, y, matrice[x][y], matrice[x][y], matrice[x][y]);
	
	temp.exportToBMP(name);
}
