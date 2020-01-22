#ifndef _MOTEURH_
#define _MOTEURH_

#include <fstream>

#include "WindowSDLimage.h"
#include "WindowSDL.h"

#include "Image.h"
#include "ImageRGB.h"
#include "ImageNG.h"
#include "ImageB.h"

#include "Liste.h"
#include "ListeTriee.h"

#include "Traitements.h"
#include "MoteurException.h"

class Moteur
{
	private:
		ListeTriee<ImageNG>	ImagesNG;
		Liste<ImageRGB>		ImagesRGB;
		Liste<ImageB>			ImagesB;
		
		ofstream fichierLog;
		
		int Insere(Image *pImage);
		int getLastID();
		
		int getImageType(Image* src);																	//1->B	2->NG		3->RGB
		
		ImageNG getImageNG(const int id) throw (MoteurException);
		Image* getImage(const int id) throw (MoteurException);
		
	public:
		Moteur();
		~Moteur();
		
		void log(const char* str);
		
		void SaveState(ofstream& fImages);
		void LoadState(ifstream& fImages);
		
		void Affiche();
		void SupprimeImage(const int id) throw (MoteurException);
		
		void VisualiseImage(const int id) throw (MoteurException);
		void VisualiseImages(const int id1, const int id2) throw (MoteurException);
		
		void ExporterBMP(const int id, const char* fichier) throw (MoteurException);
		
		void ImportCSV(const char* fichier);
		
		int ImporteImageB(const char* fichier);
		int ImporteImageNG(const char* fichier);
		int ImporteImageRGB(const char* fichier);
		
		int AugmenteLuminosite(const int id, const int val) throw (MoteurException);
		int DiminueLuminosite(const int id, const int val) throw (MoteurException);
		
		int Soustraire(const int id1, const int id2) throw (MoteurException);
		int Seuillage(int id, int seuil) throw (MoteurException);
		int Negatif(int id) throw (MoteurException);
		int FiltreMedian(int id, int tailleFiltre) throw (MoteurException);
		int FiltreMoyenneur(int id, int tailleFiltre) throw (MoteurException);
		int FiltreMoyenneurSelection(int id, int tailleFiltre) throw (MoteurException);
		int Dilatation(int id, int tailleFiltre) throw (MoteurException);
		int Erosion(int id, int tailleFiltre) throw (MoteurException);
};

#endif
