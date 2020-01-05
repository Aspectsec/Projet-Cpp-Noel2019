#ifndef _IMAGEB_
#define _IMAGEB_

#include <fstream>

#include "Dimension.h"
#include "Image.h"
#include "PixelB.h"
#include "Couleur.h"
#include "XYException.h"

class ImageB : public Image
{
	private:
		bool** matrice;
	
	public:
		ImageB();
		ImageB(const char* path);
		ImageB(bool val, const char* name);
		ImageB(const ImageB& image);
		ImageB(int nid, const char* unom, const Dimension& d);
		~ImageB();
		
		void Save(std::ofstream &fichier) const;
		void Load(std::ifstream &fichier);
		
		static Couleur couleurTrue;
		static Couleur couleurFalse;
		
		bool getPixel(const int x, const int y) const throw (XYException);
		void setPixel(const int x, const int y, const bool val) throw (XYException);
		
		void setDimension(const Dimension& d);
		
		void setBackground(const bool val);
		
		bool** AllocMatrix(int Largeur, int Hauteur);
		void FreeMatrix();
		
		void Affiche() const;
		void Dessine();
		void Dessine(const int x, const int y);
		
		void importFromBMP(const char* name);
		void exportToBMP(const char* name);
		
		friend std::ostream& operator<<(std::ostream& s, const ImageB& cpy);
		
		friend ImageB operator+(const ImageB& cpy, const PixelB& pix) throw (XYException);
		friend ImageB operator+(const PixelB& pix, const ImageB& cpy);
		
		ImageB& operator=(const ImageB& cpy);
};

#endif
