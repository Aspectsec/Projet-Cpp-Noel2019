.SILENT :

CC = g++ -m64
OBJ = WindowSDL.o WindowSDLexception.o WindowSDLimage.o WindowSDLclick.o ImageNG.o Dimension.o PixelNG.o Couleur.o ImageRGB.o PixelRGB.o ImageB.o PixelB.o Image.o Pixel.o BaseException.o RGBException.o XYException.o Liste.o ListeBase.o ListeTriee.o Iterateur.o Traitements.o Moteur.o UI.o MoteurException.o

MiniPhotoshop: MiniPhotoshop.cpp $(OBJ)
	echo creation de MiniPhotoshop ...
	$(CC) MiniPhotoshop.cpp $(OBJ) -o MiniPhotoshop -lpthread -lSDL

Moteur.o: Moteur.cpp Moteur.h
	echo Creation de Moteur.o ...
	$(CC) Moteur.cpp -c

UI.o: UI.cpp UI.h
	echo Creation de UI.o ...
	$(CC) UI.cpp -c

Traitements.o: Traitements.cpp Traitements.h
	echo Creation de Traitements.o ...
	$(CC) Traitements.cpp -c

ImageNG.o: ImageNG.cpp ImageNG.h Image.o
	echo Creation de ImageNG.o ...
	$(CC) ImageNG.cpp -c

ImageRGB.o: ImageRGB.cpp ImageRGB.h Image.o
	echo Creation de ImageRGB.o ...
	$(CC) ImageRGB.cpp -c

ImageB.o: ImageB.cpp ImageB.h Image.o 
	echo Creation de ImageB.O ...
	$(CC) ImageB.cpp -c

Image.o: Image.cpp Image.h
	echo Creation de Image.o ...
	$(CC) Image.cpp -c

Dimension.o: Dimension.cpp Dimension.h XYException.o
	echo Creation de Dimension.o ...
	$(CC) Dimension.cpp -c

PixelB.o: PixelB.cpp PixelB.h Pixel.o
	echo Creation de PixelB.o ...
	$(CC) PixelB.cpp -c

PixelNG.o: PixelNG.cpp PixelNG.h Pixel.o
	echo Creation de PixelNG.o ...
	$(CC) PixelNG.cpp -c
	
PixelRGB.o: PixelRGB.cpp PixelRGB.h Pixel.o
	echo Creation de PixelRGB.o ...
	$(CC) PixelRGB.cpp -c

Pixel.o: Pixel.cpp Pixel.h
	echo Creation de Pixel.o ...
	$(CC) Pixel.cpp -c

BaseException.o: BaseException.cpp BaseException.h
	echo Creation de BaseException.o ...
	$(CC) BaseException.cpp -c

RGBException.o: RGBException.cpp RGBException.h
	echo Creation de RGBException.o ...
	$(CC) RGBException.cpp -c

XYException.o: XYException.cpp XYException.h
	echo Creation de XYException.o ...
	$(CC) XYException.cpp -c

MoteurException.o: MoteurException.cpp MoteurException.h
	echo Creation de MoteurException.o ...
	$(CC) MoteurException.cpp -c

Couleur.o: Couleur.cpp Couleur.h
	echo Creation de Couleur.o
	$(CC) Couleur.cpp -c

Liste.o: Liste.cpp Liste.h
	echo Creation de Liste.o
	$(CC) Liste.cpp -c

ListeBase.o: ListeBase.cpp ListeBase.h
	echo Creation de ListeBase.o
	$(CC) ListeBase.cpp -c

ListeTriee.o: ListeTriee.cpp ListeTriee.h
	echo Creation de ListeTriee.o
	$(CC) ListeTriee.cpp -c

Iterateur.o: Iterateur.cpp Iterateur.h
	echo Creation de Iterateur.o
	$(CC) Iterateur.cpp -c

WindowSDL.o:	WindowSDL.cpp WindowSDL.h
	echo Creation de WindowSDL.o ...
	$(CC) -c WindowSDL.cpp

WindowSDLexception.o:	WindowSDLexception.cpp WindowSDLexception.h
	echo Creation de WindowSDLexception.o ...
	$(CC) -c WindowSDLexception.cpp

WindowSDLclick.o:	WindowSDLclick.cpp WindowSDLclick.h
	echo Creation de WindowSDLclick.o ...
	$(CC) -c WindowSDLclick.cpp

WindowSDLimage.o:	WindowSDLimage.cpp WindowSDLimage.h
	echo Creation de WindowSDLimage.o ...
	$(CC) -c WindowSDLimage.cpp
