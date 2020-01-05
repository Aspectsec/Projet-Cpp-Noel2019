#ifndef _IMAGERGB_
#define _IMAGERGB_

#include <fstream>

#include "Image.h"
#include "Couleur.h"
#include "PixelRGB.h"

class ImageRGB : public Image
{
	private:
		Couleur** matrice;
	
	public:
		ImageRGB();
		ImageRGB(const char* path);
		ImageRGB(int val, const char* name);
		ImageRGB(const ImageRGB& cpy);
		ImageRGB(const int nid, const char* nom, const Dimension& dcpy);
		~ImageRGB();
		
		void Save(std::ofstream &fichier) const;
		void Load(std::ifstream &fichier);
		
		void setDimension(const Dimension& dim);
		void setBackground(const Couleur& color);
		
		void Affiche() const;
		void Dessine();
		void Dessine(const int x, const int y);
		
		void setPixel(const int x, const int y, const Couleur& color) throw (XYException);
		Couleur getPixel(const int x, const int y) throw (XYException);
		
		void exportToBMP(const char* path);
		void importFromBMP(const char* path);
		
		Couleur** AllocMatrix(int Largeur, int Hauteur);
		void FreeMatrix();
		
		friend std::ostream& operator<<(std::ostream& s, const ImageRGB& cpy);
		
		friend ImageRGB operator+(const ImageRGB& image, const PixelRGB& pix) throw (XYException);
		friend ImageRGB operator+(const PixelRGB& pix, const ImageRGB& image);
		
		ImageRGB& operator=(const ImageRGB& cpy);
};

#endif
