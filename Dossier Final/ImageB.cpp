#include "ImageB.h"
#include "WindowSDLimage.h"
#include "WindowSDL.h"

using namespace std;

Couleur ImageB::couleurTrue(255, 255, 255);
Couleur ImageB::couleurFalse(0, 0, 0);

ImageB::ImageB()
{
	nom = NULL;
	matrice = NULL;
	setId(1);
	setDimension(dim);
	setNom("Default");
}

ImageB::ImageB(bool val, const char* name)
{
	nom = NULL;
	matrice = NULL;
	setId(val);
	setDimension(dim);
	setNom(name);
}

ImageB::ImageB(const ImageB& image)
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

ImageB::ImageB(int nid, const char* unom, const Dimension& d)
{
	nom = NULL;
	matrice = NULL;
	setDimension(d);
	setId(nid);
	setNom(unom);
}

ImageB::ImageB(const char* path)
{
	nom = NULL;
	matrice = NULL;
	setDimension(dim);
	setNom("default");
	setId(1);

	importFromBMP(path);
}

ImageB::~ImageB()
{
	if (nom) delete nom;
	FreeMatrix();
}

void ImageB::Save(ofstream &fichier) const 
{
	if(!fichier)
	{
		perror("Erreur d'ouverture");
		return;
	}
	
	fichier.write((char*)this, sizeof(ImageB));
}

void ImageB::Load(ifstream &fichier)
{
	if(!fichier)
	{
		perror("Erreur d'ouverture");
		return;
	}
	
	fichier.read((char*)this, sizeof(ImageB));
}

void ImageB::setPixel(const int x, const int y, const bool val) throw (XYException)
{
	if((x < 0 || x > dim.getLargeur()) || (y < 0 || y > dim.getHauteur())) throw XYException("X et Y en dehors de l'image !", 'd');
	if(x < 0 || x > dim.getLargeur()) throw XYException("X en dehors de l'image !", 'x');
	if(y < 0 || y > dim.getHauteur()) throw XYException("Y en dehors de l'image !", 'y');
	
	matrice[x][y] = val;
}

bool ImageB::getPixel(const int x, const int y) const throw (XYException)
{
	if((x < 0 || x > dim.getLargeur()) || (y < 0 || y > dim.getHauteur())) throw XYException("X et Y en dehors de l'image !", 'd');
	if(x < 0 || x > dim.getLargeur()) throw XYException("X en dehors de l'image !", 'x');
	if(y < 0 || y > dim.getHauteur()) throw XYException("Y en dehors de l'image !", 'y');
	
	return matrice[x][y];
}

void ImageB::setDimension(const Dimension& d)
{
	bool** temp = AllocMatrix(d.getLargeur(), d.getHauteur());
	
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

void ImageB::Affiche() const
{
	cout << endl;
	cout << "ID : " << getId() << endl;
	cout << "Nom : " << getNom() << endl;
	cout << "Dimension : " << dim.getLargeur() << "x" << dim.getHauteur() << endl;
}

bool** ImageB::AllocMatrix(int Largeur, int Hauteur)
{
	bool** temp = new bool*[Largeur];
	
	for(int x = 0; x < Largeur; x++)
		temp[x] = new bool[Hauteur];
		
	return temp;
}

void ImageB::FreeMatrix()
{
	for(int x = 0; x < dim.getLargeur(); x++)
		delete[] matrice[x];
		
	delete[] matrice;
}

void ImageB::setBackground(const bool val)
{
	for(int x = 0; x < dim.getLargeur(); x++) 
	{
		for(int y = 0; y < dim.getHauteur(); y++)
			setPixel(x, y, val);
	}
}

void ImageB::importFromBMP(const char* name)
{
	WindowSDLimage temp(name);
	int r, g, b;
	
	Dimension d(temp.getWidth(),temp.getHeight());
	setDimension(d);
	
	for(int x = 0; x < temp.getWidth(); x++)
		for(int y = 0; y < temp.getHeight(); y++)
		{
			temp.getPixel(x, y, &r, &g, &b);
			
			if(r || g || b)
				setPixel(x, y, true);
			else
				setPixel(x, y, false);
		}
}

void ImageB::exportToBMP(const char* name)
{
	WindowSDLimage temp(dim.getLargeur(), dim.getHauteur());
	
	for(int x = 0; x < temp.getWidth(); x++)
		for(int y = 0; y < temp.getHeight(); y++)
		{
			if(matrice[x][y])
				temp.setPixel(x, y, 255, 255, 255);
			else
				temp.setPixel(x, y, 0, 0, 0);
		}
	
	temp.exportToBMP(name);
}

void ImageB::Dessine()
{
	WindowSDLimage temp(dim.getLargeur(), dim.getHauteur());
	
	for(int x = 0; x < temp.getWidth(); x++)
		for(int y = 0; y < temp.getHeight(); y++)
		{
			if(matrice[x][y])
				temp.setPixel(x, y, 255, 255, 255);
			else
				temp.setPixel(x, y, 0, 0, 0);
		}
	
	
	WindowSDL::open(temp.getWidth(), temp.getHeight());
	
	WindowSDL::drawImage(temp, 0, 0);
	
	WindowSDL::waitClick();
	
	WindowSDL::close();
}

void ImageB::Dessine(const int x, const int y)
{
	WindowSDLimage temp(dim.getLargeur(), dim.getHauteur());
	
	for(int i = 0; i < temp.getWidth(); i++)
		for(int j = 0; j < temp.getHeight(); j++)
		{
			if(matrice[i][j])
				temp.setPixel(i, j, 255, 255, 255);
			else
				temp.setPixel(i, j, 0, 0, 0);
		}
	
	WindowSDL::drawImage(temp, x, y);
}

ImageB& ImageB::operator=(const ImageB& cpy)
{
	setNom(cpy.getNom());
	setId(cpy.getId());
	setDimension(cpy.dim);
	
	for(int x = 0; x < dim.getLargeur(); x++)
		for(int y = 0; y < dim.getHauteur(); y++)
			matrice[x][y] = cpy.matrice[x][y];
	
	return (*this);
}

ImageB operator+(const ImageB& image, const PixelB& pix) throw (XYException)
{
	if((pix.getX() > image.dim.getLargeur() || pix.getX() < 0) || (pix.getY() > image.dim.getHauteur() || pix.getY() < 0)) throw XYException("Coordonnees est hors de l'image !", 'd');
	if(pix.getX() > image.dim.getLargeur() || pix.getX() < 0) throw XYException("X est hors de l'image !", 'x');
	if(pix.getY() > image.dim.getHauteur() || pix.getY() < 0) throw XYException("Y est hors de l'image !", 'y');
	
	ImageB temp(image);
	
	temp.setPixel(pix.getX(), pix.getY(), pix.getValeur());
	
	return temp;
}

ImageB operator+(const PixelB& pix, const ImageB& cpy)
{
	return cpy + pix;
}

ostream& operator<<(ostream& s, const ImageB& cpy)
{
	s << endl << "ID : " << cpy.getId() << endl << "Nom : " << cpy.getNom() << endl << "Dimension : "<< cpy.dim.getLargeur() << "x" << cpy.dim.getHauteur() << endl;
	
	return s;
}
