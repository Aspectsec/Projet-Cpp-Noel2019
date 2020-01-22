#include "Traitements.h"

ImageB Traitements::Seuillage(const ImageNG& imageIn, int seuil)
{
	ImageNG in(imageIn);
	ImageB out(in.getId(), in.getNom(), in.getDimension());
	
	Dimension dim = in.getDimension();
	
	try
	{
	
		for(int x = 0; x < dim.getLargeur(); x++)
			for(int y = 0; y < dim.getHauteur(); y++)
			{
				if(in.getPixel(x, y) < seuil)
					out.setPixel(x, y, false);
				else
					out.setPixel(x, y, true);
			}
		
	}
	catch(RGBException e) { fprintf(stderr, "%s\n", e.getErreur()); }
	catch(XYException e) { fprintf(stderr, "%s\n", e.getErreur()); }
	
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
	
	try
	{
	
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
	
	}
	catch(RGBException e) { fprintf(stderr, "%s\n", e.getErreur()); }
	catch(XYException e) { fprintf(stderr, "%s\n", e.getErreur()); }
	
	return out;
}

ImageNG Traitements::FiltreMedian(const ImageNG& imageIn, int taille)
{
	ImageNG in(imageIn);
	ImageNG out(imageIn);
	
	Dimension dim = in.getDimension();
	
	int mediane = 0;
	
	try
	{
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
							if((i >= 0) && (j >= 0) && (i < dim.getLargeur()) && (j < dim.getHauteur()))
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
	}
	catch(RGBException e) { fprintf(stderr, "%s\n", e.getErreur()); }
	catch(XYException e) { fprintf(stderr, "%s\n", e.getErreur()); }
	
	return out;
}

ImageNG Traitements::Erosion(const ImageNG& imageIn, int taille)
{
	ImageNG in(imageIn);
	ImageNG out(imageIn);
	
	Dimension dim = in.getDimension();
	
	int min;
	
	try
	{
	
		for(int x = 0; x < dim.getLargeur(); x++)
		{
			for(int y = 0; y < dim.getHauteur(); y++)
			{
				min = 256;
				for(int i = x-(taille / 2); i <= x+(taille / 2); i++)
				{
					for(int j = y-(taille / 2); j <= y+(taille / 2); j++)
						{
							if((i >= 0) && (j >= 0) && (i < dim.getLargeur()) && (j < dim.getHauteur()) && (in.getPixel(i, j) < 255) && (in.getPixel(i, j) >= 0))
							{
								if(in.getPixel(i, j) < min)
									min = in.getPixel(i, j) ;
							}
						}
				}
				out.setPixel(x, y, min);
			}
		}
	
	}
	catch(RGBException e) { fprintf(stderr, "%s\n", e.getErreur()); }
	catch(XYException e) { fprintf(stderr, "%s\n", e.getErreur()); }
	
	return out;
}

ImageNG Traitements::Dilatation(const ImageNG& imageIn, int taille)
{
	ImageNG in(imageIn);
	ImageNG out(imageIn);
	
	Dimension dim = in.getDimension();
	
	int max;
	
	try
	{
	
		for(int x = 0; x < dim.getLargeur(); x++)
		{
			for(int y = 0; y < dim.getHauteur(); y++)
			{
				max = -1;
				for(int i = x-(taille / 2); i <= x+(taille / 2); i++)
				{
					for(int j = y-(taille / 2); j <= y+(taille / 2); j++)
						{
							if((i >= 0) && (j >= 0) && (i < dim.getLargeur()) && (j < dim.getHauteur()) && (in.getPixel(i, j) < 255) && (in.getPixel(i, j) >= 0))
							{
								if(in.getPixel(i, j) > max)
									max = in.getPixel(i, j);
							}
						}
				}
				out.setPixel(x, y, max);
			}
		}
	
	}
	catch(RGBException e) { fprintf(stderr, "%s\n", e.getErreur()); }
	catch(XYException e) { fprintf(stderr, "%s\n", e.getErreur()); }
	
	return out;
}

ImageNG Traitements::Negatif(const ImageNG& imageIn)
{
	ImageNG in(imageIn);
	ImageNG out(imageIn);
	
	Dimension dim = in.getDimension();
	
	try
	{
	
		for(int x = 0; x < dim.getLargeur(); x++)
			for(int y = 0; y < dim.getHauteur(); y++)
				out.setPixel(x, y, (255 - in.getPixel(x, y)));
	
	}
	catch(RGBException e) { fprintf(stderr, "%s\n", e.getErreur()); }
	catch(XYException e) { fprintf(stderr, "%s\n", e.getErreur()); }
	
	return out;
}


//------------------------------------------------RGB-----------------------------------------------


ImageB Traitements::Seuillage(const ImageRGB& imageIn, int seuil)
{
	ImageRGB cpy(imageIn);
	
	ImageB out(cpy.getId(), cpy.getNom(), cpy.getDimension());
	
	ImageB temp1(Traitements::Seuillage(cpy.getRouge(), seuil));
	ImageB temp2(Traitements::Seuillage(cpy.getVert(), seuil));
	ImageB temp3(Traitements::Seuillage(cpy.getBleu(), seuil));
	
	Dimension dim = cpy.getDimension();
	
	try
	{
	
		for(int x = 0; x < dim.getLargeur(); x++)
			for(int y = 0; y < dim.getHauteur(); y++)
			{
				if(temp1.getPixel(x, y) == false || temp2.getPixel(x, y) == false || temp3.getPixel(x, y) == false)
					out.setPixel(x, y, false);
				else
					out.setPixel(x, y, true);
			}
		
	}
	catch(RGBException e) { fprintf(stderr, "%s\n", e.getErreur()); }
	catch(XYException e) { fprintf(stderr, "%s\n", e.getErreur()); }
	
	return out;
}

ImageRGB Traitements::FiltreMoyenneur(const ImageRGB& imageIn, int taille, Pixel p1, Pixel p2)
{
	ImageRGB in(imageIn);
	ImageRGB out(imageIn);
	
	ImageNG r(in.getRouge()), g(in.getVert()), b(in.getBleu());
	
	out.setRGB(Traitements::FiltreMoyenneur(r, taille, p1, p2), Traitements::FiltreMoyenneur(g, taille, p1, p2), Traitements::FiltreMoyenneur(b, taille, p1, p2));
	
	return out;
}

ImageRGB Traitements::FiltreMedian(const ImageRGB& imageIn, int taille)
{
	ImageRGB in(imageIn);
	ImageRGB out(imageIn);
	
	ImageNG r(in.getRouge()), g(in.getVert()), b(in.getBleu());
	
	out.setRGB(Traitements::FiltreMedian(r, taille), Traitements::FiltreMedian(g, taille), Traitements::FiltreMedian(b, taille));
	
	return out;
}

ImageRGB Traitements::Erosion(const ImageRGB& imageIn, int taille)
{
	ImageRGB in(imageIn);
	ImageRGB out(imageIn);
	
	ImageNG r(in.getRouge()), g(in.getVert()), b(in.getBleu());
	
	out.setRGB(Traitements::Erosion(r, taille), Traitements::Erosion(g, taille), Traitements::Erosion(b, taille));
	
	return out;
}

ImageRGB Traitements::Dilatation(const ImageRGB& imageIn, int taille)
{
	ImageRGB in(imageIn);
	ImageRGB out(imageIn);
	
	ImageNG r(in.getRouge()), g(in.getVert()), b(in.getBleu());
	
	out.setRGB(Traitements::Dilatation(r, taille), Traitements::Dilatation(g, taille), Traitements::Dilatation(b, taille));
	
	return out;
}

ImageRGB Traitements::Negatif(const ImageRGB& imageIn)
{
	ImageRGB in(imageIn);
	ImageRGB out(imageIn);
	
	ImageNG r(in.getRouge()), g(in.getVert()), b(in.getBleu());
	
	out.setRGB(Traitements::Negatif(r), Traitements::Negatif(g), Traitements::Negatif(b));
	
	return out;
}
