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
		
		static ImageB Seuillage(const ImageRGB& imageIn, int seuil);
		static ImageRGB FiltreMoyenneur(const ImageRGB& imageIn, int taille, Pixel p1=Pixel(), Pixel p2=Pixel());
		static ImageRGB FiltreMedian(const ImageRGB& imageIn, int taille);
		static ImageRGB Erosion(const ImageRGB& imageIn, int taille);
		static ImageRGB Dilatation(const ImageRGB& imageIn, int taille);
		static ImageRGB Negatif(const ImageRGB& imageIn);
};

#endif
