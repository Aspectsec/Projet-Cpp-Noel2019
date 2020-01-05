#include "Traitements.h"

ImageB Traitements::Seuillage(const ImageNG& imageIn, int seuil)
{
	ImageNG in(imageIn);
	ImageB out(in.getId(), in.getNom(), in.getDimension());
	
	Dimension dim = in.getDimension();
	
	for(int x = 0; x < dim.getLargeur(); x++)
		for(int y = 0; y < dim.getHauteur(); y++)
		{
			if(in.getPixel(x, y) < seuil)
				out.setPixel(x, y, false);
			else
				out.setPixel(x, y, true);
		}
		
	return out;
}

ImageNG Traitements::FiltreMoyenneur(const ImageNG& imageIn, int taille, Pixel p1, Pixel p2)
{
	ImageNG in(imageIn);
	ImageNG out(imageIn);
	
	Dimension dim = out.getDimension();
	
	int start, finishx, finishy, surface, pixOut = 0;
	
	if((p1.getX() == 0 && p1.getY() == 0) && (p2.getX() == 0 && p2.getY() == 0))
	{
		start = 0;
		finishx = dim.getLargeur();
		finishy = dim.getHauteur();
	}
	else
	{
		start = p1.getX();
		finishx = p2.getX();
		finishy = p2.getY();
	}
	
	int moy = 0;
	
	for(int x = start; x < finishx; x++)
	{
		for(int y = start; y < finishy; y++)
		{
			moy = 0;
			
			for(int i = x-(taille / 2); i <= x+(taille / 2); i++)
			{
				for(int j = y-(taille / 2); j <= y+(taille / 2); j++)
					{
						if((i >= 0) && (j >= 0) && (i < dim.getLargeur()) && (j < dim.getHauteur()) && (in.getPixel(i, j) <= 255) && (in.getPixel(i, j) >= 0))
						{
							moy += in.getPixel(i, j);
						}
					}
			}
			out.setPixel(x, y, moy / (taille * taille));
		}
	}
	
	return out;
}

ImageNG Traitements::FiltreMedian(const ImageNG& imageIn, int taille)
{
	ImageNG in(imageIn);
	ImageNG out(imageIn);
	
	Dimension dim = in.getDimension();
	
	int mediane = 0;
	
	for(int x = 0; x < dim.getLargeur(); x++)
	{
		for(int y = 0; y < dim.getHauteur(); y++)
		{
			ListeTriee<int> temp;
			Iterateur<int> it(temp);
			
			for(int i = x-(taille / 2); i <= x+(taille / 2); i++)
			{
				for(int j = y-(taille / 2); j <= y+(taille / 2); j++)
					{
						if((i >= 0) && (j >= 0) && (i != x && j != y) &&(i < dim.getLargeur()) && (j < dim.getHauteur()) && (in.getPixel(i, j) < 255) && (in.getPixel(i, j) >= 0))
						{
							temp.insere(in.getPixel(i, j));
						}
					}
			}
			
			mediane = temp.getNombreElements() / 2;
			
			it.reset();
			for(int i = 1; i < mediane && !it.end(); i++, it++);
			
			out.setPixel(x, y, (int)it);
		}
	}
	
	return out;
}

ImageNG Traitements::Erosion(const ImageNG& imageIn, int taille)
{
	ImageNG in(imageIn);
	ImageNG out(imageIn);
	
	Dimension dim = in.getDimension();
	
	for(int x = 0; x < dim.getLargeur(); x++)
	{
		for(int y = 0; y < dim.getHauteur(); y++)
		{
			ListeTriee<int> temp;
			Iterateur<int> it(temp);
			
			for(int i = x-(taille / 2); i <= x+(taille / 2); i++)
			{
				for(int j = y-(taille / 2); j <= y+(taille / 2); j++)
					{
						if((i >= 0) && (j >= 0) && (i != x && j != y) &&(i < dim.getLargeur()) && (j < dim.getHauteur()) && (in.getPixel(i, j) < 255) && (in.getPixel(i, j) >= 0))
						{
							temp.insere(in.getPixel(i, j));
						}
					}
			}
			
			it.reset();
			
			out.setPixel(x, y, (int)it);
		}
	}
	
	return out;
}

ImageNG Traitements::Dilatation(const ImageNG& imageIn, int taille)
{
	ImageNG in(imageIn);
	ImageNG out(imageIn);
	
	Dimension dim = in.getDimension();
	
	for(int x = 0; x < dim.getLargeur(); x++)
	{
		for(int y = 0; y < dim.getHauteur(); y++)
		{
			ListeTriee<int> temp;
			Iterateur<int> it(temp);
			
			for(int i = x-(taille / 2); i <= x+(taille / 2); i++)
			{
				for(int j = y-(taille / 2); j <= y+(taille / 2); j++)
					{
						if((i >= 0) && (j >= 0) && (i != x && j != y) &&(i < dim.getLargeur()) && (j < dim.getHauteur()) && (in.getPixel(i, j) < 255) && (in.getPixel(i, j) >= 0))
						{
							temp.insere(in.getPixel(i, j));
						}
					}
			}
			
			for(it.reset(); !it.end(); it++);
			
			out.setPixel(x, y, (int)it);
		}
	}
	
	return out;
}

ImageNG Traitements::Negatif(const ImageNG& imageIn)
{
	ImageNG in(imageIn);
	ImageNG out(imageIn);
	
	Dimension dim = in.getDimension();
	
	for(int x = 0; x < dim.getLargeur(); x++)
		for(int y = 0; y < dim.getHauteur(); y++)
		{
			out.setPixel(x, y, (255 - in.getPixel(x, y)));
		}
		
	return out;
}
