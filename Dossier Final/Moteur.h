#ifndef _MOTEURH_
#define _MOTEURH_

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
		
		int Insere(Image *pImage);
		ImageNG getImageNG(const int id) throw (MoteurException);
		Image* getImage(const int id) throw (MoteurException);
		
	public:
		Moteur();
		~Moteur();
		
		void Affiche();
		void SupprimeImage(const int id) throw (MoteurException);
		
		void VisualiseImage(const int id) throw (MoteurException);
		void VisualiseImages(const int id1, const int id2) throw (MoteurException);
		
		void ExporterBMP(const int id, const char* fichier) throw (MoteurException);
		
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
