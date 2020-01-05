#ifndef _TRAITEMENTSH_
#define _TRAITEMENTSH_

#include "ImageNG.h"
#include "ImageB.h"
#include "ImageRGB.h"
#include "ListeTriee.h"

class Traitements
{
	public:
		static ImageB Seuillage(const ImageNG& imageIn, int seuil);
		static ImageNG FiltreMoyenneur(const ImageNG& imageIn, int taille, Pixel p1=Pixel(), Pixel p2=Pixel());
		static ImageNG FiltreMedian(const ImageNG& imageIn, int taille);
		static ImageNG Erosion(const ImageNG& imageIn, int taille);
		static ImageNG Dilatation(const ImageNG& imageIn, int taille);
		static ImageNG Negatif(const ImageNG& imageIn);
};

#endif
