#ifndef _IMAGENG_
#define _IMAGENG_

#include <iostream>
#include <fstream> 

#include "Image.h"
#include "Dimension.h"
#include "PixelNG.h"
#include "RGBException.h"
#include "XYException.h"

class ImageNG : public Image
{
	private:
		int** matrice;
		static int comparaison;
		
		int compLum(ImageNG i);
		int compPixel(ImageNG i, const int cmp);

	public:
		ImageNG();
		ImageNG(const char* path);
		ImageNG(int val, const char* name);
		ImageNG(const ImageNG& image);
		ImageNG(int nid, const char* unom, const Dimension& d);
		~ImageNG();
		
		const static int LUMINANCE;
		const static int PIXEL_A_PIXEL;
		
		void Save(ofstream &fichier) const;
		void Load(ifstream &fichier);
		
		
		static void setComparaison(int mode);
		static int getComparaison();

		void setPixel(int x, int y, int val) throw (RGBException, XYException);
		int getPixel(int x, int y) throw (XYException);

		void setDimension(const Dimension& d);
		void setBackground(int val) throw (RGBException);

		void Affiche() const;
		void Dessine();
		void Dessine(const int x, const int y);

		int** AllocMatrix(int Largeur, int Hauteur);
		void FreeMatrix();
		
		void importFromBMP(const char* name);
		void exportToBMP(const char* name);
		
		int getLuminance() const;
		int getMaximum() const;
		int getMinimum() const;
		float getContraste() const;
		
		void addToPix(const int num);
		void removeFromPix(const int num);
		void removeFromPixImageNG(ImageNG i2);
		
		ImageNG& operator=(const ImageNG& cpy);
		
		ImageNG& operator++();
		ImageNG operator++(int);
		
		ImageNG& operator--();
		ImageNG operator--(int);
		
		friend ImageNG operator+(const ImageNG& cpy, const int num);
		friend ImageNG operator+(const int num, const ImageNG& cpy);
		
		friend ImageNG operator+(const ImageNG& cpy, const PixelNG& pix) throw (XYException);
		friend ImageNG operator+(const PixelNG& pix, const ImageNG& cpy);
		
		friend ImageNG operator-(const ImageNG& cpy, const int num);
		friend ImageNG operator-(const int num, const ImageNG& cpy);
		
		friend ImageNG operator-(const ImageNG& i1, const ImageNG& i2);
		
		friend bool operator<(const ImageNG& i1, const ImageNG& i2) throw (XYException);
		friend bool operator>(const ImageNG& i1, const ImageNG& i2) throw (XYException);
		
		bool operator==(const ImageNG& i) throw (XYException);
		bool operator!=(const ImageNG& i) throw (XYException);
		
		friend std::ostream& operator<<(std::ostream& s, const ImageNG& cpy);
};

#endif
