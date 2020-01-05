#include "Moteur.h"

#include <stdlib.h>

Moteur::Moteur()
{

}

Moteur::~Moteur()
{

}

void Moteur::Affiche()
{
	cout << "----------ImagesNG----------" << endl;
	ImagesNG.Affiche();
	
	cout << "----------ImagesRGB---------" << endl;
	ImagesRGB.Affiche();
	
	cout << "----------ImagesB-----------" << endl;
	ImagesB.Affiche();
}

int Moteur::Insere(Image *pImage)
{
	ImageB* pB = dynamic_cast<ImageB*>(pImage);
	if(pB != NULL)
	{
		pB->setId(rand() % 50);
		ImagesB.insere(*pB);
		return pB->getId();
	}
	
	ImageNG* pNG = dynamic_cast<ImageNG*>(pImage);
	if(pNG != NULL) 
	{
		pNG->setId(rand() % 50);
		ImagesNG.insere(*pNG);
		return pNG->getId();
	}

	ImageRGB* pRGB = dynamic_cast<ImageRGB*>(pImage);
	if(pRGB != NULL) 
	{
		pRGB->setId(rand() % 50);
		ImagesRGB.insere(*pRGB);
		return pRGB->getId();
	}
}

ImageNG Moteur::getImageNG(const int id) throw (MoteurException)
{
	Iterateur<ImageNG> it(ImagesNG);
	
	for(; !it.end(); it++)
	{
		fprintf(stderr, "%s\n", ((ImageNG)it).getNom());
		
		if(((ImageNG)it).getId() == id)
			return (ImageNG)it;
	}
	
	throw MoteurException("Image non trouvee (getImageNG)");
}

Image* Moteur::getImage(const int id) throw (MoteurException)
{
	Iterateur<ImageNG> itNG(ImagesNG);
	Iterateur<ImageB> itB(ImagesB);
	Iterateur<ImageRGB> itRGB(ImagesRGB);
	
	for(; !itNG.end(); itNG++)
	{
		if(((ImageNG)itNG).getId() == id)
			return itNG.getValeur();
	}
	
	for(; !itB.end(); itB++)
	{
		if(((ImageB)itB).getId() == id)
			return itB.getValeur();
	}
	
	for(; !itRGB.end(); itRGB++)
	{
		if(((ImageRGB)itRGB).getId() == id)
			return itRGB.getValeur();
	}
	
	throw MoteurException("Image non trouvee (getImage)");
}

void Moteur::SupprimeImage(const int id) throw (MoteurException)
{
	Iterateur<ImageNG> itNG(ImagesNG);
	Iterateur<ImageB> itB(ImagesB);
	Iterateur<ImageRGB> itRGB(ImagesRGB);
	
	for(; !itNG.end(); itNG++)
	{
		if(((ImageNG)itNG).getId() == id)
		{
			itNG.remove();
			return;
		}
	}
	
	for(; !itB.end(); itB++)
	{
		if(((ImageB)itB).getId() == id)
		{
			itB.remove();
			return;
		}
	}
	
	for(; !itRGB.end(); itRGB++)
	{
		if(((ImageRGB)itRGB).getId() == id)
		{
			itRGB.remove();
			return;
		}
	}
	
	throw MoteurException("Image non trouvee (SupprimeImage)");
}

int Moteur::ImporteImageNG(const char * fichier)
{
	ImageNG im(fichier);
	
	return Insere(&im);
}

int Moteur::ImporteImageRGB(const char * fichier)
{
	ImageRGB im(fichier);
	
	return Insere(&im);
}

void Moteur::ExporterBMP(const int id, const char* fichier)  throw (MoteurException)
{
	Image* im(getImage(id));
	
	im->exportToBMP(fichier);
}

void Moteur::VisualiseImage(const int id)  throw (MoteurException)
{
	Image* image(getImage(id));
	
	cout << "----------Info Image---------" << endl;
	
	cout << image << endl;
	
	image->Dessine();
}

void Moteur::VisualiseImages(const int id1, const int id2)  throw (MoteurException)
{
	Image* i1(getImage(id1));
	Image* i2(getImage(id2));
	
	if(i1->getHauteur() >= i2->getHauteur())
		WindowSDL::open(i1->getLargeur() + i2->getLargeur(), i1->getHauteur());
	else
		WindowSDL::open(i1->getLargeur() + i2->getLargeur(), i2->getHauteur());
	
	i1->Dessine(0, 0);
	i2->Dessine(i1->getLargeur(), 0);
	
	WindowSDL::waitClick();
	
	WindowSDL::close();
}

int Moteur::AugmenteLuminosite(const int id, const int val) throw (MoteurException)
{
	Image* im(getImage(id));
	ImageNG* pNG = dynamic_cast<ImageNG*>(im);
	
	pNG = pNG + val;
	
	return Insere(pNG);
}

int Moteur::DiminueLuminosite(const int id, const int val) throw (MoteurException)
{
	Image* im(getImage(id));
	ImageNG* pNG = dynamic_cast<ImageNG*>(im);
	
	pNG = pNG - val;
	
	return Insere(pNG);
}

int Moteur::Soustraire(const int id1, const int id2) throw (MoteurException)
{
	ImageNG* temp;
	Image* i1(getImage(id1));
	Image* i2(getImage(id2));
	ImageNG* pNG2 = dynamic_cast<ImageNG*>(i2);
	ImageNG* pNG1 = dynamic_cast<ImageNG*>(i1);
	
	*temp = *pNG1 - *pNG2;
	
	return Insere(temp);
}

int Moteur::Seuillage(int id, int seuil) throw (MoteurException)
{
	ImageNG i1(getImageNG(id));
	ImageB temp = Traitements::Seuillage(i1, seuil);
	
	return Insere(&temp);
}

int Moteur::FiltreMedian(int id, int tailleFiltre) throw (MoteurException)
{
	ImageNG i1(getImageNG(id));
	ImageNG temp = Traitements::FiltreMedian(i1, tailleFiltre);
	
	return Insere(&temp);
}

int Moteur::FiltreMoyenneur(int id, int tailleFiltre) throw (MoteurException)
{
	ImageNG i1(getImageNG(id));
	ImageNG temp = Traitements::FiltreMoyenneur(i1, tailleFiltre);
	
	return Insere(&temp);
}

int Moteur::FiltreMoyenneurSelection(int id, int tailleFiltre) throw (MoteurException)
{
	ImageNG i1(getImageNG(id));
	Pixel p1, p2;
	WindowSDLclick click;
	
	WindowSDL::open(i1.getLargeur(), i1.getHauteur());
	
	i1.Dessine(0, 0);
	
	click = WindowSDL::waitClick();
	
	p1.setX(click.getX());
	p1.setY(click.getY());
	
	click = WindowSDL::waitClick();
	
	p2.setX(click.getX());
	p2.setY(click.getY());
	
	WindowSDL::close();
	
	ImageNG temp = Traitements::FiltreMoyenneur(i1, tailleFiltre, p1, p2);
	
	return Insere(&temp);
}

int Moteur::Dilatation(int id, int tailleFiltre) throw (MoteurException)
{
	ImageNG i1(getImageNG(id));
	ImageNG temp = Traitements::Dilatation(i1, tailleFiltre);
	
	return Insere(&temp);
}

int Moteur::Erosion(int id, int tailleFiltre) throw (MoteurException)
{
	ImageNG i1(getImageNG(id));
	ImageNG temp = Traitements::Erosion(i1, tailleFiltre);
	
	return Insere(&temp);
}

int Moteur::Negatif(int id) throw (MoteurException)
{
	ImageNG i1(getImageNG(id));
	ImageNG temp = Traitements::Negatif(i1);
	
	return Insere(&temp);
}
