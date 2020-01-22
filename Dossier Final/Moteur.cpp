#include "Moteur.h"

#include <stdlib.h>


Moteur::Moteur()
{
	fichierLog.open("traces.log", ios_base::app);
}

Moteur::~Moteur()
{
	fichierLog.close();
}

void Moteur::log(const char* str)
{
	fichierLog << str << endl;
}

void Moteur::SaveState(ofstream& fImages)
{
	if(!fImages)
	{
		perror("Erreur d'ouverture");
		return;
	}
	
	int val;
	
	val = ImagesB.getNombreElements();
	fImages.write((char*)&val, sizeof(int));
	
	val = ImagesNG.getNombreElements();
	fImages.write((char*)&val, sizeof(int));
	
	val = ImagesRGB.getNombreElements();
	fImages.write((char*)&val, sizeof(int));
	
	cout << endl;
	cout << "Exportation de " << ImagesB.getNombreElements() + ImagesNG.getNombreElements() + ImagesRGB.getNombreElements() << " elements vers Sauvegarde.dat..." << endl;
	
	if(ImagesB.getNombreElements())
	{
		Iterateur<ImageB> itB(ImagesB);
		for(; !itB.end(); itB++) { ((ImageB)itB).Save(fImages); cout << ((ImageB)itB).getNom() << endl; }
	}
	
	if(ImagesNG.getNombreElements())
	{
		Iterateur<ImageNG> itNG(ImagesNG);
		for(; !itNG.end(); itNG++) { ((ImageNG)itNG).Save(fImages); cout << ((ImageNG)itNG).getNom() << endl; }
	}
	
	if(ImagesRGB.getNombreElements())
	{
		Iterateur<ImageRGB> itRGB(ImagesRGB);
		for(; !itRGB.end(); itRGB++) { ((ImageRGB)itRGB).Save(fImages); cout << ((ImageRGB)itRGB).getNom() << endl; }
	}
	
	cout << endl;
	
	log("Images exportees vers Sauvegarde.dat");
}

void Moteur::LoadState(ifstream& fImages)
{
	if(!fImages)
	{
		perror("\nErreur d'ouverture");
		return;
	}
	
	int B, NG, RGB;
	
	fImages.read((char*)&B, sizeof(int));
	fImages.read((char*)&NG, sizeof(int));
	fImages.read((char*)&RGB, sizeof(int));
	
	if(B)
	{
		ImageB tempB;
		for(int i = 0; i < B; i++)
		{
			tempB.Load(fImages);
			Insere(&tempB);
		}
	}
	
	if(NG)
	{
		ImageNG tempNG;
		for(int i = 0; i < NG; i++)
		{
			tempNG.Load(fImages);
			Insere(&tempNG);
		}
	}
	
	if(RGB)
	{
		ImageRGB tempRGB;
		for(int i = 0; i < RGB; i++)
		{
			tempRGB.Load(fImages);
			Insere(&tempRGB);
		}
	}
	
	fprintf(stderr, "\n\t\t\t------------------------\n");
	
	if(B > 1)
		fprintf(stderr, "\t\t\t| %d ImagesB   chargees |\n%", B);
	else
		fprintf(stderr, "\t\t\t| %d ImagesB   chargee  |\n%", B);
	
	if(NG > 1)
		fprintf(stderr, "\t\t\t| %d ImagesNG  chargees |\n%", NG);
	else
		fprintf(stderr, "\t\t\t| %d ImagesNG  chargee  |\n%", NG);
	
	if(RGB > 1)
		fprintf(stderr, "\t\t\t| %d ImagesRGB chargees |\n%", RGB);
	else
		fprintf(stderr, "\t\t\t| %d ImagesRGB chargee  |\n%", RGB);
	
	fprintf(stderr, "\t\t\t------------------------\n\n");
	
	log("Sauvegarde.dat charge");
}

void Moteur::Affiche()
{
	cout << "\n------------------------------ImagesNG------------------------------" << endl;
	ImagesNG.Affiche();
	
	cout << "------------------------------ImagesRGB------------------------------" << endl;
	ImagesRGB.Affiche();
	
	cout << "------------------------------ImagesB------------------------------\n" << endl;
	ImagesB.Affiche();
}

int Moteur::Insere(Image *pImage)
{
	char buff[80];
	
	ImageB* pB = dynamic_cast<ImageB*>(pImage);
	if(pB != NULL)
	{
		pB->setId(getLastID() + 1);
		ImagesB.insere(*pB);
		sprintf(buff, "ImagesB(%d) %s inseree", pB->getId(), pB->getNom());
		log(buff);
		return pB->getId();
	}
	
	ImageNG::setComparaison(ImageNG::LUMINANCE);
	ImageNG* pNG = dynamic_cast<ImageNG*>(pImage);
	if(pNG != NULL) 
	{
		pNG->setId(getLastID() + 1);
		ImagesNG.insere(*pNG);
		sprintf(buff, "ImagesNG(%d) %s inseree", pNG->getId(), pNG->getNom());
		log(buff);
		return pNG->getId();
	}

	ImageRGB* pRGB = dynamic_cast<ImageRGB*>(pImage);
	if(pRGB != NULL) 
	{
		pRGB->setId(getLastID() + 1);
		ImagesRGB.insere(*pRGB);
		sprintf(buff, "ImagesRGB(%d) %s inseree", pRGB->getId(), pRGB->getNom());
		log(buff);
		return pRGB->getId();
	}
}

int Moteur::getLastID()
{
	int id = 0;
	
	Iterateur<ImageB> itB(ImagesB);
	if(ImagesB.getNombreElements() > 0)
		for(int i = 0; i < ImagesB.getNombreElements() && !itB.end(); itB++, i++)
			if(((ImageB)itB).getId() > id) id = ((ImageB)itB).getId();
	
	Iterateur<ImageNG> itNG(ImagesNG);
	if(ImagesNG.getNombreElements() > 0)
		for(int i = 0; i < ImagesNG.getNombreElements() && !itNG.end(); itNG++, i++)
			if(((ImageNG)itNG).getId() > id) id = ((ImageNG)itNG).getId();
	
	Iterateur<ImageRGB> itRGB(ImagesRGB);
	if(ImagesRGB.getNombreElements() > 0)
		for(int i = 0; i < ImagesRGB.getNombreElements() && !itRGB.end(); itRGB++, i++)
			if(((ImageRGB)itRGB).getId() > id) id = ((ImageRGB)itRGB).getId();
	
	return id;
}

int Moteur::getImageType(Image* src)
{
	ImageB* pB = dynamic_cast<ImageB*>(src);
	if(pB != NULL)
	{
		return 1;
	}
	
	ImageNG::setComparaison(ImageNG::LUMINANCE);
	ImageNG* pNG = dynamic_cast<ImageNG*>(src);
	if(pNG != NULL) 
	{
		return 2;
	}

	ImageRGB* pRGB = dynamic_cast<ImageRGB*>(src);
	if(pRGB != NULL) 
	{
		return 3;
	}
	
	return 0;
}

void Moteur::ImportCSV(const char* fichier)
{
	fstream file(fichier, ios::in);
	char line[80];
	char buff[80];
	
	int i = 0, j = 0;
	
	if(!file.good())
	{
		perror("Erreur d'ouverture");
		return;
	}
	
	while(file.good())
	{
		file.getline(line, sizeof(line), ':');
		
		if(strcmp(line, "NG") == 0)
		{
			file.getline(line, sizeof(line), '\n');
			line[strlen(line)] = '\0';
			try
			{
				ImageNG temp(line);
				Insere(&temp);
				sprintf(buff, "%s Importee du fichier CSV", line);
				log(buff);
				i++;
			}
			catch(WindowSDLexception) {j++;}
		}
		else
		if(strcmp(line, "RGB") == 0)
		{
			file.getline(line, sizeof(line), '\n');
			line[strlen(line)] = '\0';
			try
			{
				ImageRGB temp(line);
				Insere(&temp);
				sprintf(buff, "%s Importee du fichier CSV", line);
				log(buff);
				i++;
			}
			catch(WindowSDLexception) {j++;}
		}
		else
		if(strcmp(line, "B") == 0)
		{
			file.getline(line, sizeof(line), '\n');
			line[strlen(line)] = '\0';
			try
			{
				ImageB temp(line);
				Insere(&temp);
				sprintf(buff, "%s Importee du fichier CSV", line);
				log(buff);
				i++;
			}
			catch(WindowSDLexception) {j++;}
		}
	}
	
	fprintf(stderr, "\n\t\t\t---------------------------------\n");
	if(i > 1)
		fprintf(stderr, "\t\t\t| %d images importees du fichier |\n", i);
	else
		fprintf(stderr, "\t\t\t| %d image importee du fichier   |\n", i);
	
	if(j > 1)
		fprintf(stderr, "\t\t\t| %d images non importees        |", j);
	else
		fprintf(stderr, "\t\t\t| %d image non importee          |", j);
	
	fprintf(stderr, "\n\t\t\t---------------------------------\n");
}

ImageNG Moteur::getImageNG(const int id) throw (MoteurException)
{
	Iterateur<ImageNG> it(ImagesNG);
	
	for(; !it.end(); it++)
	{
		if(((ImageNG)it).getId() == id)
			return (ImageNG)it;
	}
	
	throw MoteurException("Image non trouvee (getImageNG)");
}

Image* Moteur::getImage(const int id) throw (MoteurException)
{
	Iterateur<ImageNG> itNG(ImagesNG);
	for(; !itNG.end(); itNG++)
	{
		if(((ImageNG)itNG).getId() == id)
			return itNG.getValeur();
	}
	
	Iterateur<ImageB> itB(ImagesB);
	for(; !itB.end(); itB++)
	{
		if(((ImageB)itB).getId() == id)
			return itB.getValeur();
	}
	
	Iterateur<ImageRGB> itRGB(ImagesRGB);
	for(; !itRGB.end(); itRGB++)
	{
		if(((ImageRGB)itRGB).getId() == id)
			return itRGB.getValeur();
	}
	
	throw MoteurException("Image non trouvee (getImage)");
}

void Moteur::SupprimeImage(const int id) throw (MoteurException)
{
	char buff[80];
	
	Iterateur<ImageNG> itNG(ImagesNG);
	for(; !itNG.end(); itNG++)
	{
		if(((ImageNG)itNG).getId() == id)
		{
			itNG.remove();
			sprintf(buff, "ImageNG %d supprimee", id);
			log(buff);
			return;
		}
	}
	
	Iterateur<ImageB> itB(ImagesB);
	for(; !itB.end(); itB++)
	{
		if(((ImageB)itB).getId() == id)
		{
			itB.remove();
			sprintf(buff, "ImageB %d supprimee", id);
			log(buff);
			return;
		}
	}
	
	Iterateur<ImageRGB> itRGB(ImagesRGB);
	for(; !itRGB.end(); itRGB++)
	{
		if(((ImageRGB)itRGB).getId() == id)
		{
			itRGB.remove();
			sprintf(buff, "ImageRGB %d supprimee", id);
			log(buff);
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

int Moteur::ImporteImageB(const char * fichier)
{
	ImageB im(fichier);
	
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
	
	char buff[80];
	
	sprintf(buff, "Image %d exporte vers %s", id, fichier);
	log(buff);
}

void Moteur::VisualiseImage(const int id)  throw (MoteurException)
{
	Image* tmp(getImage(id));
	
	ImageB* 		pB;
	ImageNG* 	pNG;
	ImageRGB* 	pRGB;
	
	const int ret = getImageType(tmp);
	
	if(ret == 0)
		throw MoteurException("Cette image n'est d'aucun type d'images (VisualiseImage)");
	if(ret == 1)
		pB = dynamic_cast<ImageB*>(tmp);
	if(ret == 2)
		pNG = dynamic_cast<ImageNG*>(tmp);
	if(ret == 3)
		pRGB = dynamic_cast<ImageRGB*>(tmp);
	
	
	if(ret == 1)	pB->Dessine();
	if(ret == 2)	pNG->Dessine();
	if(ret == 3)	pRGB->Dessine();
}


void Moteur::VisualiseImages(const int id1, const int id2)  throw (MoteurException)
{
	Image* i1(getImage(id1));
	Image* i2(getImage(id2));
	
	ImageB* 		pB1, *pB2;
	ImageNG* 	pNG1, *pNG2;
	ImageRGB* 	pRGB1, *pRGB2;
	
	int ret1 = getImageType(i1);
	
	if(ret1 == 0)
		throw MoteurException("Cette image n'est d'aucun type d'images (VisualiseImage)");
	if(ret1 == 1)
		pB1 = dynamic_cast<ImageB*>(i1);
	if(ret1 == 2)
		pNG1 = dynamic_cast<ImageNG*>(i1);
	if(ret1 == 3)
		pRGB1 = dynamic_cast<ImageRGB*>(i1);
	
	int ret2 = getImageType(i2);
	
	if(ret2 == 0)
		throw MoteurException("Cette image n'est d'aucun type d'images (VisualiseImage)");
	if(ret2 == 1)
		pB2 = dynamic_cast<ImageB*>(i2);
	if(ret2 == 2)
		pNG2 = dynamic_cast<ImageNG*>(i2);
	if(ret2 == 3)
		pRGB2 = dynamic_cast<ImageRGB*>(i2);
	
	// 											IMAGEB
	if(ret1 == 1 && ret2 == 1)
	{
		if(pB1->getHauteur() >= pB2->getHauteur())
			WindowSDL::open(pB1->getLargeur() + pB2->getLargeur(), pB1->getHauteur());
		else
			WindowSDL::open(pB1->getLargeur() + pB2->getLargeur(), pB2->getHauteur());
	
		pB1->Dessine(0, 0);
		pB2->Dessine(pB1->getLargeur(), 0);
	}
	
	if(ret1 == 1 && ret2 == 2)
	{
		if(pB1->getHauteur() >= pNG2->getHauteur())
			WindowSDL::open(pB1->getLargeur() + pNG2->getLargeur(), pB1->getHauteur());
		else
			WindowSDL::open(pB1->getLargeur() + pNG2->getLargeur(), pNG2->getHauteur());
	
		pB1->Dessine(0, 0);
		pNG2->Dessine(pB1->getLargeur(), 0);
	}
	
	if(ret1 == 1 && ret2 == 3)
	{
		if(pB1->getHauteur() >= pRGB2->getHauteur())
			WindowSDL::open(pB1->getLargeur() + pRGB2->getLargeur(), pB1->getHauteur());
		else
			WindowSDL::open(pB1->getLargeur() + pRGB2->getLargeur(), pRGB2->getHauteur());
	
		pB1->Dessine(0, 0);
		pRGB2->Dessine(pB1->getLargeur(), 0);
	}
	
	// 											IMAGENG
	if(ret1 == 2 && ret2 == 1)
	{
		if(pNG1->getHauteur() >= pB2->getHauteur())
			WindowSDL::open(pNG1->getLargeur() + pB2->getLargeur(), pNG1->getHauteur());
		else
			WindowSDL::open(pNG1->getLargeur() + pB2->getLargeur(), pB2->getHauteur());
	
		pNG1->Dessine(0, 0);
		pB2->Dessine(pNG1->getLargeur(), 0);
	}
	
	if(ret1 == 2 && ret2 == 2)
	{
		if(pNG1->getHauteur() >= pNG2->getHauteur())
			WindowSDL::open(pNG1->getLargeur() + pNG2->getLargeur(), pNG1->getHauteur());
		else
			WindowSDL::open(pNG1->getLargeur() + pNG2->getLargeur(), pNG2->getHauteur());
	
		pNG1->Dessine(0, 0);
		pNG2->Dessine(pNG1->getLargeur(), 0);
	}
	
	if(ret1 == 2 && ret2 == 3)
	{
		if(pNG1->getHauteur() >= pRGB2->getHauteur())
			WindowSDL::open(pNG1->getLargeur() + pRGB2->getLargeur(), pNG1->getHauteur());
		else
			WindowSDL::open(pNG1->getLargeur() + pRGB2->getLargeur(), pRGB2->getHauteur());
	
		pNG1->Dessine(0, 0);
		pRGB2->Dessine(pNG1->getLargeur(), 0);
	}
	
	
	// 											IMAGERGB
	if(ret1 == 3 && ret2 == 1)
	{
		if(pRGB1->getHauteur() >= pB2->getHauteur())
			WindowSDL::open(pRGB1->getLargeur() + pB2->getLargeur(), pRGB1->getHauteur());
		else
			WindowSDL::open(pRGB1->getLargeur() + pB2->getLargeur(), pB2->getHauteur());
	
		pRGB1->Dessine(0, 0);
		pB2->Dessine(pRGB1->getLargeur(), 0);
	}
	
	if(ret1 == 3 && ret2 == 2)
	{
		if(pRGB1->getHauteur() >= pNG2->getHauteur())
			WindowSDL::open(pRGB1->getLargeur() + pNG2->getLargeur(), pRGB1->getHauteur());
		else
			WindowSDL::open(pRGB1->getLargeur() + pNG2->getLargeur(), pNG2->getHauteur());
	
		pRGB1->Dessine(0, 0);
		pNG2->Dessine(pRGB1->getLargeur(), 0);
	}
	
	if(ret1 == 3 && ret2 == 3)
	{
		if(pRGB1->getHauteur() >= pRGB2->getHauteur())
			WindowSDL::open(pRGB1->getLargeur() + pRGB2->getLargeur(), pRGB1->getHauteur());
		else
			WindowSDL::open(pRGB1->getLargeur() + pRGB2->getLargeur(), pRGB2->getHauteur());
	
		pRGB1->Dessine(0, 0);
		pRGB2->Dessine(pRGB1->getLargeur(), 0);
	}
	
	
	WindowSDL::waitClick();
	
	WindowSDL::close();
}

int Moteur::AugmenteLuminosite(const int id, const int val) throw (MoteurException)
{
	Image* im(getImage(id));
	ImageNG* pNG = dynamic_cast<ImageNG*>(im);
	ImageRGB* pRGB = dynamic_cast<ImageRGB*>(im);
	
	if(pNG)
	{
		ImageNG temp(*pNG + val);
		temp.setId(getLastID());
	
		char format[80];
	
		sprintf(format, "(AugmenteLuminosite(%d) de %d)", id, val);
	
		char nom[80];
		strcpy(nom, temp.getNom());
		strcat(nom, format);
	
		temp.setNom(nom);
	
		char buff[80];
		sprintf(buff, "Luminosite de l'Image %d augmentee de %d", id, val);
		log(buff);
	
		return Insere(&temp);
	}
	
	if(pRGB)
	{
		ImageNG temp1(pRGB->getRouge() + val), temp2(pRGB->getVert() + val), temp3(pRGB->getBleu() + val);
		cout << "Yeet" << endl;
		ImageRGB temp(*pRGB);
		temp.setRGB(temp1, temp2, temp3);
		cout << "Yeet" << endl;
		temp.setId(getLastID());
	
		char format[80];
	
		sprintf(format, "(AugmenteLuminosite(%d) de %d)", id, val);
	
		char nom[80];
		strcpy(nom, temp.getNom());
		strcat(nom, format);
	
		temp.setNom(nom);
	
		char buff[80];
		sprintf(buff, "Luminosite de l'Image %d augmentee de %d", id, val);
		log(buff);
	
		return Insere(&temp);
	}
}

int Moteur::DiminueLuminosite(const int id, const int val) throw (MoteurException)
{
	Image* im(getImage(id));
	ImageNG* pNG = dynamic_cast<ImageNG*>(im);
	ImageRGB* pRGB = dynamic_cast<ImageRGB*>(im);
	
	if(pNG)
	{
		ImageNG temp(*pNG - val);
		temp.setId(getLastID());
	
		char format[80];
	
		sprintf(format, "(DiminueLuminosite(%d) de %d)", id, val);
	
		char nom[80];
		strcpy(nom, temp.getNom());
		strcat(nom, format);
	
		temp.setNom(nom);
	
		char buff[80];
		sprintf(buff, "Luminosite de l'Image %d diminuee de %d", id, val);
		log(buff);
	
		return Insere(&temp);
	}
	
	if(pRGB)
	{
		ImageNG temp1(pRGB->getRouge() - val), temp2(pRGB->getVert() - val), temp3(pRGB->getBleu() - val);
		cout << "Yeet" << endl;
		ImageRGB temp(*pRGB);
		temp.setRGB(temp1, temp2, temp3);
		cout << "Yeet" << endl;
		temp.setId(getLastID());
	
		char format[80];
	
		sprintf(format, "(DiminueLuminosite(%d) de %d)", id, val);
	
		char nom[80];
		strcpy(nom, temp.getNom());
		strcat(nom, format);
	
		temp.setNom(nom);
	
		char buff[80];
		sprintf(buff, "Luminosite de l'Image %d diminuee de %d", id, val);
		log(buff);
	
		return Insere(&temp);
	}
}

int Moteur::Soustraire(const int id1, const int id2) throw (MoteurException)
{
	Image* i1(getImage(id1));
	Image* i2(getImage(id2));
	ImageNG* pNG2 = dynamic_cast<ImageNG*>(i2);
	ImageNG* pNG1 = dynamic_cast<ImageNG*>(i1);
	
	ImageRGB* pRGB1 = dynamic_cast<ImageRGB*>(i1);
	ImageRGB* pRGB2 = dynamic_cast<ImageRGB*>(i2);
	
	if(pNG1)
	{
		if(pNG1->getDimension() != pNG2->getDimension()) throw MoteurException("Dimension des images differentes (Soustraire)");
	
		ImageNG temp(*pNG1 - *pNG2);
		temp.setId(getLastID());
	
		char format[80];
	
		sprintf(format, "(Soustraire(%d, %d))", id1, id2);
	
		char nom[80];
		strcpy(nom, temp.getNom());
		strcat(nom, format);
	
		temp.setNom(nom);
	
		char buff[80];
		sprintf(buff, "Image %d et Image %d soustraites", id1, id2);
		log(buff);
	
		return Insere(&temp);
	}
	
	if(pRGB1)
	{
		if(pRGB1->getDimension() != pRGB2->getDimension()) throw MoteurException("Dimension des images differentes (Soustraire)");
	
		ImageNG tempR((pRGB1->getRouge()) - (pRGB2->getRouge()));
		ImageNG tempG((pRGB1->getVert()) - (pRGB2->getVert()));
		ImageNG tempB((pRGB1->getBleu()) - (pRGB2->getBleu()));
		
		ImageRGB temp(*pRGB1);
		temp.setRGB(tempR, tempG, tempB);
		
		temp.setId(getLastID());
	
		char format[80];
	
		sprintf(format, "(Soustraire(%d, %d))", id1, id2);
	
		char nom[80];
		strcpy(nom, temp.getNom());
		strcat(nom, format);
	
		temp.setNom(nom);
	
		char buff[80];
		sprintf(buff, "Image %d et Image %d soustraites", id1, id2);
		log(buff);
	
		return Insere(&temp);
	}
}

int Moteur::Seuillage(int id, int seuil) throw (MoteurException)
{
	Image* i1(getImage(id));
	ImageB temp;
	
	ImageNG* pNG = dynamic_cast<ImageNG*>(i1);
	ImageRGB* pRGB = dynamic_cast<ImageRGB*>(i1);
	
	if(pNG)
		temp = Traitements::Seuillage(*pNG, seuil);
	
	if(pRGB)
		temp = Traitements::Seuillage(*pRGB, seuil);
	
	temp.setId(getLastID() + 1);
	
	char format[80];
	
	sprintf(format, "(Seuillage(%d))", seuil);
	
	char nom[80];
	strcpy(nom, temp.getNom());
	strcat(nom, format);
	
	temp.setNom(nom);
	
	char buff[80];
	sprintf(buff, "Image %d seuillee de %d", id, seuil);
	log(buff);
	
	return Insere(&temp);
}

int Moteur::FiltreMedian(int id, int tailleFiltre) throw (MoteurException)
{
	Image* i1(getImage(id));
	ImageNG* pNG = dynamic_cast<ImageNG*>(i1);
	ImageRGB* pRGB = dynamic_cast<ImageRGB*>(i1);
	
	if(pNG)
	{
		ImageNG temp(Traitements::FiltreMedian(*pNG, tailleFiltre));
		temp.setId(getLastID() + 1);
	
		char format[80];
	
		sprintf(format, "(Median(%d))", tailleFiltre);
	
		char nom[80];
		strcpy(nom, temp.getNom());
		strcat(nom, format);
	
		temp.setNom(nom);
		
		char buff[80];
		sprintf(buff, "Filtre Median de %d applique sur l'Image %d", tailleFiltre, id);
		log(buff);
	
		return Insere(&temp);
	}
	
	if(pRGB)
	{
		ImageRGB temp(Traitements::FiltreMedian(*pRGB, tailleFiltre));
		
		temp.setId(getLastID() + 1);
	
		char format[80];
	
		sprintf(format, "(Median(%d))", tailleFiltre);
	
		char nom[80];
		strcpy(nom, temp.getNom());
		strcat(nom, format);
	
		temp.setNom(nom);
		
		char buff[80];
		sprintf(buff, "Filtre Median de %d applique sur l'Image %d", tailleFiltre, id);
		log(buff);
	
		return Insere(&temp);
	}
}

int Moteur::FiltreMoyenneur(int id, int tailleFiltre) throw (MoteurException)
{
	Image* i1(getImage(id));
	ImageNG* pNG = dynamic_cast<ImageNG*>(i1);
	ImageRGB* pRGB = dynamic_cast<ImageRGB*>(i1);
	
	if(pNG)
	{
		ImageNG temp(Traitements::FiltreMoyenneur(*pNG, tailleFiltre));
		
		temp.setId(getLastID() + 1);
	
		char format[80];
	
		sprintf(format, "(Moyenneur(%d))", tailleFiltre);
	
		char nom[80];
		strcpy(nom, temp.getNom());
		strcat(nom, format);
	
		temp.setNom(nom);
		
		char buff[80];
		sprintf(buff, "Filtre Moyenneur de %d applique sur l'Image %d", tailleFiltre, id);
		log(buff);
	
		return Insere(&temp);
	}
	
	if(pRGB)
	{
		ImageRGB temp(Traitements::FiltreMoyenneur(*pRGB, tailleFiltre));
		
		temp.setId(getLastID() + 1);
	
		char format[80];
	
		sprintf(format, "(Moyenneur(%d))", tailleFiltre);
	
		char nom[80];
		strcpy(nom, temp.getNom());
		strcat(nom, format);
	
		temp.setNom(nom);
		
		char buff[80];
		sprintf(buff, "Filtre Moyenneur de %d applique sur l'Image %d", tailleFiltre, id);
		log(buff);
	
		return Insere(&temp);
	}
}

int Moteur::FiltreMoyenneurSelection(int id, int tailleFiltre) throw (MoteurException)
{
	Image* i1(getImage(id));
	ImageNG* pNG = dynamic_cast<ImageNG*>(i1);
	ImageRGB* pRGB = dynamic_cast<ImageRGB*>(i1);
	
	ImageNG tempNG;
	ImageRGB tempRGB;
	
	if(pNG)
		tempNG = *pNG;
	if(pRGB)
		tempRGB = *pRGB;
	
	Pixel p1, p2;
	WindowSDLclick click;
	
	if(pNG)
		WindowSDL::open(pNG->getLargeur(), pNG->getHauteur());
	if(pRGB)
		WindowSDL::open(pRGB->getLargeur(), pRGB->getHauteur());
	
	while(1)
	{
		if(pNG)
			tempNG.Dessine(0, 0);
		if(pRGB)
			tempRGB.Dessine(0, 0);
		
		click = WindowSDL::waitClick();
		if(click.getX() == -1 || click.getY() == -1) break;
		
		p1.setX(click.getX());
		p1.setY(click.getY());
		
	
		click = WindowSDL::waitClick();
		if(click.getX() == -1 || click.getY() == -1) break;
	
		p2.setX(click.getX());
		p2.setY(click.getY());
		
		if(pNG)
			tempNG = Traitements::FiltreMoyenneur(tempNG, tailleFiltre, p1, p2);
		if(pRGB)
			tempRGB = Traitements::FiltreMoyenneur(tempRGB, tailleFiltre, p1, p2);
	}
	
	WindowSDL::close();
	
	if(pNG)
	{
		tempNG.setId(getLastID() + 1);
	
		char format[80];
	
		sprintf(format, "(MoyenneurSelection(%d))", tailleFiltre);
	
		char nom[80];
		strcpy(nom, tempNG.getNom());
		strcat(nom, format);
	
		tempNG.setNom(nom);
	
		char buff[80];
		sprintf(buff, "Filtre Moyenneur(Selection) de %d applique sur l'Image %d", tailleFiltre, id);
		log(buff);
	
		return Insere(&tempNG);
	}
	
	if(pRGB)
	{
		tempRGB.setId(getLastID() + 1);
	
		char format[80];
	
		sprintf(format, "(MoyenneurSelection(%d))", tailleFiltre);
	
		char nom[80];
		strcpy(nom, tempRGB.getNom());
		strcat(nom, format);
	
		tempRGB.setNom(nom);
	
		char buff[80];
		sprintf(buff, "Filtre Moyenneur(Selection) de %d applique sur l'Image %d", tailleFiltre, id);
		log(buff);
	
		return Insere(&tempRGB);
	}
}

int Moteur::Dilatation(int id, int tailleFiltre) throw (MoteurException)
{
	Image* i1(getImage(id));
	ImageNG* pNG = dynamic_cast<ImageNG*>(i1);
	ImageRGB* pRGB = dynamic_cast<ImageRGB*>(i1);
	
	if(pNG)
	{
		ImageNG temp(Traitements::Dilatation(*pNG, tailleFiltre));
		temp.setId(getLastID() + 1);
	
		char format[80];
	
		sprintf(format, "(Dilatation(%d) de %d)", id, tailleFiltre);
	
		char nom[80];
		strcpy(nom, temp.getNom());
		strcat(nom, format);
	
		temp.setNom(nom);
		
		char buff[80];
		sprintf(buff, "Dilatation de %d applique sur l'Image %d", tailleFiltre, id);
		log(buff);
	
		return Insere(&temp);
	}
	
	if(pRGB)
	{
		ImageRGB temp(Traitements::Dilatation(*pRGB, tailleFiltre));
		
		temp.setId(getLastID() + 1);
	
		char format[80];
	
		sprintf(format, "(Dilatation(%d) de %d)", id, tailleFiltre);
	
		char nom[80];
		strcpy(nom, temp.getNom());
		strcat(nom, format);
	
		temp.setNom(nom);
		
		char buff[80];
		sprintf(buff, "Dilatation de %d applique sur l'Image %d", tailleFiltre, id);
		log(buff);
	
		return Insere(&temp);
	}
}

int Moteur::Erosion(int id, int tailleFiltre) throw (MoteurException)
{
	Image* i1(getImage(id));
	ImageNG* pNG = dynamic_cast<ImageNG*>(i1);
	ImageRGB* pRGB = dynamic_cast<ImageRGB*>(i1);
	
	if(pNG)
	{
		ImageNG temp(Traitements::Erosion(*pNG, tailleFiltre));
		temp.setId(getLastID() + 1);
	
		char format[80];
	
		sprintf(format, "(Erosion(%d) de %d)", id, tailleFiltre);
	
		char nom[80];
		strcpy(nom, temp.getNom());
		strcat(nom, format);
	
		temp.setNom(nom);
		
		char buff[80];
		sprintf(buff, "Erosion de %d applique sur l'Image %d", tailleFiltre, id);
		log(buff);
	
		return Insere(&temp);
	}
	
	if(pRGB)
	{
		ImageRGB temp(Traitements::Erosion(*pRGB, tailleFiltre));
		
		temp.setId(getLastID() + 1);
	
		char format[80];
	
		sprintf(format, "(Erosion(%d) de %d)", id, tailleFiltre);
	
		char nom[80];
		strcpy(nom, temp.getNom());
		strcat(nom, format);
	
		temp.setNom(nom);
		
		char buff[80];
		sprintf(buff, "Erosion de %d applique sur l'Image %d", tailleFiltre, id);
		log(buff);
	
		return Insere(&temp);
	}
}

int Moteur::Negatif(int id) throw (MoteurException)
{
	Image* i1(getImage(id));
	ImageNG* pNG = dynamic_cast<ImageNG*>(i1);
	ImageRGB* pRGB = dynamic_cast<ImageRGB*>(i1);
	
	if(pNG)
	{
		ImageNG temp(Traitements::Negatif(*pNG));
		temp.setId(getLastID() + 1);
	
		char format[80];
	
		sprintf(format, "(Negatif(%d))", id);
	
		char nom[80];
		strcpy(nom, temp.getNom());
		strcat(nom, format);
	
		temp.setNom(nom);
		
		char buff[80];
		sprintf(buff, "Negatif applique sur l'Image %d", id);
		log(buff);
	
		return Insere(&temp);
	}
	
	if(pRGB)
	{
		ImageRGB temp(Traitements::Negatif(*pRGB));
		
		temp.setId(getLastID() + 1);
	
		char format[80];
	
		sprintf(format, "(Negatif(%d))", id);
	
		char nom[80];
		strcpy(nom, temp.getNom());
		strcat(nom, format);
	
		temp.setNom(nom);
		
		char buff[80];
		sprintf(buff, "Negatif applique sur l'Image %d", id);
		log(buff);
	
		return Insere(&temp);
	}
}
